// Source file: C:/develop/JSmartController/src/jsmartcontroller/ConnectorsNode.java

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


/**
 * <p>Title: Smart Controller</p>
 * <p>Description: Smart Controller Patch Editor and Simulator</p>
 * <p>Copyright: Copyright (c) 2003 Angelo Fraietta</p>
 * <p>Company: Angelo Fraietta</p>
 * @author Angelo Fraietta
 * @version 1.0
 */
public class ConnectorsNode extends PatchTreeNode {
    int _patch;
    int _p_interface;
    boolean _expanded = false;

    /**
       @roseuid 3E7EE4D500DA
     */
    public ConnectorsNode(int p_interface, int pPatch, PatchForm patch_form) {
      super ("Connectors", patch_form);
      _patch = pPatch;
      _p_interface = p_interface;

    }

    /**
       @roseuid 3E7EE66D03E3
     */
    public boolean CanEdit() {
      return false;
    }

    /**
       @roseuid 3E7EE6E2019C
     */
    public String GetDefaultName() {
      return "Connectors";
    }

    /**
       @roseuid 3E88E59C00DF
     */
    public void LoadNode() {
      System.out.println ("Loading Connector Node");
      int number_cons = Patch.NumberConnectors(_p_interface, _patch);
      for (int i = 0; i < number_cons; i++)
      {
        int pObject = Patch.FindConnector(_p_interface, _patch, i);
        ConnectorTreeNode pNode = this.AddConnector(pObject);
        if (pNode != null)
        {
          this.add(pNode);

          _patch_form.AddConnector(pNode._pHook, pNode);
        }
      }

    }

    /**
       @roseuid 3E88E59C00FD
     */
    public void ClearAllNodes() {
      int num_nodes = this.getChildCount();

      for (int i = 0; i < num_nodes; i++)
      {
        ConnectorTreeNode TreelNode = (ConnectorTreeNode) this.getChildAt(i);
        TreelNode.ClearNode();
      }

    }

    /**
       returns ConnectorTreeNode
       @roseuid 3E88EA0503E6
     */
    public ConnectorTreeNode AddConnector(int pCon) {
      ConnectorTreeNode pNode;

      pNode = new ConnectorTreeNode (_p_interface, pCon, _patch_form);



      ConnectorHook pHook = new ConnectorHook (_p_interface, pCon);
      pNode.setHook(pHook);
      pHook.SetTreeNode(pNode);
      return pNode;

    }
}
/*
ConnectorsNode.ConnectorsNode(int,int){
    super ("Connectors");
    _patch = pPatch;
    _p_interface = p_interface;

    }

*/
