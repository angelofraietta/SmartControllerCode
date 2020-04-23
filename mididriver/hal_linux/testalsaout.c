/*
Test opening and sending a message to a virtual ALSA mixer

For Raspberry Pi, do following

sudo apt-get install timidity
sudo apt install timidity-daemon
sudo apt-get install libasound2-dev

compile
gcc -o testalsaout testalsaout.c -lasound -lpthread
*/

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
// ALSA header file.
#include <alsa/asoundlib.h>

// A structure to hold variables related to the ALSA API
// implementation.
typedef struct AlsaMidiData {
  snd_seq_t *seq;
  int vport;
  snd_seq_port_subscribe_t *subscription;
  snd_midi_event_t *coder;
  unsigned int bufferSize;
  unsigned char *buffer;
  pthread_t thread;
  unsigned long long lastTime;
  int queue_id; // an input queue is needed to get timestamped events
} AlsaMidiData;

AlsaMidiData *gAlsaMididata;

#define PORT_TYPE( pinfo, bits ) ((snd_seq_port_info_get_capability(pinfo) & (bits)) == (bits))
#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )

// This function is used to count or get the pinfo structure for a given port number.
unsigned int portInfo( snd_seq_t *seq, snd_seq_port_info_t *pinfo, unsigned int type, int portNumber )
{
    snd_seq_client_info_t *cinfo;
    int client;
    int count = 0;
    snd_seq_client_info_alloca( &cinfo );

    snd_seq_client_info_set_client( cinfo, -1 );
    printf ("Get Client \r\n");
    while ( snd_seq_query_next_client( seq, cinfo ) >= 0 ) 
    {
        client = snd_seq_client_info_get_client( cinfo );
        if ( client == 0 ){
            printf ("Client 0\r\n");
            continue;
        }

        // Reset query info
        snd_seq_port_info_set_client( pinfo, client );
        snd_seq_port_info_set_port( pinfo, -1 );

        while ( snd_seq_query_next_port( seq, pinfo ) >= 0 ) 
        {
            if ( !PORT_TYPE( pinfo, type ) )  continue;

            if ( count == portNumber ) return 1;

            count++;
        }
    }

  // If a negative portNumber was used, return the port count.
  if ( portNumber < 0 ) return count;
  return 0;
}

void* initialize()
{
    void* ret = NULL;
  // Set up the ALSA sequencer client.
    snd_seq_t *seq;
    int result = snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, 0);
    if ( result < 0 ) {
        printf("RtMidiOut::initialize: error creating ALSA sequencer client object.\r\n");
        return ret;
    }
    
    // Set client name.
    snd_seq_set_client_name(seq, " Output Client");

    // Save our api-specific connection information.
    AlsaMidiData *data = (AlsaMidiData *) malloc (sizeof(AlsaMidiData));
    data->seq = seq;
    data->vport = -1;
    data->bufferSize = 32;
    data->coder = 0;
    data->buffer = 0;
    result = snd_midi_event_new( data->bufferSize, &data->coder );
    if ( result < 0 ) {
      free(data);
      printf("initialize: error initializing MIDI event parser!\n\n");
      return ret;
    }

    data->buffer = (unsigned char *) malloc( data->bufferSize );
    if ( data->buffer == NULL ) {
      free (data);
      printf("initialize: error allocating buffer memory!\n\n");
      return ret;
    }

    printf("Buffer allocated\n\n");
    snd_midi_event_init( data->coder );
    ret = (void *) data;

    return ret;
}

 int getPortCount()
{
     int ret = 0;
	snd_seq_port_info_t *pinfo;
	snd_seq_port_info_alloca( &pinfo );

    AlsaMidiData *data = gAlsaMididata;
    if (data){
        ret = portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, -1 );
    }
    
    return ret;
}

int getPortName( unsigned int portNumber , char* ret_buf, unsigned ret_size)
{
  int ret = 0;
  snd_seq_client_info_t *cinfo;
  snd_seq_port_info_t *pinfo;
  snd_seq_client_info_alloca( &cinfo );
  snd_seq_port_info_alloca( &pinfo );


  AlsaMidiData *data = gAlsaMididata;

  if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, (int) portNumber ) ) {
    int cnum = snd_seq_port_info_get_client( pinfo );
    snd_seq_get_any_client_info( data->seq, cnum, cinfo );



    snd_seq_client_info_get_name( cinfo );
    ":";
    strncat (ret_buf, snd_seq_client_info_get_name( cinfo ), ret_size);
    /*
    os << snd_seq_port_info_get_name( pinfo );
    os << " ";                                    // These lines added to make sure devices are listed
    os << snd_seq_port_info_get_client( pinfo );  // with full portnames added to ensure individual device names
    os << ":";
    os << snd_seq_port_info_get_port( pinfo );
    stringName = os.str();
    return stringName;
    */
    ret = strlen (ret_buf);
    }

    return ret;
  }

int openPort( unsigned int portNumber, const char* portName )
{
  int ret = 0;

  snd_seq_port_info_t *pinfo;
  snd_seq_port_info_alloca( &pinfo );
  AlsaMidiData *data = gAlsaMididata;

  if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, (int) portNumber ) == 0 ) {

    printf ("openPort: the 'portNumber' %u is invalid. \r\n", portNumber  );
    return ret;
  }

  snd_seq_addr_t sender, receiver;
  receiver.client = snd_seq_port_info_get_client( pinfo );
  receiver.port = snd_seq_port_info_get_port( pinfo );
  sender.client = snd_seq_client_id( data->seq );

  if ( data->vport < 0 ) {
    data->vport = snd_seq_create_simple_port( data->seq, portName,
                                              SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
                                              SND_SEQ_PORT_TYPE_MIDI_GENERIC|SND_SEQ_PORT_TYPE_APPLICATION );
    if ( data->vport < 0 ) {
      printf ("openPort: ALSA error creating output port.\r\n");

      return ret;
    }
  }

  sender.port = data->vport;

  // Make subscription
  if ( snd_seq_port_subscribe_malloc( &data->subscription ) < 0 ) {
    snd_seq_port_subscribe_free( data->subscription );
    printf ("openPort: error allocating port subscription.\r\n");
    return ret;
  }
  snd_seq_port_subscribe_set_sender( data->subscription, &sender );
  snd_seq_port_subscribe_set_dest( data->subscription, &receiver );
  snd_seq_port_subscribe_set_time_update( data->subscription, 1 );
  snd_seq_port_subscribe_set_time_real( data->subscription, 1 );
  if ( snd_seq_subscribe_port( data->seq, data->subscription ) ) {
    snd_seq_port_subscribe_free( data->subscription );
    printf ("openPort: ALSA error making port connection.\r\n");

    return ret;
  }

  ret = 1;
  return ret;
}

void closePort( void )
{
    AlsaMidiData *data = gAlsaMididata;
    snd_seq_unsubscribe_port( data->seq, data->subscription );
    snd_seq_port_subscribe_free( data->subscription );
    data->subscription = 0;
}

void sendMessage( const unsigned char *message, int nBytes )
{
  int result;
  AlsaMidiData *data = gAlsaMididata;


  if ( nBytes > data->bufferSize ) {
    data->bufferSize = nBytes;
    result = snd_midi_event_resize_buffer( data->coder, nBytes );
    if ( result != 0 ) {
      printf ("sendMessage: ALSA error resizing MIDI event buffer.\r\n");

      return;
    }
    free (data->buffer);
    data->buffer = (unsigned char *) malloc( data->bufferSize );
    if ( data->buffer == NULL ) {
      printf ("initialize: error allocating buffer memory!\n\n");
      return;
    }
  }

  snd_seq_event_t ev;
  snd_seq_ev_clear( &ev );
  snd_seq_ev_set_source( &ev, data->vport );
  snd_seq_ev_set_subs( &ev );
  snd_seq_ev_set_direct( &ev );
  for ( unsigned int i=0; i<nBytes; ++i ) data->buffer[i] = message[i];
  result = snd_midi_event_encode( data->coder, data->buffer, (long)nBytes, &ev );
  if ( result < (int)nBytes ) {
    printf ("sendMessage: event parsing error!\r\n");
    return;
  }

  // Send the event.
  result = snd_seq_event_output( data->seq, &ev );
  if ( result < 0 ) {
    printf ("sendMessage: error sending MIDI message to port.\r\n");

    return;
  }
  snd_seq_drain_output( data->seq );
  printf ("Sent Message \r\n");
}


int main(void){
    printf("Test ALSA Aoutput \n");

    gAlsaMididata = initialize();
    if (gAlsaMididata)
    {
        int count  = getPortCount();

        printf("Port count = %u\r\n", count);

        for (int i = 0; i < count; i++)
        {
            char buf [256];
            buf [0] = '\0';
            if (getPortName(i, buf, sizeof(buf) -1))
            {

                printf ("Port %u %s \r\n", i, buf);
                if (openPort(i, buf)){
                    printf ("Opened Port \r\n");

                    unsigned char message [3];
                  message[0] = 0x90;
                  message[1] = 64;
                  message[2] = 90;

                    sendMessage( message, 3 );

                    SLEEP( 500 );

                    // Note Off: 128, 64, 40
                    message[0] = 128;
                    message[1] = 64;
                    message[2] = 40;
                    sendMessage(message , 3);

                    SLEEP( 500 );
                    closePort();
                }
            }

        }

        if (openPort(1, "Test")){
            printf ("Opened Port \r\n");

            unsigned char message [3];
          message[0] = 0x90;
          message[1] = 64;
          message[2] = 90;

            sendMessage( message, 3 );

            SLEEP( 500 );

            // Note Off: 128, 64, 40
            message[0] = 128;
            message[1] = 64;
            message[2] = 40;
            sendMessage(message , 3);

            SLEEP( 500 );
            closePort();
        }
    }
    else
    {
        printf ("Unable to allocate \r\n");
    }
    return 0;
}