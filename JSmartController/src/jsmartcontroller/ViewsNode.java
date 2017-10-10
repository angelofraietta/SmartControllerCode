// Source file: C:/develop/JSmartController/src/jsmartcontroller/ViewsNode.java

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
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import Jni.*;


/**
   Tree Node for Holding Views
 */
public class ViewsNode extends PatchTreeNode {
    int _patch;
    int _p_interface;
    boolean _expanded = false;

    /**
       @roseuid 3E7EE4D5027E
     */
    public ViewsNode(int p_interface, int pPatch, PatchForm patch_form) {
      super ("Views", patch_form);
      _patch = pPatch;
      _p_interface = p_interface;

    }

    /**
       @roseuid 3E7EE666028E
     */
    public boolean CanEdit() {
      return false;
    }

    /**
       @roseuid 3E7EE6DE02EB
     */
    public String GetDefaultName() {
      return "Views";
    }

    /**
       @roseuid 3E88E5AB0299
     */
    public void LoadNode() {
      System.out.println ("Loading Views Node");
      int number_views = View.GetNumViews(_p_interface, _patch);
      for (int i = 0; i < number_views; i++)
      {
        this.add(this.AddView(i));
      }

    }
/*
    public void AddNewView(){
      int number_views = View.GetNumViews(_p_interface, _patch);
      this.add(this.AddView(number_views));

    }
 */
    /**
       @roseuid 3E88E5AB02AD
     */
    public void ClearAllNodes() {
      int num_nodes = this.getChildCount();

      for (int i = 0; i < num_nodes; i++)
      {
        ViewTreeNode pNode = (ViewTreeNode) this.getChildAt(i);
        ViewHook pHook = pNode._pHook;
        pHook.ClearView();
      }

    }

    public boolean DisplayView (int index){
      boolean ret = false;

      if (index < this.getChildCount())
      {
        ViewTreeNode pNode = (ViewTreeNode) this.getChildAt(index);
        ViewHook pHook = pNode._pHook;

        if (pHook != null)
        {
          pHook.DisplayEditForm();
          ret = true;
        }
      }
      return ret;
    }

    /**
       Adds A View
       @roseuid 3E88EACE00EC
     */
    public ViewTreeNode AddView(int index) {
      ViewHook pHook = new ViewHook(_p_interface, _patch, index, _patch_form);
      ViewTreeNode pNode = new ViewTreeNode (_p_interface, _patch, pHook, _patch_form);
      pHook.SetTreeNode(pNode);
      return pNode;
    }

    /**
       Returns True if Object can has Been removed
       @roseuid 3E891A4302FE
     */
    public void RemoveObject(BaseShellHook pObject) {
      // iterate through views and delete object
      int num_nodes = this.getChildCount();

      for (int i = 0; i < num_nodes; i++)
      {
        ViewTreeNode pNode = (ViewTreeNode) this.getChildAt(i);
        pNode.RemoveObject(pObject);
      }

    }

    /**
       Returns True if a Connector is removed
       @roseuid 3E891A440088
     */
    public void RemoveConnector(ConnectorHook pCon) {
      // iterate through views and delete Connector
      int num_nodes = this.getChildCount();

      for (int i = 0; i < num_nodes; i++)
      {
        ViewTreeNode pNode = (ViewTreeNode) this.getChildAt(i);
        pNode.RemoveConnector(pCon);
      }


    }
}
