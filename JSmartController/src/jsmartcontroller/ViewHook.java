// Source file: C:/develop/JSmartController/src/jsmartcontroller/ViewHook.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.util.*;



/**
   Contains Information About Performance Views
 */
public class ViewHook extends IdentityHook {
    private boolean _initialised = false;
    /**
       The Index Within The Patch
     */
    private int _index;
    private String _viewName = null;
    public PatchForm _patch_form;
    TreeMap _object_map = new TreeMap ();
    /**
       A ViewHook Displays the objects on a ViewForm
     */
    public ViewForm _view_form;
    TreeMap _connector_map = new TreeMap ();

    /**
       Sets the Name in both the cached an the underlying name
       @roseuid 3E88DCE001D4
     */
    public void setName(String value) {
      _viewName = value;
      View.SetViewName(this._presentation, this._pObject, this._index, _viewName);
    }

    /**
       Sets the Comment in both the cached an the underlying comment
       @roseuid 3E88DCE001DE
     */
    public void setComment(String value) {
    }

    /**
       Returns the Name. If the Name is empty, returns the native value
       @roseuid 3E88DCE001E8
     */
    public String getName() {
      if (_viewName == null)
      {
        _viewName = View.GetViewName(this._presentation, this._pObject, this._index);
      }

      return _viewName;
    }

    /**
       Returns the Comment. If the Comment is empty, returns the native value
       @roseuid 3E88DCE001F2
     */
    public String getComment() {
      return "";
    }

    /**
       Returns the Type. If the Type is empty, returns the native value
       @roseuid 3E88DCE001FC
     */
    public String getType() {
      return "Performance View";
    }

    /**
       @roseuid 3E88DCE00206
     */
    public void DisplayEditForm() {
      LoadView();

      if (_view_form == null)
      {
        _view_form = _patch_form.AddViewForm(this);
      }

      if (_view_form != null)
      {
        Set key_set = _object_map.entrySet();
        Iterator iter = key_set.iterator();

        while (iter.hasNext())
        {
          ViewObject pView = (ViewObject) ((java.util.Map.Entry) iter.next()).getValue();
          _view_form.AddObject(pView);
        }
        _view_form.update();

      }

    }

    /**
       Constructor
       @roseuid 3E88DD330151
     */
    public ViewHook(int presentation, int pObject, int index, PatchForm patch_form) {
      super(presentation, pObject);
      _index = index;
      _patch_form = patch_form;
    }

    /**
       Returns True if Object can be added
       @roseuid 3E88DDD701D9
     */
    public boolean CanAdd(BaseShellHook pObject) {
      return true;
    }

    /**
       Returns True if Object can has Been Added
       @roseuid 3E88DE07026F
     */
    public boolean AddObject(BaseShellHook pObject) {
      return true;
    }

    /**
       Returns True if Object can has Been Added
       @roseuid 3E8CC849003E
     */
    public boolean AddObject(BaseShellHook pObject, ViewObject pViewObject) {
      boolean ret = false;

      if (!_object_map.containsValue(pObject))
      {
        _object_map.put(pObject, pViewObject);
        ret = true;
      }
      return ret;
    }

    /**
       Returns True if Object can has Been removed
       @roseuid 3E88DE2703BF
     */
    public boolean RemoveObject(BaseShellHook pObject) {
      boolean ret = false;
      // find and remove Object
      if (_object_map.containsKey(pObject))
      {
        _object_map.remove(pObject);
        ret = true;
      }

      if (_view_form != null)
      {
        boolean removed = _view_form.RemoveObject (pObject);
        ret |= removed;
      }

      return ret;
    }

    /**
       Returns True if a Connector is added
       @roseuid 3E88DE5A03C2
     */
    public boolean AddConnector(ConnectorHook pCon) {
      return true;
    }

    /**
       Returns True if a Connector is added
       @roseuid 3E9232E0039C
     */
    public boolean AddConnector(ConnectorHook pCon, ViewConnector pView) {
      boolean ret = false;

      if (!_connector_map.containsValue(pCon))
      {
        _connector_map.put(pCon, pView);
        ret = true;
      }
      return ret;

    }

    /**
       Returns True if a Connector is removed
       @roseuid 3E88DE860004
     */
    public boolean RemoveConnector(ConnectorHook pCon) {
      if (_view_form != null)
      {
        _view_form.RemoveConnector(pCon);
      }
      return true;
    }

    /**
       Clears View
       @roseuid 3E88DEB50106
     */
    public void ClearView() {
      _object_map.clear();
      _connector_map.clear();
      if (_view_form != null)
      {
        _view_form.HideObjectList();
      }
    }

    /**
       Loads View if Not initialised
       @roseuid 3E88FA300008
     */
    public void LoadView() {
      if (!_initialised)
      {
        int num_objects = View.GetNumViewObjects(this._presentation, this._pObject, this._index);

        for (int i = 0; i < num_objects; i++)
        {
          ViewObject view_object = new ViewObject();
          // Read the parameters for the view
          if (view_object.GetViewObjectDisplayParams(this._presentation, this._pObject, this._index, i))
          {
            //view_object.Print();
            BaseShellHook pHook = _patch_form.GetBaseShellHook(view_object.dwpShell);

            if (pHook != null)
            {
              view_object.setHook(pHook);
              AddObject (pHook, view_object);
            }
          }
        }

        int num_connectors = View.GetNumViewConnectors(this._presentation, this._pObject, this._index);
        for (int i = 0; i < num_connectors; i++)
        {
          int connector = View.GetViewConnector(_presentation, _pObject, _index, i);
          ConnectorHook pHook = this._patch_form.GetConnectorHook(connector);
          if (pHook != null)
          {
            ViewConnector pConView = new ViewConnector(pHook);
            pConView.LoadValues(_presentation, _pObject, _index, i);
            this.AddConnector(pHook, pConView);
          }
        }


        _initialised = true;
      }
    }

    /**
       Saves The view
       @roseuid 3E921D1D017F
     */
    public boolean SaveView() {
      boolean ret = true;

      View.ClearView(this._presentation, this._pObject, this._index);
      Set key_set = _object_map.entrySet();
      Iterator iter = key_set.iterator();

      while (iter.hasNext()) {
        ViewObject pView = (ViewObject) ((java.util.Map.Entry) iter.next()).getValue();
        ret &= pView.StoreView (this._presentation, this._pObject, this._index);
      }

      key_set = _connector_map.entrySet();
      iter = key_set.iterator();

      while (iter.hasNext()) {
        ViewConnector pView = (ViewConnector) ((java.util.Map.Entry) iter.next()).getValue();
        ret &= pView.StoreView (this._presentation, this._pObject, this._index);
      }

      return ret;
    }

    /**
       Returns a View Connector if exists in its connector map
       @roseuid 3E925987028C
     */
    public ViewConnector GetViewConnector(ConnectorHook pCon) {
      ViewConnector pView = null;

      if (_connector_map.containsKey(pCon))
      {
        pView = (ViewConnector)_connector_map.get(pCon);
      }
      return pView;
    }
}
