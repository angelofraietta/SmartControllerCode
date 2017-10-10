// Source file: C:/develop/JSmartController/src/jsmartcontroller/IdentityTreeNode.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

/**
   Tree node of Leaf or Patch Trees
 */
public abstract class IdentityTreeNode extends PatchTreeNode {

    /**
       @roseuid 3E7EEDB10044
     */
    public boolean CanEdit() {
      return true;
    }

    /**
       @roseuid 3E7EEDB1004E
     */
    public String GetDefaultName() {
      return GetHook().getName();
    }

    /**
       @roseuid 3E7EEDE50306
     */
    public IdentityTreeNode(int presentation, int pIdentity, PatchForm patch_form) {
      super (Identity.GetName (presentation, pIdentity), patch_form);
    }

    /**
       @roseuid 3E8798F60323
     */
    public abstract IdentityHook GetHook();

    /**
       @roseuid 3E88F361007A
     */
    public IdentityTreeNode(String name, PatchForm patch_form) {
      super (name, patch_form);
    }

    // function overriden by sub classes
    public void DisplayMouseClick(){}
}
/*
IdentityTreeNode.IdentityTreeNode(String){
      super (name);
    }

*/
/*
IdentityTreeNode.IdentityTreeNode(int,int){
      super (Identity.GetName (presentation, pIdentity));
    }

*/
