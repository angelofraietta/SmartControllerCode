//## begin module%3D335A8D0157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D335A8D0157.cm

//## begin module%3D335A8D0157.cp preserve=no
//	Angelo Fraietta
//## end module%3D335A8D0157.cp

//## Module: ViewAnswer%3D335A8D0157; Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\viewanswer.h

#ifndef viewanswer_h
#define viewanswer_h 1

//## begin module%3D335A8D0157.additionalIncludes preserve=no
//## end module%3D335A8D0157.additionalIncludes

//## begin module%3D335A8D0157.includes preserve=yes
//## end module%3D335A8D0157.includes


class SMUtility;
class PatchAnswer;

//## begin module%3D335A8D0157.declarations preserve=no
//## end module%3D335A8D0157.declarations

//## begin module%3D335A8D0157.additionalDeclarations preserve=yes
//## end module%3D335A8D0157.additionalDeclarations


//## begin ViewAnswer%3D335A550193.preface preserve=yes
//## end ViewAnswer%3D335A550193.preface

//## Class: ViewAnswer%3D335A550193; Class Utility
//	Returns view parameters
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3D3363C4029A;SMUtility { -> F}
//## Uses: <unnamed>%3D33640300F6;PatchAnswer { -> F}

class ViewAnswer 
{
  //## begin ViewAnswer%3D335A550193.initialDeclarations preserve=yes
  //## end ViewAnswer%3D335A550193.initialDeclarations

  public:
    //## begin ViewAnswer::pFuncType%3D335B380045.preface preserve=yes
    //## end ViewAnswer::pFuncType%3D335B380045.preface

    //## Class: pFuncType%3D335B380045; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef unsigned (*pfunctype) (const BYTE*, BYTE*, unsigned);
    //## begin ViewAnswer::pFuncType%3D335B380045.postscript preserve=yes
    //## end ViewAnswer::pFuncType%3D335B380045.postscript

    //## begin ViewAnswer::TargetFunc%3D335B3F0316.preface preserve=yes
    //## end ViewAnswer::TargetFunc%3D335B3F0316.preface

    //## Class: TargetFunc%3D335B3F0316; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eGetNumViews, eGetNumViewObjects, eGetViewObject, eGetViewObjectDisplayParams, eAddViewObject, eClearView, eGetViewName, eSetViewName, eModifyViewObject, eAddView, eDeleteView, eAddViewConnector, eGetNumViewConnectors, eGetViewConnector,  eGetViewConnectorValue,  eGetNumViewConnectorValues, eAddViewConnectorValue, eMaxFuncIndex} TargetFunc;

    //## begin ViewAnswer::TargetFunc%3D335B3F0316.postscript preserve=yes
    //## end ViewAnswer::TargetFunc%3D335B3F0316.postscript


    //## Other Operations (specified)
      //## Operation: PerformOperation%1026777693
      static unsigned PerformOperation (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

  public:
    // Additional Public Declarations
      //## begin ViewAnswer%3D335A550193.public preserve=yes
      //## end ViewAnswer%3D335A550193.public

  protected:
    // Additional Protected Declarations
      //## begin ViewAnswer%3D335A550193.protected preserve=yes
      //## end ViewAnswer%3D335A550193.protected

  private:

    //## Other Operations (specified)
      //## Operation: GetNumViews%1026777694; C++
      static unsigned GetNumViews (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumViewObjects%1026777695; C++
      static unsigned GetNumViewObjects (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetViewObject%1026777696; C++
      static unsigned GetViewObject (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetViewObjectDisplayParams%1026777697; C++
      static unsigned GetViewObjectDisplayParams (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddViewObject%1026777698; C++
      static unsigned AddViewObject (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: ClearView%1026777699; C++
      static unsigned ClearView (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetViewName%1026777706; C++
      static unsigned GetViewName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetViewName%1026777707; C++
      static unsigned SetViewName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddView%1026777714; C++
      static unsigned AddView (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: DeleteView%1026777715; C++
      static unsigned DeleteView (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddViewConnector%1049496124
      static unsigned AddViewConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumViewConnectors%1049496125
      static unsigned GetNumViewConnectors (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetViewConnector%1049496126
      static unsigned GetViewConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetViewConnectorValue%1049496127
      static unsigned GetViewConnectorValue (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumViewConnectorValues%1049496128
      static unsigned GetNumViewConnectorValues (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: ModifyViewObject%1026777711; C++
      static unsigned ModifyViewObject (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddViewConnectorValue%1049496129; C++
      static unsigned AddViewConnectorValue (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

    // Additional Private Declarations
      //## begin ViewAnswer%3D335A550193.private preserve=yes
      //## end ViewAnswer%3D335A550193.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pFunc%3D33613C01BB
      //	Static array of member functions
      //## begin ViewAnswer::pFunc%3D33613C01BB.attr preserve=no  private: static ViewAnswer::pfunctype [eMaxFuncIndex] {U} {GetNumViews, GetNumViewObjects, GetViewObject, GetViewObjectDisplayParams, AddViewObject, ClearView, GetViewName, SetViewName, ModifyViewObject, AddView, DeleteView, AddViewConnector, GetNumViewConnectors, GetViewConnector,  GetViewConnectorValue,  GetNumViewConnectorValues, AddViewConnectorValue}
      static ViewAnswer::pfunctype  pFunc[eMaxFuncIndex];
      //## end ViewAnswer::pFunc%3D33613C01BB.attr

    // Additional Implementation Declarations
      //## begin ViewAnswer%3D335A550193.implementation preserve=yes
      //## end ViewAnswer%3D335A550193.implementation

};

//## begin ViewAnswer%3D335A550193.postscript preserve=yes
//## end ViewAnswer%3D335A550193.postscript

// Class Utility ViewAnswer 

//## begin module%3D335A8D0157.epilog preserve=yes
//## end module%3D335A8D0157.epilog


#endif
