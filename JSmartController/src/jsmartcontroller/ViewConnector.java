// Source file: C:/develop/JSmartController/src/jsmartcontroller/ViewConnector.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.util.Vector;


class IntContainer {
    public int _i;

    /**
       @roseuid 3E922FEA02E9
     */
    public IntContainer(int i) {
      _i = i;
    }
}
/**
   Contains Information about Connectors within View
 */
public class ViewConnector {
    public ConnectorHook _pHook;
    Vector _points_list = new Vector ();

    /**
       Stores View
       @roseuid 3E9225CC0081
     */
    public boolean StoreView(int pQuestion, int dwpPatch, int viewNum) {


      int index = View.AddViewConnector(pQuestion, dwpPatch, viewNum, _pHook._pObject);

      boolean ret = index >= 0;

      if (ret)
      {
        for (int i = 0; i < this._points_list.size(); i++)
        {
          IntContainer iC = (IntContainer)_points_list.get(i);

          if (!View.AddViewConnectorValue(pQuestion, dwpPatch, viewNum, index, iC._i))
          {
            System.out.println("Unable to Add Connector Point");
          }
        }
      }

      return ret;
    }

    /**
       @roseuid 3E9225D5017E
     */
    public void setHook(ConnectorHook pHook) {
      _pHook = pHook;
    }

    /**
       @roseuid 3E922C3100D5
     */
    ViewConnector() {
    }

    /**
       Adds a Value tro the List
       @roseuid 3E922C4D0310
     */
    public void AddValue(int new_val) {
      _points_list.add(new IntContainer(new_val));
    }

    /**
       Clears All Objects in list
       @roseuid 3E922C87027D
     */
    public void Clear() {
      _points_list.clear();
    }

    /**
       @roseuid 3E922E6901AE
     */
    public ViewConnector(ConnectorHook pHook) {
      _pHook = pHook;
    }

    /**
       @roseuid 3E9256160069
     */
    public boolean LoadValues(int pQuestion, int dwpPatch, int viewNum, int connector_index) {
      int num_params = View.GetNumViewConnectorValues(pQuestion, dwpPatch, viewNum, connector_index);

      for (int i = 0; i < num_params; i++)
      {
        int value = View.GetViewConnectorValue(pQuestion, dwpPatch, viewNum, connector_index, i);
        AddValue (value);
      }
      return true;
    }

    /**
       Returns the Value at the index
       @roseuid 3E9263240367
     */
    public int ReadValue(int index) {
      int ret = 0;
      if (index < _points_list.size())
      {
        ret = ((IntContainer)_points_list.get(index))._i;
      }
      return ret;
    }

    /**
       Returns the Number of Values Stored
       @roseuid 3E92686F0384
     */
    public int NumValues() {
      return _points_list.size();
    }
}
