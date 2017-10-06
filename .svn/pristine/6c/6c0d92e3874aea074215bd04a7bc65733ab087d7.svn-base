#ifndef CONECTAD_H
#define CONECTAD_H



// ConnectorMessage informs inlets and outlets that connector wants to
// connect or disconnect

class Connector; // forward declaration


class ConnectorMessage {
 public:
  bool	fJoin:1; 			// true if Making Connection, false if disconnecting
  bool  fToInlet:1;		// true if Calling Inlet, false if calling Outlet
  unsigned wSocketNumber; // The Socket Number that is being connected to
  Connector* pCon; // The Address of the Connector
  
};

#endif
