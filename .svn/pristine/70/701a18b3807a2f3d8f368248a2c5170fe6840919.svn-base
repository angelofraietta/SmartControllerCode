
/**************************************************************
File taken from 
http://remus.rutgers.edu/~rhoads/Code/crc-32b.c
***********************************************************/

#include <stdio.h>

int gen_table(void);                /* build the crc table */

static unsigned long crc_table[256];

/* This will force the Table to generate on Startup */
static int dummy_value = gen_table();

int gen_table(void)                /* build the crc table */
{
    unsigned long crc, poly;
    int	i, j;

    poly = 0xEDB88320L;
    for (i = 0; i < 256; i++)
        {
        crc = i;
        for (j = 8; j > 0; j--)
            {
            if (crc & 1)
                crc = (crc >> 1) ^ poly;
            else
                crc >>= 1;
            }
        crc_table[i] = crc;
        }
		return i;

}


extern "C" unsigned long CRC32(unsigned char ch, unsigned long crc)
{
	crc = (( crc >> 8 ) & 0x00FFFFFFL) ^ (crc_table[ ( (short int) crc ^ ch ) & 0xff ]);
	return crc;
}

extern "C" unsigned long calculate_crc(unsigned const char* buf, unsigned buflen)    /* calculate the crc value */
{
    register unsigned long crc;

    crc = 0xFFFFFFFFL;
    for (unsigned i = 0; i < buflen; i++)
			{
        crc = CRC32 (buf[i], crc);
			}

    return( crc^0xFFFFFFFFL );
}



extern "C" unsigned long crc_file (const char* filename)
{
	register unsigned long crc = 0xFFFFFFFFL;

	if (filename)
		{
			FILE* fp = fopen (filename, "r+b");
			if (fp)
				{
					unsigned char c;
					while (fread (&c, 1, 1, fp))
						{
							crc = CRC32 (c, crc);
						}
          fclose(fp);
				}
      else
      {
        printf("crc_file-> Unable to open %s\r\n", filename);
      }
		}
    else
      {
        printf("crc_file-> No filename");
      }
	return( crc^0xFFFFFFFFL );
}


extern "C" void crc_to_buf (unsigned long crc, unsigned char* ret)
{
  // store lowest byte and shift right
  for (unsigned i = 0; i < sizeof (crc); i++)
  {
    ret [i] = (char)crc;
    crc /= 256;
  }
}

extern "C" unsigned long buf_to_crc (const unsigned char* buf)
{
  unsigned long ret = 0;

  for (unsigned i = sizeof (ret) - 1;  i > 0; i--)
  {
    ret += buf [i];
    ret *= 256;
  }

  ret += buf [0];

  return ret;
}


