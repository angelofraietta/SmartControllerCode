// Source file: C:/develop/JSmartController/src/jsmartcontroller/BaseShellBox.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import ViewForms.Graphics.*;



class BaseShellBox_RemoveFromViewMenu_actionAdapter implements ActionListener {
    BaseShellBox adaptee;

    /**
       @roseuid 3E9606070300
     */
    BaseShellBox_RemoveFromViewMenu_actionAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E9606070302
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.RemoveFromViewMenu_actionPerformed(e);
    }
}
class BaseShellBox_EditObjectMenu_actionAdapter implements ActionListener {
    BaseShellBox adaptee;

    /**
       @roseuid 3E8D055C0245
     */
    BaseShellBox_EditObjectMenu_actionAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8D055C0247
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.EditObjectMenu_actionPerformed(e);
    }
}
class BaseShellBox_DeleteFromPatchMenu_actionAdapter implements ActionListener {
    BaseShellBox adaptee;

    /**
       @roseuid 3E8D055C0275
     */
    BaseShellBox_DeleteFromPatchMenu_actionAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8D055C0277
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.DeleteFromPatchMenu_actionPerformed(e);
    }
}
class BaseShellBox_ResetObjectMenu_actionAdapter implements ActionListener {
    BaseShellBox adaptee;

    /**
       @roseuid 3E8D055C0261
     */
    BaseShellBox_ResetObjectMenu_actionAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8D055C0263
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.ResetObjectMenu_actionPerformed(e);
    }
}
class BaseShellBox_this_mouseAdapter extends MouseAdapter {
    BaseShellBox adaptee;

    /**
       @roseuid 3E8D055C0231
     */
    BaseShellBox_this_mouseAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8D055C0233
     */
    public void mousePressed(MouseEvent e) {
    adaptee.this_mousePressed(e);
    }

    /**
       @roseuid 3E8D055C0235
     */
    public void mouseReleased(MouseEvent e) {
    adaptee.this_mouseReleased(e);
    }

    /**
       @roseuid 3E96060701FF
     */
    public void mouseExited(MouseEvent e) {
    adaptee.this_mouseExited(e);
    }

    /**
       @roseuid 3EB1F1740239
     */
    public void mouseClicked(MouseEvent e) {
    adaptee.this_mouseClicked(e);
    }
}
/**
   Represents a BaseShell
 */
public class BaseShellBox extends CObjectBox {
    boolean _resizing = false;
    static boolean _disable_resize = true;
    static boolean _force_update = false;

    public BaseShellHook _pHook;
    JPopupMenu ObjectPopupMenu = new JPopupMenu ();
    JMenuItem EditObjectMenu = new JMenuItem ();
    JMenuItem ResetObjectMenu = new JMenuItem ();
    JMenuItem RemoveFromViewMenu = new JMenuItem ();
    JMenuItem DeleteFromPatchMenu = new JMenuItem ();
    String cached_attribute = null;
    boolean _disable_update = true;
   JCheckBoxMenuItem mnuAutoUpdate = new JCheckBoxMenuItem();


    /**
       Creates a BaseShellBox
       @roseuid 3E83C83E013A
     */

    public static void DisableResize (boolean disable ){
      _disable_resize = disable;
    }
    public static boolean DisableResize (){
      return _disable_resize;
    }

    public static void ForceUpdate (boolean force){
      _force_update = force;
    }

    public static boolean ForceUpdate (){
      return _force_update;
    }

    public void DisableUpdate (boolean disable ){
      _disable_update = disable;
    }
    public  boolean DisableUpdate (){
      return _disable_update;
    }

    public static BaseShellBox create(ViewFormPanel parent, BaseShellHook pHook) {
      return new BaseShellBox(parent, pHook);
    }

    /**
       Constructor
       @roseuid 3E83C8C601D5
     */
    public BaseShellBox(ViewFormPanel parent, BaseShellHook pHook) {
      super(parent);
      try {
          jbInit();
        }
        catch(Exception e) {
          e.printStackTrace();
        }

      _pHook = pHook;

      for (int i = 0; i < BaseShell.GetNumInlets(_pHook._presentation, _pHook._pObject); i++)
      {
        BaseShellInlet pInlet = new BaseShellInlet (this, i, pHook);
        this.AddFollower(pInlet);
      }

      for (int i = 0; i < BaseShell.GetNumOutlets(_pHook._presentation, _pHook._pObject); i++)
      {
        BaseShellOutlet pOutlet = new BaseShellOutlet (this, i, pHook);
        this.AddFollower(pOutlet);
      }

      notifyFollowers();
    }

    public void AdjustSize(){
      if (BaseShell.CanChangeSize(_pHook._presentation, _pHook._pObject))
      {
        int new_num_outlets = BaseShell.GetNumOutlets(_pHook._presentation, _pHook._pObject);
        int current_num_outlets = this._bottomFollowers.size();
        if (new_num_outlets != current_num_outlets)
        {
          for (int i = current_num_outlets ; i < new_num_outlets; i++)
          {
            BaseShellOutlet pOutlet = new BaseShellOutlet (this, i, _pHook);
            this.AddFollower(pOutlet);
          }

          System.out.println("Adjust number Outlets");
        }
        int new_num_inlets = BaseShell.GetNumInlets(_pHook._presentation, _pHook._pObject);
        int current_num_inlets = this._topFollowers.size();
        if (new_num_inlets != current_num_inlets)
        {
          System.out.println("Adjust number Inlets");
          for (int i = current_num_inlets ; i < new_num_inlets; i++)
          {
            BaseShellInlet pInlet = new BaseShellInlet (this, i, _pHook);
            this.AddFollower(pInlet);
          }

        }

        notifyFollowers();
      }
    }
    /**
       Virtual method which returns the string that must be wriiten in the box
       @roseuid 3E83C904015C
     */
    public String GetText() {
      String ret = null;

      PatchForm pForm = GetPatchForm();

      if (pForm.DisplayValues())
      {
        if (cached_attribute == null ||
            ! _disable_update || _force_update || GetHighlighted())
        {
          cached_attribute = _pHook.GetDefaultAttribute();
        }

        ret = cached_attribute;
      }
      else if (pForm.DisplayTypes())
      {
        ret = _pHook.getType();
      }
      else
      {
        ret = _pHook.getName();
      }

      if (ret == null)
      {
        ret = "";
      }
      return ret;
    }

    /**
       @roseuid 3E8D055C00DA
     */
    private void jbInit() throws Exception {
    this.addMouseListener(new BaseShellBox_this_mouseAdapter(this));
    EditObjectMenu.setText("Edit Object");
    EditObjectMenu.addActionListener(new BaseShellBox_EditObjectMenu_actionAdapter(this));
    ResetObjectMenu.setText("Reset Object");
    ResetObjectMenu.addActionListener(new BaseShellBox_ResetObjectMenu_actionAdapter(this));
    RemoveFromViewMenu.setText("Remove From View");
    RemoveFromViewMenu.addActionListener(new BaseShellBox_RemoveFromViewMenu_actionAdapter(this));
    DeleteFromPatchMenu.setText("Delete From Patch");
    DeleteFromPatchMenu.addActionListener(new BaseShellBox_DeleteFromPatchMenu_actionAdapter(this));
    this.addMouseMotionListener(new BaseShellBox_this_mouseMotionAdapter(this));
    mnuAutoUpdate.setToolTipText("Causes Object value to allways be updated");
    mnuAutoUpdate.setText("Automatic Update");
    mnuAutoUpdate.setState(false);
    mnuAutoUpdate.addActionListener(new BaseShellBox_mnuAutoUpdate_actionAdapter(this));
    ObjectPopupMenu.addComponentListener(new BaseShellBox_ObjectPopupMenu_componentAdapter(this));
    ObjectPopupMenu.setDefaultLightWeightPopupEnabled(false);
    ObjectPopupMenu.add(EditObjectMenu);
    ObjectPopupMenu.add(ResetObjectMenu);
    ObjectPopupMenu.add(mnuAutoUpdate);
    ObjectPopupMenu.add(RemoveFromViewMenu);
    ObjectPopupMenu.addSeparator();
    ObjectPopupMenu.add(DeleteFromPatchMenu);
    }

    /**
       @roseuid 3E8D055C00EE
     */
    void this_mousePressed(MouseEvent e) {
      _resizing = IsInResizePosition (e.getX(), e.getY()) && !_disable_resize;
      if (e.isPopupTrigger())
      {
        ObjectPopupMenu.show(e.getComponent(),
                             e.getX(), e.getY());
      }

    }

    /**
       @roseuid 3E8D055C0120
     */
    void this_mouseReleased(MouseEvent e) {
    CompleteDrag();
    if (e.isPopupTrigger())
    {
      ObjectPopupMenu.show(e.getComponent(),
                           e.getX(), e.getY());
    }

    }

    /**
       @roseuid 3E8D055C0166
     */
    void EditObjectMenu_actionPerformed(ActionEvent e) {
    this._pHook.DisplayEditForm();
    }

    /**
       @roseuid 3E8D055C01A2
     */
    void ResetObjectMenu_actionPerformed(ActionEvent e) {
      BaseShell.Reset(_pHook._presentation, _pHook._pObject);
    }

    /**
       @roseuid 3E8D055C01D4
     */
    void DeleteFromPatchMenu_actionPerformed(ActionEvent e) {
    ViewForm pViewForm = (ViewForm) this._parent;
    PatchForm parent_form = pViewForm._patch_form;
    parent_form.DeleteObject(_pHook);
    }

    /**
       Returns The BaseShell Outlet At a Given Index
       @roseuid 3E8D04D40139
     */
    public BaseShellOutlet GetBottom(int index) {
      BaseShellOutlet ret = null;
      if (index < this._bottomFollowers.size())
      {
        ret = (BaseShellOutlet)_bottomFollowers.get(index);
      }
      return ret;
    }

    /**
       Returns The BaseShell Inlet At a Given Index
       @roseuid 3E8D049D0252
     */
    public BaseShellInlet GetTop(int index) {
      BaseShellInlet ret = null;

      if (index < this._topFollowers.size())
      {
        ret = (BaseShellInlet)_topFollowers.get(index);
      }
      return ret;
    }

    /**
       @roseuid 3E9606070243
     */
    public boolean IsResizing() {
      return _resizing;
    }

    /**
       @roseuid 3E9606070257
     */
    private boolean IsInResizePosition(int x, int y) {
      int x_thresh = boxSize.width / 2;
      int y_thresh = boxSize.height / 2;
      return x >=  x_thresh && y >= y_thresh;
    }

    /**
       @roseuid 3E96060702A6
     */
    void RemoveFromViewMenu_actionPerformed(ActionEvent e) {
    ((ViewForm)_parent).RemoveObject(this._pHook);

    }

    /**
       @roseuid 3E96060702BA
     */
    void this_mouseExited(MouseEvent e) {
    setCursor(Cursor.getDefaultCursor());
    }

    /**
       @roseuid 3E96060702C5
     */
    void this_mouseMoved(MouseEvent e) {
    if (IsInResizePosition(e.getX(), e.getY()) && !_disable_resize)
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.SE_RESIZE_CURSOR));
    }
    else
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
    }
    }

    /**
       Returns the PatchForm for this object
       @roseuid 3E961327033D
     */
    public PatchForm GetPatchForm() {
      PatchForm ret = null;
      if (this._parent != null)
      {
        ret = ((ViewForm)_parent)._patch_form;
      }

      return ret;
    }

    /**
       @roseuid 3EB1F175022C
     */
    void this_mouseClicked(MouseEvent e) {
      SetHighlighted(!GetHighlighted());
      invalidate();
      if (GetHighlighted())
      {
        GetPatchForm().SetSelectedObject(this);
      }
      else
      {
        GetPatchForm().SetSelectedObject(null);
      }
      if (GetPatchForm().DisplayValues())
      {
        BaseShell.Send(_pHook._presentation, _pHook._pObject);
      }
    }

    /**
       Method that Change has been made.
       Methos called by superclass
       @roseuid 3EB1FB2B02B3
     */
    public void NotifyChange() {
      GetPatchForm().SetModified();
    }

  void mnuAutoUpdate_actionPerformed(ActionEvent e) {
    this.DisableUpdate(!this.DisableUpdate());
    mnuAutoUpdate.setState(!this.DisableUpdate());
  }

  void ObjectPopupMenu_componentShown(ComponentEvent e) {
    mnuAutoUpdate.setState(!this.DisableUpdate());
  }
}
class BaseShellBox_this_mouseMotionAdapter extends MouseMotionAdapter {
    BaseShellBox adaptee;

    /**
       @roseuid 3E960607030B
     */
    BaseShellBox_this_mouseMotionAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E9606070315
     */
    public void mouseMoved(MouseEvent e) {
    adaptee.this_mouseMoved(e);
    }
}

class BaseShellBox_mnuAutoUpdate_actionAdapter implements java.awt.event.ActionListener {
  BaseShellBox adaptee;

  BaseShellBox_mnuAutoUpdate_actionAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuAutoUpdate_actionPerformed(e);
  }
}

class BaseShellBox_ObjectPopupMenu_componentAdapter extends java.awt.event.ComponentAdapter {
  BaseShellBox adaptee;

  BaseShellBox_ObjectPopupMenu_componentAdapter(BaseShellBox adaptee) {
    this.adaptee = adaptee;
  }
  public void componentShown(ComponentEvent e) {
    adaptee.ObjectPopupMenu_componentShown(e);
  }
}
