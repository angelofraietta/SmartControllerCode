// Source file: C:/develop/JSmartController/src/jsmartcontroller/ObjectsNode.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

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
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
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


/**
   Objects Node contaions list of All MaseShell Nodes
 */
public class ObjectsNode extends PatchTreeNode {
    int _patch;
    int _p_interface;
    boolean _loaded = false;
    PatchForm _patch_form;

    /**
       @roseuid 3E7E69B302DB
     */
    public ObjectsNode(int p_interface, int pPatch, PatchForm patch_form) {
    super ("Objects", patch_form);
    _patch = pPatch;
    _p_interface = p_interface;
    _patch_form = patch_form;

    }

    /**
       @roseuid 3E7E69B302DF
     */
    public BaseShellTreeNode AddBaseShell(int pBaseShell) {
    BaseShellTreeNode pNode;

    if (BaseShell.CanHaveChildren(_p_interface, pBaseShell))
    {
      pNode = new PatchTree (_p_interface, pBaseShell, _patch_form, null);
    }
    else
    {
      pNode = new BaseShellTreeNode (_p_interface, pBaseShell, _patch_form);
    }



    BaseShellHook pHook = new BaseShellHook (_p_interface, pBaseShell);
    pNode.setHook(pHook);
    pHook.SetTreeNode(pNode);
    return pNode;
    }

    /**
       @roseuid 3E7E69B302E1
     */
    public void LoadNode() {
    if (_loaded == false){
      System.out.println ("Loading Object Node");
      int number_objects = Patch.NumberBaseShells(_p_interface, _patch);
      for (int i = 0; i < number_objects; i++)
      {
        int pObject = Patch.FindBaseShell(_p_interface, _patch, i);
        BaseShellTreeNode pNode = this.AddBaseShell(pObject);
        this.add(pNode);
        _patch_form.AddObject(pNode._pHook, pNode);
      }

    }
    }

    /**
       @roseuid 3E7E6C3401B0
     */
    public void ClearAllNodes() {

      int num_nodes = this.getChildCount();

      for (int i = 0; i < num_nodes; i++)
      {
        BaseShellTreeNode BaseshellNode = (BaseShellTreeNode) this.getChildAt(i);
        BaseshellNode.ClearNode();
      }

    }

    /**
       @roseuid 3E7EE64F00A0
     */
    public boolean CanEdit() {
      return false;
    }

    /**
       @roseuid 3E7EE6C502C7
     */
    public String GetDefaultName() {
      return "Objects";
    }
}
