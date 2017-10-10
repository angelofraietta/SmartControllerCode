// Source file: C:/develop/JSmartController/src/jsmartcontroller/ConnectorTreeNode.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import javax.swing.tree.DefaultMutableTreeNode;


public class ConnectorTreeNode extends IdentityTreeNode {
    public ConnectorHook _pHook;

    /**
       @roseuid 3E7EE4D5010C
     */
    ConnectorTreeNode(int presentation, int pObject, PatchForm patch_form) {
      super(presentation, pObject, patch_form);
    }

    /**
       Saves the ConnectorHook
       @roseuid 3E7EEFB60390
     */
    public void setHook(ConnectorHook pHook) {
      _pHook = pHook;
    }

    /**
       @roseuid 3E839EFF0317
     */
    public void ClearNode() {

        ConnectorHook pHook = this._pHook;
        _pHook.Clear();

    }

    /**
       @roseuid 3E87991A0017
     */
    public IdentityHook GetHook() {
      return _pHook;
    }

    public void DisplayMouseClick(){
      // find the BaseShellBox on the active display and set it on Patch Form
      this._patch_form.DisplaySelectedConnectorLine(_pHook);

    }

}
/*
ConnectorTreeNode.ConnectorTreeNode(int,int){
    super(presentation, pObject);
    }

*/
