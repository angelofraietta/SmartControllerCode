//## begin module%3D33598402D3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D33598402D3.cm

//## begin module%3D33598402D3.cp preserve=no
//	Angelo Fraietta
//## end module%3D33598402D3.cp

//## Module: ViewQuestion%3D33598402D3; Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\viewquestion.h

#ifndef viewquestion_h
#define viewquestion_h 1

//## begin module%3D33598402D3.additionalIncludes preserve=no
//## end module%3D33598402D3.additionalIncludes

//## begin module%3D33598402D3.includes preserve=yes
//## end module%3D33598402D3.includes


class SMUtility;
class PresentationQuestion;
class PresentationAnswer;
class ViewAnswer;

//## begin module%3D33598402D3.declarations preserve=no
//## end module%3D33598402D3.declarations

//## begin module%3D33598402D3.additionalDeclarations preserve=yes
//## end module%3D33598402D3.additionalDeclarations


//## begin ViewQuestion%3D33592700C6.preface preserve=yes
//## end ViewQuestion%3D33592700C6.preface

//## Class: ViewQuestion%3D33592700C6; Class Utility
//	Passes parameters about views and objects they contain
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3D3363C801FF;SMUtility { -> F}
//## Uses: calls%3D34A2590383;PresentationQuestion { -> F}
//## Uses: <unnamed>%3D34A3D202EF;ViewAnswer { -> F}
//## Uses: <unnamed>%3D34A4180155;PresentationAnswer { -> F}

class ViewQuestion 
{
  //## begin ViewQuestion%3D33592700C6.initialDeclarations preserve=yes
  //## end ViewQuestion%3D33592700C6.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: GetNumViews%1026777700
      static unsigned GetNumViews (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: GetNumViewObjects%1026777701
      static unsigned GetNumViewObjects (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum);

      //## Operation: GetViewObject%1026777702
      static P_BASESHELL GetViewObject (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum);

      //## Operation: GetViewObjectDisplayParams%1026777703
      static bool GetViewObjectDisplayParams (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum, P_BASESHELL* pObject, unsigned* top, unsigned* left, unsigned* height, unsigned* width, unsigned* tag);

      //## Operation: AddViewObject%1026777704
      static bool AddViewObject (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, P_BASESHELL pObject, unsigned top, unsigned left, unsigned height, unsigned width, unsigned tag);

      //## Operation: ClearView%1026777705
      static bool ClearView (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum);

      //## Operation: GetViewName%1026777708
      static bool GetViewName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, char* ret_name, unsigned buf_len);

      //## Operation: SetViewName%1026777709
      static bool SetViewName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, const char* name);

      //## Operation: ModifyViewObject%1026777710
      static bool ModifyViewObject (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, 	// View number within the patch
      P_BASESHELL pObject, 	// The Baseshell object
      unsigned top, unsigned left, unsigned height, unsigned width, unsigned tag);

      //## Operation: AddView%1026777712
      static unsigned AddView (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: DeleteView%1026777713
      static void DeleteView (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum);

      //## Operation: AddViewConnector%1049496130
      static int AddViewConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, P_CONNECTOR pCon);

      //## Operation: GetNumViewConnectors%1049496131
      static unsigned GetNumViewConnectors (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum);

      //## Operation: GetViewConnector%1049496132
      static P_CONNECTOR GetViewConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum);

      //## Operation: GetViewConnectorValue%1049496133
      static int GetViewConnectorValue (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum, unsigned value_num);

      //## Operation: GetNumViewConnectorValues%1049496134
      static unsigned GetNumViewConnectorValues (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum);

      //## Operation: AddViewConnectorValue%1049496135
      static bool AddViewConnectorValue (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum, int new_value);

    // Additional Public Declarations
      //## begin ViewQuestion%3D33592700C6.public preserve=yes
      //## end ViewQuestion%3D33592700C6.public

  protected:
    // Additional Protected Declarations
      //## begin ViewQuestion%3D33592700C6.protected preserve=yes
      //## end ViewQuestion%3D33592700C6.protected

  private:
    // Additional Private Declarations
      //## begin ViewQuestion%3D33592700C6.private preserve=yes
      //## end ViewQuestion%3D33592700C6.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ViewQuestion%3D33592700C6.implementation preserve=yes
      //## end ViewQuestion%3D33592700C6.implementation

};

//## begin ViewQuestion%3D33592700C6.postscript preserve=yes
//## end ViewQuestion%3D33592700C6.postscript

// Class Utility ViewQuestion 

//## begin module%3D33598402D3.epilog preserve=yes
//## end module%3D33598402D3.epilog


#endif
