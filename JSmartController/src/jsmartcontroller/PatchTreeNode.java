// Source file: C:/develop/JSmartController/src/jsmartcontroller/PatchTreeNode.java

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


public abstract class PatchTreeNode extends DefaultMutableTreeNode {
    public PatchForm _patch_form;

    /**
       Constructor taking String to Pass to Default Muytable Tree Node
       @roseuid 3E7EE5DC03DA
     */
    public PatchTreeNode(String name, PatchForm patch_form) {
      super(name);
      _patch_form = patch_form;
    }

    /**
       @roseuid 3E7EE60B014D
     */
    public abstract boolean CanEdit();

    /**
       @roseuid 3E7EE6A500D6
     */
    public abstract String GetDefaultName();
}
