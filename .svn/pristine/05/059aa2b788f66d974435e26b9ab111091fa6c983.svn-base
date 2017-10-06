#ifndef VIEW_H
#define VIEW_H

#include "estring.h"
#include "evector.h"



class Patch;

class PatchView: public Identity
{
 public:

	PatchView(Patch* pParent):Identity (pParent, "", "") {}
	~PatchView();

	bool Restore(FILE* infile);

  void ClearView();
  
	unsigned GetNumObjects(){return object_list.size();}
  unsigned GetNumConnectors(){return connector_list.size();}

	const char* GetType()const {return szType;}

	void Save(FILE* outfile);

	void AddObject(BaseShell* pShell,
								 unsigned top, 
								 unsigned left,
								 unsigned height, 
								 unsigned width,
								 unsigned tag);

  bool RemoveObject(BaseShell* pShell);
  
	bool ModifyObject(BaseShell* pShell,
								 unsigned top, 
								 unsigned left,
								 unsigned height, 
								 unsigned width,
								 unsigned tag);
			

	bool GetObjectParams(unsigned index,
											 BaseShell** pShell, 
											 unsigned* top, 
											 unsigned* left,
											 unsigned* height, 
											 unsigned* width,
											 unsigned* tag);
	
// will return a value greater than the number of items if failed
	unsigned GetObjectIndex (BaseShell* pShell);
  unsigned GetConnectorIndex (Connector* pCon);

  int AddConnector(Connector* pCon);
  Connector* GetConnector (unsigned index);

  unsigned GetNumConnectorValues (unsigned index);
  int GetConnectorValue (unsigned index, unsigned value_num);
  bool AddConnectorValue (unsigned index, int value);

	static const char *const StartBlock;

 private:
	// declare nested class
	class ViewObject
		{
			public:

			void Save(FILE*);
			
			bool Restore(Patch* parent, char* input_buffer);

			ViewObject(BaseShell* pShell = NULL, 
												unsigned top = 0, 
												unsigned left = 0,
												unsigned height = 0, 
												unsigned width = 0,
												unsigned tag = 0)
				:_pShell(pShell), _top(top), _left(left), 
				_height(height), _width(width), _tag(tag){}
			
			BaseShell* _pShell;
			unsigned _top, _left, _height, _width, _tag;
			static const char *const StartBlock;
		};

	class ViewConnector	 {
	public:
		ViewConnector(Connector* pCon = NULL):_pCon(pCon){}

    ~ViewConnector (){Clear();}

	  void Save(FILE*);

		bool Restore(Patch* parent, char* input_buffer);

    void AddValue (int i) {_values.push_back (i);}
    unsigned GetNumValues ()const {return _values.size();}

    void Clear () {_values.erase(_values.begin(), _values.end());}
    int GetValue (unsigned index) const
      {
      int i = 0;
      if (index < GetNumValues())
      {
        i = _values[index];
      }
      return i;
      }

		sm_ptr::vector <int> _values;
		static const char *const StartBlock;
		Connector *_pCon;
	}; //end class class ViewConnector

	static const char*const szType;

	sm_ptr::vector<ViewObject> object_list;
  sm_ptr::vector<ViewConnector*> connector_list;
};


#endif
