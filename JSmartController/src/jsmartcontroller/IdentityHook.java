// Source file: C:/develop/JSmartController/src/jsmartcontroller/IdentityHook.java

package jsmartcontroller;

import Jni.Identity;

import javax.swing.*;
import javax.swing.*;
import java.lang.*;
import Jni.Identity;


/**
   Provides a cached interface to Identity native methods
 */
public abstract class IdentityHook implements Comparable {
    /**
       The Presentation Interface required for JNI Input
     */
    protected int _presentation;
    /**
       key for underlying Jni object
     */
    protected int _pObject;
    /**
       Cached Name of Underlying Object
     */
    private String _Name;
    /**
       Cached Commet of Underlying Object
     */
    private String _Comment;
    /**
       Cached Type of Underlying Object
     */
    private String _Type = null;

    private IdentityTreeNode _tree_node = null;
    /**
       Constructor
       @roseuid 3E78EBFB0041
     */
    public IdentityHook(int presentation, int pObject) {
      _presentation = presentation;
      _pObject = pObject;
    }

    public void SetTreeNode (IdentityTreeNode node){
      _tree_node = node;
    }

    public IdentityTreeNode GetTreeNode(){
      return _tree_node;
    }

    public PatchForm GetPatchForm(){
      PatchForm ret = null;
      if (_tree_node != null)
      {
        ret = ((PatchTree)_tree_node.getRoot())._patch_form;
      }

      return ret;
    }
    /**
       Sets the Name in both the cached an the underlying name
       @roseuid 3E78E2E303BE
     */
    public void setName(String value) {
      _Name = value;
      Identity.SetName (_presentation, _pObject, _Name);
      if (_tree_node != null)
      {
        _tree_node.setUserObject(_Name);
        ((PatchTree)_tree_node.getRoot())._patch_form.jTree1.repaint();
      }
    }

    /**
       Sets the Comment in both the cached an the underlying comment
       @roseuid 3E78E30F01F5
     */
    public void setComment(String value) {
      _Comment = value;
      Identity.SetComment (_presentation, _pObject, _Comment);


    }

    /**
       Returns the Name. If the Name is empty, returns the native value
       @roseuid 3E78E32E002D
     */
    public String getName() {
      if (_Name == null)
      {
        _Name = Identity.GetName (_presentation, _pObject);
      }
      return _Name;
    }

    /**
       Returns the Comment. If the Comment is empty, returns the native value
       @roseuid 3E78E36502F3
     */
    public String getComment() {
      if (_Comment == null)
      {
        _Comment = Identity.GetComment (_presentation, _pObject);
      }
      return _Comment;

    }

    /**
       Returns the Type. If the Type is empty, returns the native value
       @roseuid 3E78E3670075
     */
    public String getType() {
      if (_Type == null)
      {
        _Type = Identity.GetType (_presentation, _pObject);
      }
      return _Type;

    }

    /**
       @roseuid 3E7E7B9A01F8
     */
    protected void finalize() throws Throwable {
        super.finalize();
    }

    /**
       @roseuid 3E7EF57D0152
     */
    public abstract void DisplayEditForm();

    /**
       @roseuid 3E837E92016C
     */
    public int compareTo(Object other) {
      IdentityHook right = (IdentityHook) other;
      return _pObject - right._pObject;
    }

    /**
       @roseuid 3E8CFE8E0270
     */
    public void Print() {
      System.out.println(this._pObject);
    }
}
