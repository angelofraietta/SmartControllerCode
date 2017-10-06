//## begin module%40FF3E6801CE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40FF3E6801CE.cm

//## begin module%40FF3E6801CE.cp preserve=no
//	Angelo Fraietta
//## end module%40FF3E6801CE.cp

//## Module: OSCArg%40FF3E6801CE; Pseudo Package specification
//## Subsystem: engine%39F51CB901B8
//## Source file: D:\develop\smartcontroller\controller\source\engine\oscarg.h

#ifndef oscarg_h
#define oscarg_h 1

//## begin module%40FF3E6801CE.additionalIncludes preserve=no
//## end module%40FF3E6801CE.additionalIncludes

//## begin module%40FF3E6801CE.includes preserve=yes
//## end module%40FF3E6801CE.includes

//## begin module%40FF3E6801CE.additionalDeclarations preserve=yes
//## end module%40FF3E6801CE.additionalDeclarations


//## begin OSCArg%40FF3E6801CE.preface preserve=yes
//## end OSCArg%40FF3E6801CE.preface

//## Class: OSCArg%40FF3E6801CE
//	Contains arguments that we can use for OSC Messages
//	Contains a Union that is not shown in the diagram
//## Category: engine%39F4C4E2005F
//## Subsystem: engine%39F51CB901B8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class OSCArg 
{
  //## begin OSCArg%40FF3E6801CE.initialDeclarations preserve=yes
  //## end OSCArg%40FF3E6801CE.initialDeclarations

  public:
    //## begin OSCArg::arg_type%40FF3EA90131.preface preserve=yes
    //## end OSCArg::arg_type%40FF3EA90131.preface

    //## Class: arg_type%40FF3EA90131
    //## Category: engine%39F4C4E2005F
    //## Subsystem: engine%39F51CB901B8
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eUndefined, eTick, eInt, eFloat, eString} arg_type;

    //## begin OSCArg::arg_type%40FF3EA90131.postscript preserve=yes
    //## end OSCArg::arg_type%40FF3EA90131.postscript

    //## Constructors (generated)
      OSCArg();


    //## Other Operations (specified)
      //## Operation: SetVal%1090469976
      bool SetVal ();

      //## Operation: SetVal%1090469973
      bool SetVal (int arg);

      //## Operation: SetVal%1090469974
      bool SetVal (const char* arg);

      //## Operation: SetVal%1090469975
      bool SetVal (float arg);

      //## Operation: ClearVal%1090469977
      void ClearVal ();

    // Data Members for Class Attributes

      //## Attribute: _arg_type%40FF3FB80076
      //	Contains the argument type contained in hidden union
      //## begin OSCArg::_arg_type%40FF3FB80076.attr preserve=no  public: arg_type {U} eUndefined
      arg_type _arg_type;
      //## end OSCArg::_arg_type%40FF3FB80076.attr

  public:
    // Additional Public Declarations
      //## begin OSCArg%40FF3E6801CE.public preserve=yes
      union
      {
        float f;
        int i;
        const char* s;
      };
      //## end OSCArg%40FF3E6801CE.public
  protected:
    // Additional Protected Declarations
      //## begin OSCArg%40FF3E6801CE.protected preserve=yes
      //## end OSCArg%40FF3E6801CE.protected

  private:
    // Additional Private Declarations
      //## begin OSCArg%40FF3E6801CE.private preserve=yes
      //## end OSCArg%40FF3E6801CE.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin OSCArg%40FF3E6801CE.implementation preserve=yes
      //## end OSCArg%40FF3E6801CE.implementation

};

//## begin OSCArg%40FF3E6801CE.postscript preserve=yes
//## end OSCArg%40FF3E6801CE.postscript

// Class OSCArg 

inline OSCArg::OSCArg()
  //## begin OSCArg::OSCArg%.hasinit preserve=no
      : _arg_type(eUndefined)
  //## end OSCArg::OSCArg%.hasinit
  //## begin OSCArg::OSCArg%.initialization preserve=yes
  //## end OSCArg::OSCArg%.initialization
{
  //## begin OSCArg::OSCArg%.body preserve=yes
  //## end OSCArg::OSCArg%.body
}



//## Other Operations (inline)
//## Operation: SetVal%1090469976
inline bool OSCArg::SetVal ()
{
  _arg_type = eTick;

  //## begin OSCArg::SetVal%1090469976.body preserve=yes
  //## end OSCArg::SetVal%1090469976.body
}

//## Operation: SetVal%1090469973
inline bool OSCArg::SetVal (int arg)
{
  //## begin OSCArg::SetVal%1090469973.body preserve=yes
  i = arg;
  _arg_type = eInt;
  //## end OSCArg::SetVal%1090469973.body
}

//## Operation: SetVal%1090469974
inline bool OSCArg::SetVal (const char* arg)
{
  //## begin OSCArg::SetVal%1090469974.body preserve=yes
  s = arg;
  _arg_type = eString;
  //## end OSCArg::SetVal%1090469974.body
}

//## Operation: SetVal%1090469975
inline bool OSCArg::SetVal (float arg)
{
  //## begin OSCArg::SetVal%1090469975.body preserve=yes
  f = arg;
  _arg_type = eFloat;
  //## end OSCArg::SetVal%1090469975.body
}

//## Operation: ClearVal%1090469977
inline void OSCArg::ClearVal ()
{
  _arg_type = eUndefined;

  //## begin OSCArg::ClearVal%1090469977.body preserve=yes
  //## end OSCArg::ClearVal%1090469977.body
}

//## begin module%40FF3E6801CE.epilog preserve=yes
//## end module%40FF3E6801CE.epilog


#endif
