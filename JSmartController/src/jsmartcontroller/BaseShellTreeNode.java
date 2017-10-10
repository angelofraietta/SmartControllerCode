// Source file: C:/develop/JSmartController/src/jsmartcontroller/BaseShellTreeNode.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import Jni.*;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import Jni.*;


public class BaseShellTreeNode extends IdentityTreeNode {
    public BaseShellHook _pHook;

    /**
       Constructor
       @roseuid 3E79010A02EB
     */
    public BaseShellTreeNode(int presentation, int pObject, PatchForm patch_form) {
      super (presentation, pObject, patch_form);
    }

    /**
       Saves the BaseShellHook
       @roseuid 3E79023603BF
     */
    public void setHook(BaseShellHook pHook) {
      _pHook = pHook;
    }

    /**
       @roseuid 3E7E6D5D010D
     */
    public void ClearNode() {
      BaseShellHook pHook = this._pHook;
      _pHook.Clear();
    }

    /**
       @roseuid 3E879912000C
     */
    public IdentityHook GetHook() {
      return _pHook;
    }

    public void DisplayMouseClick(){
      // find the BaseShellBox on the active display and set it on Patch Form
      this._patch_form.SetSelectedBaseShellHook(_pHook);

    }
}
/*
BaseShellTreeNode.BaseShellTreeNode(int,int){
				super (presentation, pObject);
    }

*/
