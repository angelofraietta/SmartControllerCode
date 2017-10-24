// Source file: C:/develop/JSmartController/src/jsmartcontroller/PatchTree.java

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


/**
   Tree Node for Patch Objects
 */
public class PatchTree extends BaseShellTreeNode {
    int _patch = 0;
    int _p_interface = 0;
    ObjectsNode _objects_node = null;
    ConnectorsNode _connectors_node = null;
    PatchForm _patch_form = null;
    //DefaultMutableTreeNode _views_node = null;
    DefaultTreeModel _tree_model = null;
    ViewsNode _views_node = null;

    /**
       @roseuid 3E7E69B30361
     */
    public void SetTreeModel(DefaultTreeModel tree_model) {
    _tree_model = tree_model;
    }

    /**
       @roseuid 3E7E69B30363
     */
    public PatchTree(int p_interface, int pPatch, PatchForm patch_form) {
    super (p_interface, pPatch, patch_form);
    _patch = pPatch;
    _p_interface = p_interface;
    _patch_form = patch_form;
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }

    }

    /**
       @roseuid 3E7E69B30367
     */
    public PatchTree(int p_interface, int pPatch, PatchForm patch_form, DefaultTreeModel tree_model) {
    super (p_interface, pPatch, patch_form);
    _tree_model = tree_model;
    _patch = pPatch;
    _p_interface = p_interface;
    _patch_form = patch_form;
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }

    }

    /**
       @roseuid 3E7E69B3036C
     */
    public BaseShellTreeNode AddBaseShell(int pBaseShell) {
    BaseShellTreeNode pNode;

    if (BaseShell.CanHaveChildren(_p_interface, pBaseShell))
    {
      pNode = new PatchTree (_p_interface, pBaseShell, _patch_form, _tree_model);
    }
    else
    {
      pNode = new BaseShellTreeNode (_p_interface, pBaseShell, _patch_form);
    }



    BaseShellHook pHook = new BaseShellHook (_p_interface, pBaseShell);
    pNode.setHook(pHook);
    pHook.SetTreeNode(pNode);

    ObjectsNode pObjectNode = FindObjectNode(pBaseShell);

    if (pObjectNode != null)
    {
      _tree_model.insertNodeInto(pNode, pObjectNode,
                                 pObjectNode.getChildCount());

      _patch_form.AddObject(pHook, pNode);
    }
    return pNode;
    }

    private ObjectsNode FindObjectNode (int pBaseShell){
      ObjectsNode ret = null;
      int pPatch = Identity.GetParent(_p_interface, pBaseShell);
      if (pPatch != _patch)
      {
        BaseShellHook pBaseHook = _patch_form.GetBaseShellHook(pPatch);

        if (pBaseHook != null)
        {
          PatchTree PatchNode = (PatchTree) pBaseHook.GetTreeNode();
          ret = PatchNode._objects_node;
        }
        //System.out.println("Need to find Correct Object Node");
        //ret = _objects_node;
      }
      else
      {
        ret = _objects_node;
      }
      return ret;
    }

    /**
       @roseuid 3E7E69B3036E
     */
    public PatchForm GetPatchForm() {
    return _patch_form;
    }

    /**
       @roseuid 3E7E69B3036F
     */
    private void jbInit() throws Exception {
    _objects_node = new ObjectsNode (_p_interface, _patch, _patch_form);
    _objects_node.LoadNode();

    _connectors_node = new ConnectorsNode (_p_interface, _patch, _patch_form);

    _connectors_node.LoadNode();

    _views_node = new ViewsNode (_p_interface, _patch, _patch_form);
    _views_node.LoadNode();

    if (_tree_model == null)
    {
      this.add(_objects_node);
      this.add(_connectors_node);
      this.add(_views_node);
    }
    else
    {
      _tree_model.insertNodeInto(_objects_node, this,
                                   this.getChildCount());

      _tree_model.insertNodeInto(_connectors_node, this,
                                     this.getChildCount());
      _tree_model.insertNodeInto(_views_node, this,
                                       this.getChildCount());

    }
    }

    /**
       @roseuid 3E7E6D900143
     */
    public void ClearNode() {
      _objects_node.ClearAllNodes();
      _connectors_node.ClearAllNodes();
      _views_node.ClearAllNodes();
      super.ClearNode();
    }

    /**
       Add a connector To Tree
       @roseuid 3E878A43012D
     */
    public ConnectorTreeNode AddConnector(int pCon) {
      ConnectorTreeNode pNode;

      pNode = new ConnectorTreeNode (_p_interface, pCon, _patch_form);



      ConnectorHook pHook = new ConnectorHook (_p_interface, pCon);
      pNode.setHook(pHook);
      pHook.SetTreeNode(pNode);

      _tree_model.insertNodeInto(pNode, _connectors_node,
                                   _connectors_node.getChildCount());

      _patch_form.AddConnector (pHook, pNode);
      return pNode;

    }

    /**
       @roseuid 3F9F4BB703E1
     */
    public boolean DisplayView(int index) {
      return _views_node.DisplayView (index);
    }

    public void AddNewView(){
      ViewTreeNode pNode;
      int view_number = View.GetNumViews(_p_interface, _patch);
      int view_hook = View.AddView(_p_interface, _patch);

      if (view_hook != 0)
      {
        pNode = _views_node.AddView(view_number);

        _tree_model.insertNodeInto(pNode, _views_node,
                                 _views_node.getChildCount());
      }
    }
}
