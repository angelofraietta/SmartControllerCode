//## begin module%3D802415035A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D802415035A.cm

//## begin module%3D802415035A.cp preserve=no
//	Angelo Fraietta
//## end module%3D802415035A.cp

//## Module: NVRAMStore%3D802415035A; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\nvramstore.h

#ifndef nvramstore_h
#define nvramstore_h 1

//## begin module%3D802415035A.additionalIncludes preserve=no
//## end module%3D802415035A.additionalIncludes

//## begin module%3D802415035A.includes preserve=yes
//## end module%3D802415035A.includes

// iodata
#include "iodata.h"
// FileBlock
#include "fileblock.h"
// Event
#include "event.h"
// ActiveObject
#include "activeobject.h"

class MidiOutputDriver;

//## begin module%3D802415035A.additionalDeclarations preserve=yes
using sm_str::vector;
//## end module%3D802415035A.additionalDeclarations


//## begin NVRAMStore%3D802415035A.preface preserve=yes
//## end NVRAMStore%3D802415035A.preface

//## Class: NVRAMStore%3D802415035A
//	This is a single block of memory that contains AllFiles
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3D8148B10356;IOData { -> }
//## Uses: <unnamed>%3D8148B40256;MidiOutputDriver { -> F}
//## Uses: <unnamed>%3D8160BD0067;Event { -> }

class NVRAMStore : public ActiveObject  //## Inherits: <unnamed>%3D815F5000BC
{
  //## begin NVRAMStore%3D802415035A.initialDeclarations preserve=yes
  //## end NVRAMStore%3D802415035A.initialDeclarations

  public:
    //## begin NVRAMStore::TaskState%3D816326005A.preface preserve=yes
    //## end NVRAMStore::TaskState%3D816326005A.preface

    //## Class: TaskState%3D816326005A
    //	state that determines whether we are idle, reading,
    //	writing, testing, erasing, read_internal
    //## Category: EngineInterface%3A998EE60122
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {idle, reading, writing, testing, erasing, read_internal} TaskState;

    //## begin NVRAMStore::TaskState%3D816326005A.postscript preserve=yes
    //## end NVRAMStore::TaskState%3D816326005A.postscript

    //## Constructors (generated)
      NVRAMStore();

    //## Destructor (generated)
      ~NVRAMStore();


    //## Other Operations (specified)
      //## Operation: SaveFiles%1031879361
      static bool SaveFiles (const char* path	// The path that the files are located at
      );

      //## Operation: GetNumFiles%1031879362
      static unsigned GetNumFiles ();

      //## Operation: RestoreFiles%1031879363
      static bool RestoreFiles ();

      //## Operation: ReadFiles%1031879364
      bool ReadFiles ();

      //## Operation: ReceiveData%1031879368
      static bool ReceiveData (IOData data);

      //## Operation: run%1031888837
      void run ();

      //## Operation: ProcessTransmitData%1031888840
      void ProcessTransmitData ();

      //## Operation: LoadFiles%1031888841
      static bool LoadFiles (const char* path	// The path that the files are located at
      );

      //## Operation: create%1031960275
      static void create ();

      //## Operation: flush%1031960276
      virtual void flush ();

      //## Operation: IsIdle%1032126395
      static bool IsIdle ();

      //## Operation: ReadHeader%1032126396
      unsigned ReadHeader (char* ret_buf, 	// The buffer where we will be writing the header
      unsigned buf_len	// the size of ret_buf
      );

      //## Operation: TestHeader%1032126397
      unsigned TestHeader (const char* buf, 	// The buffer where we will be writing the header
      unsigned buf_len	// the size of ret_buf
      );

      //## Operation: ProcessInternal%1032171145
      void ProcessInternal ();

      //## Operation: WriteIntEEprom%1032171146
      void WriteIntEEprom ();

      //## Operation: EraseNVRAM%1032171147
      static void EraseNVRAM ();

  public:
    // Additional Public Declarations
      //## begin NVRAMStore%3D802415035A.public preserve=yes
      //## end NVRAMStore%3D802415035A.public

  protected:
    // Additional Protected Declarations
      //## begin NVRAMStore%3D802415035A.protected preserve=yes
      //## end NVRAMStore%3D802415035A.protected

  private:

    //## Other Operations (specified)
      //## Operation: AddByte%1031888838
      bool AddByte (IOData data);

      //## Operation: ProcessReceiveData%1031888839
      void ProcessReceiveData ();

      //## Operation: ProcessTimeout%1045109262
      void ProcessTimeout ();

      //## Operation: WriteHeader%1050531909
      static bool WriteHeader (FILE* fp);

      //## Operation: WriteFiles%1050531910
      static bool WriteFiles (FILE* fp);

      //## Operation: WritePatches%1050531911
      static bool WritePatches (FILE* fp);

      //## Operation: ReadPatches%1050531912
      static bool ReadPatches (FILE* fp, bool doing_test = false);

      //## Operation: ReadFiles%1050531913
      static bool ReadFiles (FILE* fp, bool doing_test = false);

      //## Operation: ReadHeader%1050531914
      static bool ReadHeader (FILE* fp);

      //## Operation: EraseFilesList%1050531915
      static void EraseFilesList ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _header_name%3D8529430164
      //	The data we will stcik on the header so we know we are
      //	dealing with a valid NVRAM
      static const char* get__header_name ();
      static void set__header_name (const char* value);

    // Additional Private Declarations
      //## begin NVRAMStore%3D802415035A.private preserve=yes
      //## end NVRAMStore%3D802415035A.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _num_files%3D8024E40195
      //	The number of FileBlocks that mus be created or have
      //	been created
      //## begin NVRAMStore::_num_files%3D8024E40195.attr preserve=no  private: unsigned {UT} 0
      volatile unsigned  _num_files;
      //## end NVRAMStore::_num_files%3D8024E40195.attr

      //## Attribute: _buffer%3D81614D00FA
      //	A buffer for receiving returned bytes from IO or
      //	buffering before sending
      //## begin NVRAMStore::_buffer%3D81614D00FA.attr preserve=no  private: char [256] {U} 
      char  _buffer[256];
      //## end NVRAMStore::_buffer%3D81614D00FA.attr

      //## Attribute: _buffer_index%3D81618102CC
      //	Index of _buffer
      //## begin NVRAMStore::_buffer_index%3D81618102CC.attr preserve=no  private: unsigned {UT} 0
      volatile unsigned  _buffer_index;
      //## end NVRAMStore::_buffer_index%3D81618102CC.attr

      //## Attribute: _state%3D81627F01CC
      //	state that determines whether we are idle, reading,
      //	writing, testing
      //## begin NVRAMStore::_state%3D81627F01CC.attr preserve=no  private: TaskState {UT} idle
      volatile TaskState  _state;
      //## end NVRAMStore::_state%3D81627F01CC.attr

      //## Attribute: _total_num_bytes%3D8283B400C8
      //	The number of bytes transmitted
      //## begin NVRAMStore::_total_num_bytes%3D8283B400C8.attr preserve=no  private: unsigned {UT} 0
      volatile unsigned  _total_num_bytes;
      //## end NVRAMStore::_total_num_bytes%3D8283B400C8.attr

      //## Attribute: _current_file_index%3D84FF860124
      //	The current index in the list of files that we are
      //	streaming
      //## begin NVRAMStore::_current_file_index%3D84FF860124.attr preserve=no  private: unsigned {UT} 0
      volatile unsigned  _current_file_index;
      //## end NVRAMStore::_current_file_index%3D84FF860124.attr

      //## begin NVRAMStore::_header_name%3D8529430164.attr preserve=no  private: static const char* {U} "SMART"
      static const char* _header_name;
      //## end NVRAMStore::_header_name%3D8529430164.attr

      //## Attribute: _failed%3D852A960220
      //	Flag to indicate whether we are in a failed state during
      //	our read or test
      //## begin NVRAMStore::_failed%3D852A960220.attr preserve=no  private: bool {UT} false
      volatile bool  _failed;
      //## end NVRAMStore::_failed%3D852A960220.attr

      //## Attribute: _internal_NVRAM%3D86211602B5
      //	Copy of the internal NVRAM stored
      //## begin NVRAMStore::_internal_NVRAM%3D86211602B5.attr preserve=no  private: char[256] {UT} 
      volatile char  _internal_NVRAM[256];
      //## end NVRAMStore::_internal_NVRAM%3D86211602B5.attr

      //## Attribute: _num_tx_retries%3D88FB0302B7
      //	The number of attempts made to store the NVRAM
      //## begin NVRAMStore::_num_tx_retries%3D88FB0302B7.attr preserve=no  private: unsigned {UT} 0
      volatile unsigned  _num_tx_retries;
      //## end NVRAMStore::_num_tx_retries%3D88FB0302B7.attr

      //## Attribute: _num_rx_retries%3D88FB3703DE
      //	The number of attempts made to retrieve the NVRAM
      //## begin NVRAMStore::_num_rx_retries%3D88FB3703DE.attr preserve=no  private: unsigned {UT} 0
      volatile unsigned  _num_rx_retries;
      //## end NVRAMStore::_num_rx_retries%3D88FB3703DE.attr

      //## Attribute: _default_path%3D891A410159
      //	The defult path
      //## begin NVRAMStore::_default_path%3D891A410159.attr preserve=no  private: static string {U} ""
      static string _default_path;
      //## end NVRAMStore::_default_path%3D891A410159.attr

    // Data Members for Associations

      //## Association: hal_include::<unnamed>%3D8024C70297
      //## Role: NVRAMStore::FilesList%3D8024C801B3
      //## begin NVRAMStore::FilesList%3D8024C801B3.role preserve=no  public: static FileBlock { -> 0..nVHN}
      static vector <FileBlock> FilesList;
      //## end NVRAMStore::FilesList%3D8024C801B3.role

      //## Association: hal_include::<unnamed>%3D815F6F0002
      //## Role: NVRAMStore::_event%3D815F6F01E3
      //## begin NVRAMStore::_event%3D815F6F01E3.role preserve=no  public: Event { -> 1RFHN}
      Event *_event;
      //## end NVRAMStore::_event%3D815F6F01E3.role

      //## Association: EngineInterface::<unnamed>%3D8276F4030A
      //## Role: NVRAMStore::this_store%3D8276FB0347
      //## begin NVRAMStore::this_store%3D8276FB0347.role preserve=no  private: static NVRAMStore { -> 0..1RFHN}
      static NVRAMStore *this_store;
      //## end NVRAMStore::this_store%3D8276FB0347.role

    // Additional Implementation Declarations
      //## begin NVRAMStore%3D802415035A.implementation preserve=yes
      //## end NVRAMStore%3D802415035A.implementation

};

//## begin NVRAMStore%3D802415035A.postscript preserve=yes
//## end NVRAMStore%3D802415035A.postscript

// Class NVRAMStore 

//## Get and Set Operations for Class Attributes (inline)

inline const char* NVRAMStore::get__header_name ()
{
  //## begin NVRAMStore::get__header_name%3D8529430164.get preserve=no
  return _header_name;
  //## end NVRAMStore::get__header_name%3D8529430164.get
}

inline void NVRAMStore::set__header_name (const char* value)
{
  //## begin NVRAMStore::set__header_name%3D8529430164.set preserve=no
  _header_name = value;
  //## end NVRAMStore::set__header_name%3D8529430164.set
}

//## begin module%3D802415035A.epilog preserve=yes
//## end module%3D802415035A.epilog


#endif
