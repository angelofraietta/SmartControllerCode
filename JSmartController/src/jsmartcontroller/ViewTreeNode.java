// Source file: C:/develop/JSmartController/src/jsmartcontroller/ViewTreeNode.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

/**
   Sigle View Node
 */
public class ViewTreeNode extends IdentityTreeNode {
    public ViewHook _pHook;

    /**
       @roseuid 3E88E0A00134
     */
    public ViewTreeNode(int presentation, int pObject, PatchForm patch_form) {
      super(presentation, pObject, patch_form);
    }

    /**
       @roseuid 3E88E15701E2
     */
    public IdentityHook GetHook() {
      return _pHook;
    }

    /**
       Stores The ViewHook into the Node
       @roseuid 3E88EEC5007D
     */
    public void setHook(ViewHook pHook) {
      _pHook = pHook;
    }

    /**
       @roseuid 3E88F28003B5
     */
    public ViewTreeNode(int presentation, int pObject, ViewHook pHook, PatchForm patch_form) {
      super(pHook.getName(), patch_form);
      _pHook = pHook;
    }

    /**
       Returns True if Object can has Been removed
       @roseuid 3E891B980196
     */
    public void RemoveObject(BaseShellHook pObject) {
      _pHook.RemoveObject(pObject);
    }

    /**
       Returns True if a Connector is removed
       @roseuid 3E891B9801B4
     */
    public void RemoveConnector(ConnectorHook pCon) {
      _pHook.RemoveConnector(pCon);
    }
}
