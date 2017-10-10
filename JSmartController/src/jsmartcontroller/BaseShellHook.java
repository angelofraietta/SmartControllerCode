// Source file: C:/develop/JSmartController/src/jsmartcontroller/BaseShellHook.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import Jni.*;


/**
   Provides a cached interface to BaseShell native methods
 */
public class BaseShellHook extends IdentityHook {
    public volatile BaseShellDisplayForm _pEditform = null;

    /**
       Constructor
       @roseuid 3E78FD460353
     */
    public BaseShellHook(int presentation, int pObject) {
				super(presentation, pObject);
    }

    /**
       If an edit form is displayed, moves to front, otherwise creates an edit form
       @roseuid 3E78FE7A0356
     */
    public void DisplayEditForm() {
      if (_pEditform == null)
      {
        _pEditform = new BaseShellDisplayForm (this);
      }
      _pEditform.setVisible(true);
    }

    /**
       @roseuid 3E7E7B9A019B
     */
    protected void finalize() throws Throwable {
        super.finalize();
    }

    /**
       @roseuid 3E7E7BB1023E
     */
    public void Clear() {
      if (_pEditform != null)
      {
        _pEditform.dispose();
        _pEditform = null;
      }

    }

    /**
       @roseuid 3E9614D102AA
     */
    public String GetAttribute(int index) {
      String ret = "";
      if (this._presentation != 0)
      {
        ret = BaseShell.GetAttribute(_presentation, _pObject, index);
      }
      return ret;

    }

    /**
       @roseuid 3EAE01EC01C2
     */
    public String GetDefaultAttribute() {
      String ret = "";
      if (this._presentation != 0)
      {
        ret = BaseShell.GetDefaultAttribute(_presentation, _pObject);
      }
      return ret;

    }
}
/*
BaseShellHook.SetDefaultAttribute(int,String){
    }

*/
/*
BaseShellHook.SetAttribute(int,String){
      BaseShell.SetAttribute(_presentation, _pObject, index, value);
    }

*/
