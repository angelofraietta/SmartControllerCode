// Source file: C:/develop/JSmartController/src/jsmartcontroller/ConnectorHook.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;


public class ConnectorHook extends IdentityHook {
    public ConnectorDisplayForm _pEditform = null;

    /**
       @roseuid 3E8399F80399
     */
    public void DisplayEditForm() {
      if (_pEditform == null)
      {
        _pEditform = new ConnectorDisplayForm (this);
      }
      _pEditform.setVisible(true);
    }

    public void Clear() {
      if (_pEditform != null)
      {
        _pEditform.dispose();
        _pEditform = null;
      }

    }

    /**
       Constructor
       @roseuid 3E839A4601F6
     */
    public ConnectorHook(int presentation, int pObject) {
      super(presentation, pObject);
    }
}
