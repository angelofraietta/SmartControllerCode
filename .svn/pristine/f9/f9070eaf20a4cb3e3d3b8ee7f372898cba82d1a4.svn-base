//## begin module%3D80249300BC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D80249300BC.cm

//## begin module%3D80249300BC.cp preserve=no
//	Angelo Fraietta
//## end module%3D80249300BC.cp

//## Module: FileBlock%3D80249300BC; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\fileblock.h

#ifndef fileblock_h
#define fileblock_h 1

//## begin module%3D80249300BC.additionalIncludes preserve=no
//## end module%3D80249300BC.additionalIncludes

//## begin module%3D80249300BC.includes preserve=yes
//## end module%3D80249300BC.includes

//## begin module%3D80249300BC.additionalDeclarations preserve=yes
//## end module%3D80249300BC.additionalDeclarations


//## begin FileBlock%3D80249300BC.preface preserve=yes
//## end FileBlock%3D80249300BC.preface

//## Class: FileBlock%3D80249300BC
//	Information About the File. This class is used to stream
//	the file to and from the file system
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class FileBlock 
{
  //## begin FileBlock%3D80249300BC.initialDeclarations preserve=yes
  //## end FileBlock%3D80249300BC.initialDeclarations

  public:
    //## begin FileBlock::StreamState%3D84FD2C00CE.preface preserve=yes
    //## end FileBlock::StreamState%3D84FD2C00CE.preface

    //## Class: StreamState%3D84FD2C00CE
    //	The current state of the class.
    //	init, name, data_len, data, crc, complete
    //## Category: EngineInterface%3A998EE60122
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {init, name, data_len, data, crc, complete} StreamState;

    //## begin FileBlock::StreamState%3D84FD2C00CE.postscript preserve=yes
    //## end FileBlock::StreamState%3D84FD2C00CE.postscript

    //## Constructors (generated)
      FileBlock(const FileBlock &right);

    //## Constructors (specified)
      //## Operation: FileBlock%1031879365
      FileBlock (const char* filename = "");

    //## Destructor (generated)
      ~FileBlock();


    //## Other Operations (specified)
      //## Operation: GetFileLength%1031879367
      unsigned GetFileLength ();

      //## Operation: ReadBytes%1032126385
      unsigned ReadBytes (char* ret_buf, 	// return buffer
      unsigned buf_len	// The length of the buffer
      );

      //## Operation: WriteBytes%1032126386
      unsigned WriteBytes (const char* buf, 	// data buffer
      unsigned buf_len, 	// The length of the buffer
      bool write_to_file = true	// Flag to indicate whether we are only testing or
      	// actually writing to filesystem
      );

      //## Operation: Complete%1032126388
      bool Complete ();

      //## Operation: FreeResources%1032171143
      void FreeResources ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _failed%3D85441A0060
      //	Flag to determine whether restore or test has failed
      const bool Failed () const;

  public:
    // Additional Public Declarations
      //## begin FileBlock%3D80249300BC.public preserve=yes
      //## end FileBlock%3D80249300BC.public

  protected:
    // Additional Protected Declarations
      //## begin FileBlock%3D80249300BC.protected preserve=yes
      //## end FileBlock%3D80249300BC.protected

  private:

    //## Other Operations (specified)
      //## Operation: WriteFilenameBytes%1032126389
      unsigned WriteFilenameBytes (const char* buf, 	// data buffer
      unsigned buf_len, 	// The length of the buffer
      bool testing = false	// Flag to indicate whether we are only testing or
      	// actually writing to filesystem
      );

      //## Operation: WriteDataBytes%1032126390
      unsigned WriteDataBytes (const char* buf, 	// data buffer
      unsigned buf_len, 	// The length of the buffer
      bool testing = false	// Flag to indicate whether we are only testing or
      	// actually writing to filesystem
      );

      //## Operation: WriteCRCBytes%1032126391
      unsigned WriteCRCBytes (const char* buf, 	// data buffer
      unsigned buf_len, 	// The length of the buffer
      bool testing = false	// Flag to indicate whether we are only testing or
      	// actually writing to filesystem
      );

      //## Operation: ReadFilenameBytes%1032126392
      unsigned ReadFilenameBytes (char* ret_buf, 	// data buffer
      unsigned buf_len	// The length of the buffer
      );

      //## Operation: ReadDataBytes%1032126393
      unsigned ReadDataBytes (char* ret_buf, 	// data buffer
      unsigned buf_len	// The length of the buffer
      );

      //## Operation: ReadCRCBytes%1032126394
      unsigned ReadCRCBytes (char* ret_buf, 	// data buffer
      unsigned buf_len	// The length of the buffer
      );

      //## Operation: WriteDataLenBytes%1032126398
      unsigned WriteDataLenBytes (const char* buf, 	// data buffer
      unsigned buf_len, 	// The length of the buffer
      bool testing = false	// Flag to indicate whether we are only testing or
      	// actually writing to filesystem
      );

      //## Operation: ReadDataLenBytes%1032126399
      unsigned ReadDataLenBytes (char* ret_buf, 	// data buffer
      unsigned buf_len	// The length of the buffer
      );

      //## Operation: NextState%1032171144
      void NextState ();

    // Additional Private Declarations
      //## begin FileBlock%3D80249300BC.private preserve=yes
      //## end FileBlock%3D80249300BC.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _filename%3D8025530004
      //	Null terminated string. Reaching the Null defines end of
      //	string
      //## begin FileBlock::_filename%3D8025530004.attr preserve=no  private: string {U} 
      string _filename;
      //## end FileBlock::_filename%3D8025530004.attr

      //## Attribute: _file_length%3D80259000DE
      //	The Number of data byes in the file
      //## begin FileBlock::_file_length%3D80259000DE.attr preserve=no  private: unsigned {U} 
      unsigned _file_length;
      //## end FileBlock::_file_length%3D80259000DE.attr

      //## Attribute: data%3D8025670319
      //	the data on the file. No member is generated as it is
      //	read from the file
      //## begin FileBlock::data%3D8025670319.attr preserve=no  private: void {U} 
      //## end FileBlock::data%3D8025670319.attr

      //## Attribute: _CRC%3D802572008A
      //	4 byte CRC on data
      //## begin FileBlock::_CRC%3D802572008A.attr preserve=no  private: unsigned long {U} 0xFFFFFFFF
      unsigned long _CRC;
      //## end FileBlock::_CRC%3D802572008A.attr

      //## Attribute: _temp_buf%3D84FC9B00E3
      //	A temporary buffer for storing incomplete information
      //	that has been streamed
      //## begin FileBlock::_temp_buf%3D84FC9B00E3.attr preserve=no  private: char* {U} 0
      char* _temp_buf;
      //## end FileBlock::_temp_buf%3D84FC9B00E3.attr

      //## Attribute: _index%3D84FCD70284
      //	A running index for the current byte number in the
      //	current state
      //## begin FileBlock::_index%3D84FCD70284.attr preserve=no  private: unsigned {U} 0
      unsigned _index;
      //## end FileBlock::_index%3D84FCD70284.attr

      //## Attribute: _state%3D84FD980336
      //## begin FileBlock::_state%3D84FD980336.attr preserve=no  private: StreamState {U} init
      StreamState _state;
      //## end FileBlock::_state%3D84FD980336.attr

      //## Attribute: _name_length%3D84FE4000B7
      //	The Number of data byes in the file
      //## begin FileBlock::_name_length%3D84FE4000B7.attr preserve=no  private: unsigned {U} 
      unsigned _name_length;
      //## end FileBlock::_name_length%3D84FE4000B7.attr

      //## Attribute: _fp%3D85106E01E5
      //	File pointer to data
      //## begin FileBlock::_fp%3D85106E01E5.attr preserve=no  private: FILE* {U} 0
      FILE* _fp;
      //## end FileBlock::_fp%3D85106E01E5.attr

      //## begin FileBlock::_failed%3D85441A0060.attr preserve=no  public: bool {U} false
      bool _failed;
      //## end FileBlock::_failed%3D85441A0060.attr

    // Additional Implementation Declarations
      //## begin FileBlock%3D80249300BC.implementation preserve=yes
      //## end FileBlock%3D80249300BC.implementation

};

//## begin FileBlock%3D80249300BC.postscript preserve=yes
//## end FileBlock%3D80249300BC.postscript

// Class FileBlock 


//## Other Operations (inline)
//## Operation: NextState%1032171144
//	Increments State
inline void FileBlock::NextState ()
{
  int state = (int)_state;
  state++;
  _state = (StreamState)state;

  //## begin FileBlock::NextState%1032171144.body preserve=yes
  //## end FileBlock::NextState%1032171144.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const bool FileBlock::Failed () const
{
  //## begin FileBlock::Failed%3D85441A0060.get preserve=no
  return _failed;
  //## end FileBlock::Failed%3D85441A0060.get
}

//## begin module%3D80249300BC.epilog preserve=yes
//## end module%3D80249300BC.epilog


#endif
