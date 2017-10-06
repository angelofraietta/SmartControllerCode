//## begin module%3AC3CDD102E2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC3CDD102E2.cm

//## begin module%3AC3CDD102E2.cp preserve=no
//	Angelo Fraietta
//## end module%3AC3CDD102E2.cp

//## Module: SessionInterface%3AC3CDD102E2; Package specification
//	presentation question and answer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\sessioninterface.h

#ifndef sessioninterface_h
#define sessioninterface_h 1

//## begin module%3AC3CDD102E2.additionalIncludes preserve=no
//## end module%3AC3CDD102E2.additionalIncludes

//## begin module%3AC3CDD102E2.includes preserve=yes
//## end module%3AC3CDD102E2.includes


class SMUtility;
class QuestionTask;
class PresentationAnswer;
class SimulatorAnswer;
class NetworkLayer;

//## begin module%3AC3CDD102E2.declarations preserve=no
//## end module%3AC3CDD102E2.declarations

//## begin module%3AC3CDD102E2.additionalDeclarations preserve=yes
//## end module%3AC3CDD102E2.additionalDeclarations


//## begin SessionQuestion%3AA8170C00F6.preface preserve=yes
//## end SessionQuestion%3AA8170C00F6.preface

//## Class: SessionQuestion%3AA8170C00F6; Abstract
//	Superclass for the Session Layer Question Types. Passes
//	messages between the Presentation Question and
//	Presentation Answer.
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC3F70F0320;SMUtility { -> F}

class SessionQuestion 
{
  //## begin SessionQuestion%3AA8170C00F6.initialDeclarations preserve=yes
  //## end SessionQuestion%3AA8170C00F6.initialDeclarations

  public:
    //## Destructor (generated)
      virtual ~SessionQuestion();


    //## Other Operations (specified)
      //## Operation: AskQuestion%985819687
      virtual bool AskQuestion (const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      unsigned q_size, 	// Size of the question
      BYTE* ret_answer, 	// This is where the answer to the question will be placed.
      unsigned r_size, 	// Maximum allowed size of answer
      unsigned timeout = 2000	// The amount of toime to wait
      ) = 0;

      //## Operation: create%985819688
      static SessionQuestion* create (const char* name, DWORD port_speed	// The speed at which to open the port
      );

      //## Operation: destroy%985819711
      static void destroy (SessionQuestion* pLayer);

      //## Operation: createfile%1022540283
      static SessionQuestion* createfile (const char* file_name);

      //## Operation: SetInterfaceAddress%1082670128
      virtual bool SetInterfaceAddress (const char* address);

    // Data Members for Class Attributes

      //## Attribute: simulator_name%3AC3EAF30387
      //## begin SessionQuestion::simulator_name%3AC3EAF30387.attr preserve=no  public: static const char*const {V} "simulator"
      static const char*const simulator_name;
      //## end SessionQuestion::simulator_name%3AC3EAF30387.attr

    // Additional Public Declarations
      //## begin SessionQuestion%3AA8170C00F6.public preserve=yes
      //## end SessionQuestion%3AA8170C00F6.public

  protected:
    // Additional Protected Declarations
      //## begin SessionQuestion%3AA8170C00F6.protected preserve=yes
      //## end SessionQuestion%3AA8170C00F6.protected

  private:
    // Additional Private Declarations
      //## begin SessionQuestion%3AA8170C00F6.private preserve=yes
      //## end SessionQuestion%3AA8170C00F6.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin SessionQuestion%3AA8170C00F6.implementation preserve=yes
      //## end SessionQuestion%3AA8170C00F6.implementation

};

//## begin SessionQuestion%3AA8170C00F6.postscript preserve=yes
//## end SessionQuestion%3AA8170C00F6.postscript

//## begin SimulatorQuestion%3AC0144D0183.preface preserve=yes
//## end SimulatorQuestion%3AC0144D0183.preface

//## Class: SimulatorQuestion%3AC0144D0183
//	The question is part of the Simulator and therefore uses
//	function calls to the engine simulator library
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class SimulatorQuestion : public SessionQuestion  //## Inherits: <unnamed>%3AC0159300FF
{
  //## begin SimulatorQuestion%3AC0144D0183.initialDeclarations preserve=yes
  //## end SimulatorQuestion%3AC0144D0183.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: initialise%985819710
      bool initialise ();

      //## Operation: AskQuestion%985819712
      bool AskQuestion (const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      unsigned q_size, 	// Size of the question
      BYTE* ret_answer, 	// This is where the answer to the question will be placed.
      unsigned r_size, 	// Maximum allowed size of answer
      unsigned timeout = 2000	// The amount of toime to wait
      );

    // Additional Public Declarations
      //## begin SimulatorQuestion%3AC0144D0183.public preserve=yes
      //## end SimulatorQuestion%3AC0144D0183.public

  protected:
    // Additional Protected Declarations
      //## begin SimulatorQuestion%3AC0144D0183.protected preserve=yes
      //## end SimulatorQuestion%3AC0144D0183.protected

  private:
    // Additional Private Declarations
      //## begin SimulatorQuestion%3AC0144D0183.private preserve=yes
      //## end SimulatorQuestion%3AC0144D0183.private

  private: //## implementation
    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3AC272FC0268
      //## Role: SimulatorQuestion::<the_SimulatorAnswer>%3AC272FD009D
      //## begin SimulatorQuestion::<the_SimulatorAnswer>%3AC272FD009D.role preserve=no  public: SimulatorAnswer { -> RFHN}
      //## end SimulatorQuestion::<the_SimulatorAnswer>%3AC272FD009D.role

    // Additional Implementation Declarations
      //## begin SimulatorQuestion%3AC0144D0183.implementation preserve=yes
      //## end SimulatorQuestion%3AC0144D0183.implementation

};

//## begin SimulatorQuestion%3AC0144D0183.postscript preserve=yes
//## end SimulatorQuestion%3AC0144D0183.postscript

//## begin StreamedQuestion%3AC015A10069.preface preserve=yes
//## end StreamedQuestion%3AC015A10069.preface

//## Class: StreamedQuestion%3AC015A10069
//	The question must travel through some sort of stream
//	through to a serial device
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class StreamedQuestion : public SessionQuestion  //## Inherits: <unnamed>%3AC0161A0104
{
  //## begin StreamedQuestion%3AC015A10069.initialDeclarations preserve=yes
  //## end StreamedQuestion%3AC015A10069.initialDeclarations

  public:
    //## Constructors (generated)
      StreamedQuestion();

    //## Destructor (generated)
      virtual ~StreamedQuestion();


    //## Other Operations (specified)
      //## Operation: open%985819699
      bool open (const char* dev_name, 	// name to pass to lower layer
      DWORD port_speed	// The speed at which to open the port
      );

      //## Operation: AskQuestion%985819713
      bool AskQuestion (const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      unsigned q_size, 	// Size of the question
      BYTE* ret_answer, 	// This is where the answer to the question will be placed.
      unsigned r_size, 	// Maximum allowed size of answer
      unsigned timeout = 2000	// The amount of toime to wait
      );

      //## Operation: GetAnswer%1023147568
      bool GetAnswer ();

      //## Operation: SetInterfaceAddress%1082670127
      virtual bool SetInterfaceAddress (const char* address);

      //## Operation: Flush%1083901316
      void Flush ();

    // Additional Public Declarations
      //## begin StreamedQuestion%3AC015A10069.public preserve=yes
      //## end StreamedQuestion%3AC015A10069.public

  protected:
    // Additional Protected Declarations
      //## begin StreamedQuestion%3AC015A10069.protected preserve=yes
      //## end StreamedQuestion%3AC015A10069.protected

  private:
    // Additional Private Declarations
      //## begin StreamedQuestion%3AC015A10069.private preserve=yes
      //## end StreamedQuestion%3AC015A10069.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _return_result%3CFC0B850349
      //	return result caused by receiving from separate thread
      //## begin StreamedQuestion::_return_result%3CFC0B850349.attr preserve=no  private: bool {UT} 
      volatile bool  _return_result;
      //## end StreamedQuestion::_return_result%3CFC0B850349.attr

      //## Attribute: _bytes_read%3CFC0C5C02D0
      //	The number of bytes returned from ;ower lay question
      //## begin StreamedQuestion::_bytes_read%3CFC0C5C02D0.attr preserve=no  private: DWORD {UT} 0
      volatile DWORD  _bytes_read;
      //## end StreamedQuestion::_bytes_read%3CFC0C5C02D0.attr

      //## Attribute: _answer_buf%3CFC0C8A00B9
      //## begin StreamedQuestion::_answer_buf%3CFC0C8A00B9.attr preserve=no  private: BYTE* {U} 
      BYTE* _answer_buf;
      //## end StreamedQuestion::_answer_buf%3CFC0C8A00B9.attr

    // Data Members for Associations

      //## Association: EngineInterface::Question::<unnamed>%3CFC02EF01CC
      //## Role: StreamedQuestion::_pThread%3CFC02F00048
      //## begin StreamedQuestion::_pThread%3CFC02F00048.role preserve=no  public: QuestionTask {1 -> 1RFHN}
      QuestionTask *_pThread;
      //## end StreamedQuestion::_pThread%3CFC02F00048.role

      //## Association: EngineInterface::Question::<unnamed>%40857F0D01B5
      //## Role: StreamedQuestion::_lower_layer%40857F0D030D
      //## begin StreamedQuestion::_lower_layer%40857F0D030D.role preserve=no  public: NetworkLayer { -> RFHN}
      NetworkLayer *_lower_layer;
      //## end StreamedQuestion::_lower_layer%40857F0D030D.role

    // Additional Implementation Declarations
      //## begin StreamedQuestion%3AC015A10069.implementation preserve=yes
      //## end StreamedQuestion%3AC015A10069.implementation

};

//## begin StreamedQuestion%3AC015A10069.postscript preserve=yes
//## end StreamedQuestion%3AC015A10069.postscript

//## begin SimulatorAnswer%3AC01654026F.preface preserve=yes
//## end SimulatorAnswer%3AC01654026F.preface

//## Class: SimulatorAnswer%3AC01654026F; Class Utility
//	The Answer is part of the simulator, and therfore exists
//	on the PatchEditor machine.
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class SimulatorAnswer 
{
  //## begin SimulatorAnswer%3AC01654026F.initialDeclarations preserve=yes
  //## end SimulatorAnswer%3AC01654026F.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: GetAnswer%985819692
      static bool GetAnswer (const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      BYTE* ret_answer	// This is where the answer to the question will be placed.
      );

    // Additional Public Declarations
      //## begin SimulatorAnswer%3AC01654026F.public preserve=yes
      //## end SimulatorAnswer%3AC01654026F.public

  protected:
    // Additional Protected Declarations
      //## begin SimulatorAnswer%3AC01654026F.protected preserve=yes
      //## end SimulatorAnswer%3AC01654026F.protected

  private:
    // Additional Private Declarations
      //## begin SimulatorAnswer%3AC01654026F.private preserve=yes
      //## end SimulatorAnswer%3AC01654026F.private

  private: //## implementation
    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3AEE4E4D02C3
      //## Role: SimulatorAnswer::_presentation%3AEE4E4E015C
      //## begin SimulatorAnswer::_presentation%3AEE4E4E015C.role preserve=no  public: PresentationAnswer { -> 1VFHN}
      static PresentationAnswer _presentation;
      //## end SimulatorAnswer::_presentation%3AEE4E4E015C.role

    // Additional Implementation Declarations
      //## begin SimulatorAnswer%3AC01654026F.implementation preserve=yes
      //## end SimulatorAnswer%3AC01654026F.implementation

};

//## begin SimulatorAnswer%3AC01654026F.postscript preserve=yes
//## end SimulatorAnswer%3AC01654026F.postscript

//## begin StreamedAnswer%3AC0172700EC.preface preserve=yes
//## end StreamedAnswer%3AC0172700EC.preface

//## Class: StreamedAnswer%3AC0172700EC
//	The Answer must be passed back through a lower layer.
//	The lower layers will pass the answer to the Patch
//	Editor through some sort of serial device.
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class StreamedAnswer 
{
  //## begin StreamedAnswer%3AC0172700EC.initialDeclarations preserve=yes
  //## end StreamedAnswer%3AC0172700EC.initialDeclarations

  public:
    //## Constructors (generated)
      StreamedAnswer();

    //## Destructor (generated)
      ~StreamedAnswer();


    //## Other Operations (specified)
      //## Operation: GetQuestion%985819700
      unsigned GetQuestion (const BYTE** question	// This is the buffer where the question will be written to
      );

      //## Operation: open%985819701
      bool open (const char* name, 	// the name of the stream to open
      DWORD port_speed, 	// The speed at which to open the port
      unsigned buf_size	// The size of the buffer to maintain
      );

      //## Operation: SendAnswer%992232178
      unsigned SendAnswer (const BYTE* answer, 	// The buffer containing the answer
      unsigned answer_size	// the number of Bytes in the answer
      );

      //## Operation: close%992232179
      void close ();

      //## Operation: SendRaw%1044915131
      unsigned SendRaw (const BYTE* answer, 	// The buffer containing the answer
      unsigned answer_size	// the number of Bytes in the answer
      );

    // Additional Public Declarations
      //## begin StreamedAnswer%3AC0172700EC.public preserve=yes
      //## end StreamedAnswer%3AC0172700EC.public

  protected:
    // Additional Protected Declarations
      //## begin StreamedAnswer%3AC0172700EC.protected preserve=yes
      //## end StreamedAnswer%3AC0172700EC.protected

  private:
    // Additional Private Declarations
      //## begin StreamedAnswer%3AC0172700EC.private preserve=yes
      //## end StreamedAnswer%3AC0172700EC.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _buf%3B27F1D102D5
      //	Internal buffer maintained by this class. it is used to
      //	initialise and read from the link layer
      //## begin StreamedAnswer::_buf%3B27F1D102D5.attr preserve=no  private: BYTE* {U} NULL
      BYTE* _buf;
      //## end StreamedAnswer::_buf%3B27F1D102D5.attr

      //## Attribute: _buf_size%3B27F40000A8
      //## begin StreamedAnswer::_buf_size%3B27F40000A8.attr preserve=no  private: unsigned {U} 0
      unsigned _buf_size;
      //## end StreamedAnswer::_buf_size%3B27F40000A8.attr

    // Data Members for Associations

      //## Association: EngineInterface::Answer::<unnamed>%40857DDC034B
      //## Role: StreamedAnswer::_lower_layer%40857DDD01A6
      //## begin StreamedAnswer::_lower_layer%40857DDD01A6.role preserve=no  public: NetworkLayer { -> RFHN}
      NetworkLayer *_lower_layer;
      //## end StreamedAnswer::_lower_layer%40857DDD01A6.role

    // Additional Implementation Declarations
      //## begin StreamedAnswer%3AC0172700EC.implementation preserve=yes
      //## end StreamedAnswer%3AC0172700EC.implementation

};

//## begin StreamedAnswer%3AC0172700EC.postscript preserve=yes
//## end StreamedAnswer%3AC0172700EC.postscript

// Class SessionQuestion 

inline SessionQuestion::~SessionQuestion()
{
  //## begin SessionQuestion::~SessionQuestion%.body preserve=yes
  //## end SessionQuestion::~SessionQuestion%.body
}



//## Other Operations (inline)
//## Operation: SetInterfaceAddress%1082670128
//	Sets the Interface address of network Layer
inline bool SessionQuestion::SetInterfaceAddress (const char* address)
{
  return false;

  //## begin SessionQuestion::SetInterfaceAddress%1082670128.body preserve=yes
  //## end SessionQuestion::SetInterfaceAddress%1082670128.body
}

// Class SimulatorQuestion 

// Class StreamedQuestion 

// Class Utility SimulatorAnswer 

// Class StreamedAnswer 

//## begin module%3AC3CDD102E2.epilog preserve=yes
//## end module%3AC3CDD102E2.epilog


#endif
