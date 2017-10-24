// Source file: C:/develop/JSmartController/src/jsmartcontroller/ViewForm.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import java.util.*;
import ViewForms.Graphics.*;


public class ViewForm extends ViewFormPanel {
    public int _patch;
    public PatchForm _patch_form;
    /**
       A ViewHook Displays the objects on a ViewForm
     */
    public ViewHook _view_hook;
    TreeMap _object_map = new TreeMap ();
    TreeMap _connector_map = new TreeMap ();
    JPopupMenu ViewPopup = new JPopupMenu ();
    JMenuItem CreateObjectMenu = new JMenuItem ();
    Point _mouse_pos;
    Iterator _update_iterator;
    ObjectsList _object_list = null;

    /**
       @roseuid 3E8778C702F4
     */
    public ViewForm(ScrollPane parent, PatchForm pPatchForm) {
      super (parent);
      _patch_form = pPatchForm;
      _patch = _patch_form._pPatch;

      try {
        jbInit();
      }
      catch(Exception e) {
        e.printStackTrace();
      }

    }

    public void HideObjectList()
    {
      if  (_object_list != null)
      {
        _object_list.dispose();
        _object_list = null;
      }
    }
    /**
       @roseuid 3E8CBA0F0023
     */
    public ViewForm(ScrollPane parent, ViewHook pView) {
      super (parent);
      _patch_form = pView._patch_form;
      _patch = pView._pObject;
      _view_hook = pView;

      try {
        jbInit();
      }
      catch(Exception e) {
        e.printStackTrace();
      }

    }

    /**
       Make the connection
       @roseuid 3E877A4F0211
     */
    public void DoConnection(CTopFollower top, CBottomFollower bottom) {
      System.out.println("Do Connection");
    }

    /**
       Sets the _patch value
       @roseuid 3E878C6B020D
     */
    public void SetPatch(int pPatch) {
      _patch = pPatch;
    }

    /**
       Updates the Form and Parent
       @roseuid 3E8CC44A0169
     */
    public void update() {
      System.out.println("Update View ");
      doLayout();
      if (_parent != null)
      {
        _parent.doLayout();
      }

    }

    public BaseShellBox GetBaseShellBox (BaseShellHook pHook){
      BaseShellBox ret = null;
      if (_object_map.containsKey(pHook))
      {
        ret = (BaseShellBox) _object_map.get(pHook);
      }
      return ret;
    }

    public ConnectorLine GetConnectorLine(ConnectorHook pCon){
      ConnectorLine pline = null;

      if (_connector_map.containsKey(pCon))
      {
        pline = (ConnectorLine) _connector_map.get(pCon);
      }

      return pline;
    }
      /**
       Adds A View Object to the Display
       @roseuid 3E8CDCB902EA
     */
    public boolean AddObject(ViewObject view_object) {
      boolean ret = false;
      BaseShellHook pHook = view_object._pHook;
      // see if already exists
      if (!_object_map.containsKey(pHook))
      {
        BaseShellTreeNode pNode = _patch_form.GetObjectNode(pHook);

        BaseShellBox object_box = BaseShellBox.create(this, pNode._pHook);
        object_box.setLocation(view_object.left, view_object.top);

        object_box.resizeBox(new Dimension(view_object.width, view_object.height));
        object_box.doLayout();
        AddObjectBox(object_box);


        _object_map.put(pHook, object_box);
        int p_interface = _patch_form._pinterface;
        int pObject = pHook._pObject;

        // now see if any connectors need to be added
        for(int InletNum = 0; InletNum < BaseShell.GetNumInlets(p_interface, pObject); InletNum++)
         {
           for (int ConNum = 0; ConNum < BaseShell.GetNumInletConnectors(p_interface, pObject, InletNum);
                                     ConNum++)
           {
             int pCon = BaseShell.GetInletConnector(p_interface, pObject, InletNum, ConNum);
             AddConnection(_patch_form.GetConnectorHook(pCon));//only adds if can
           }
         }

         for(int OutletNum = 0; OutletNum < BaseShell.GetNumOutlets(p_interface, pObject); OutletNum++)
         {
           for (int ConNum = 0; ConNum < BaseShell.GetNumOutletConnectors(p_interface, pObject, OutletNum);
                                     ConNum++)
           {
             int pCon = BaseShell.GetOutletConnector(p_interface, pObject, OutletNum, ConNum);
             AddConnection(_patch_form.GetConnectorHook(pCon));//only adds if can
           }
         }

        ret = true;
      }
      return ret;
    }

    /**
       Removes Object From Display using BaseShellHook as Parameter
       @roseuid 3E8CDD500175
     */
    public boolean RemoveObject(BaseShellHook pHook) {
      boolean ret = false;
      if (_object_map.containsKey(pHook))
      {
        BaseShellBox old_panel = (BaseShellBox) _object_map.get (pHook);
        _object_map.remove(pHook);
        this.remove(old_panel);

        // now see if we have any connectors to remove
        int p_interface = _patch_form._pinterface;
        int pObject = pHook._pObject;

        // now see if any connectors need to be added
        for(int InletNum = 0; InletNum < BaseShell.GetNumInlets(p_interface, pObject); InletNum++)
         {
           for (int ConNum = 0; ConNum < BaseShell.GetNumInletConnectors(p_interface, pObject, InletNum);
                                     ConNum++)
           {
             int pCon = BaseShell.GetInletConnector(p_interface, pObject, InletNum, ConNum);
             RemoveConnector(_patch_form.GetConnectorHook(pCon));//only adds if can
           }
         }

         for(int OutletNum = 0; OutletNum < BaseShell.GetNumOutlets(p_interface, pObject); OutletNum++)
         {
           for (int ConNum = 0; ConNum < BaseShell.GetNumOutletConnectors(p_interface, pObject, OutletNum);
                                     ConNum++)
           {
             int pCon = BaseShell.GetOutletConnector(p_interface, pObject, OutletNum, ConNum);
             RemoveConnector(_patch_form.GetConnectorHook(pCon));//only adds if can
           }
         }

        update();
      }
      return ret;
    }

    /**
       Adds a Connection Between two Objects if possible
       @roseuid 3E8CEB980212
     */
    public boolean AddConnection(ConnectorHook pCon) {
      boolean ret = false;

      if (pCon != null && ! _connector_map.containsKey(pCon))
      {
        ret = true;
        int p_interface = _patch_form._pinterface;
        int inlet_base, outlet_base, inlet_num, outlet_num;
        BaseShellHook inlet_hook, outlet_hook;

        inlet_base = Connector.GetInletBase(p_interface, pCon._pObject);
        outlet_base = Connector.GetOutletBase(p_interface, pCon._pObject);

        inlet_hook = _patch_form.GetBaseShellHook(inlet_base);
        outlet_hook = _patch_form.GetBaseShellHook(outlet_base);

        // both must be in our map to add
        if (_object_map.containsKey(inlet_hook) && _object_map.containsKey(outlet_hook))
        {
          // get inlet information first
          BaseShellBox inlet_box = (BaseShellBox) _object_map.get(inlet_hook);
          inlet_num = Connector.GetInletNum(p_interface, pCon._pObject);
          BaseShellInlet inlet_socket = inlet_box.GetTop(inlet_num);

          // get outlet information
          BaseShellBox outlet_box = (BaseShellBox) _object_map.get(outlet_hook);
          outlet_num = Connector.GetOutletNum(p_interface, pCon._pObject);
          BaseShellOutlet outlet_socket = outlet_box.GetBottom(outlet_num);

          if (inlet_socket != null && outlet_socket != null)
          {
            // we can Make a connection
            // first see if there is a View Available from the ViewHook
            ViewConnector pViewCon = this._view_hook.GetViewConnector(pCon);

            ConnectorLine pline = new ConnectorLine (inlet_socket, outlet_socket, this, pCon, pViewCon);
            _connector_map.put(pCon, pline);
          }
        }
      }
      return ret;
    }

    /**
       Removes Connector From Form
       @roseuid 3E91FDF90230
     */
    public boolean RemoveConnector(ConnectorHook pCon) {
      boolean ret = false;
      if (_connector_map.containsKey(pCon))
      {
        ConnectorLine pline = (ConnectorLine)_connector_map.get(pCon);
        _connector_map.remove(pCon);
        pline.destroy();
        update();
        ret = true;
      }
      return ret;
    }

    /**
       Stores the View Within View Hook
       @roseuid 3E91FE37009F
     */
    public synchronized boolean SaveView() {
      System.out.println("Save View");
      _view_hook.ClearView();

      // first save Objects
      Set key_set = _object_map.entrySet();
      Iterator iter = key_set.iterator();

      while (iter.hasNext())
      {
        BaseShellBox pBox = (BaseShellBox) ((java.util.Map.Entry) iter.next()).getValue();
        BaseShellHook pHook = pBox._pHook;
        ViewObject pViewObj = new ViewObject ();

        pViewObj.SetBounds(pBox.getBounds());
        pViewObj.setHook(pHook);
        _view_hook.AddObject(pHook, pViewObj);
      }

      key_set = _connector_map.entrySet();
      iter = key_set.iterator();

      while (iter.hasNext())
      {
        ConnectorLine pline = (ConnectorLine) ((java.util.Map.Entry) iter.next()).getValue();
        ConnectorHook pHook = pline._pHook;

        ViewConnector pConView = new ViewConnector (pHook);

        // store all the points into the ConView
        // there is no need to save the last segment
        for (int i = 0; i < pline._segments.size() -1; i++)
        {
          int length = ((CLineSegment)pline._segments.get(i)).getPlacementSize();
          pConView.AddValue(length);
        }

        pConView.AddValue(pline._tag);
        _view_hook.AddConnector (pHook, pConView);
      }

      return _view_hook.SaveView();
    }

    /**
       @roseuid 3E961A160033
     */
    void destroy() {
      // first save Objects
      Set key_set = _object_map.entrySet();
      Iterator iter = key_set.iterator();

      while (iter.hasNext())
      {
        BaseShellBox pBox = (BaseShellBox) ((java.util.Map.Entry) iter.next()).getValue();
        pBox._pHook = null;
        pBox.destroy();
      }

      _object_map.clear();

      key_set = _connector_map.entrySet();
      iter = key_set.iterator();

      while (iter.hasNext())
      {
        ConnectorLine pline = (ConnectorLine) ((java.util.Map.Entry) iter.next()).getValue();
        pline._pHook = null;
        pline.destroy();
      }
      _connector_map.clear();

      this._view_hook._view_form = null;
      _view_hook = null;
      this._parent.remove(this);
      if (_object_list != null)
      {
        _object_list.dispose();
      }
    }

    /**
       @roseuid 3E961A16024F
     */
    public ViewForm() {
    super (null);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    }

    /**
       @roseuid 3E961A160263
     */
    private void jbInit() throws Exception {
    CreateObjectMenu.setText("Create Object");
    CreateObjectMenu.addActionListener(new ViewForm_CreateObjectMenu_actionAdapter(this));
    this.addMouseListener(new ViewForm_this_mouseAdapter(this));
    ViewPopup.add(CreateObjectMenu);
    ViewPopup.setDefaultLightWeightPopupEnabled(false);
    }

    /**
       @roseuid 3E961A16028C
     */
    void this_mousePressed(MouseEvent e) {
    if (e.isPopupTrigger())
    {
      _mouse_pos = new Point (e.getX(), e.getY());
      ViewPopup.show(e.getComponent(),
                           e.getX(), e.getY());
    }

    }

    /**
       @roseuid 3E961A1602D2
     */
    void this_mouseReleased(MouseEvent e) {
    if (e.isPopupTrigger())
    {
      _mouse_pos = new Point (e.getX(), e.getY());
      ViewPopup.show(e.getComponent(),
                           e.getX(), e.getY());
    }

    }

    /**
       @roseuid 3E961A16030E
     */
    void CreateObjectMenu_actionPerformed(ActionEvent e) {
    if (_object_list != null)
    {
      _object_list.dispose();
    }
    _object_list = new ObjectsList(this._patch_form._pinterface, _patch, this._patch_form, _mouse_pos);
    _object_list.pack();
    _object_list.setVisible(true);

    }

    /**
       Invalidates all the objects on the display, making them redraw themselves
       @roseuid 3E961A2602A3
     */
    public synchronized void RefreshDisplay() {
//      System.out.println("RefreshDisplay");
      Set key_set = _object_map.entrySet();
      Iterator iter = key_set.iterator();

      while (iter.hasNext() && this._patch_form.IsConnected())
      {
        final BaseShellBox pBox = (BaseShellBox) ((java.util.Map.Entry) iter.next()).getValue();
        try {
          // make a new segment using the top and this
          javax.swing.SwingUtilities.invokeLater(new Runnable() {

            public void run() {
              pBox.AdjustSize();
              if (pBox.GetLastString() != pBox.GetText()
                  || pBox.PaintedHighlighted() != pBox.GetHighlighted())
              {
                pBox.invalidate();
                pBox.repaint();
              }

            }
          });
        }
        catch(Exception e) {
          e.printStackTrace();
        }

      }

    }
}
class ViewForm_this_mouseAdapter extends MouseAdapter {
    ViewForm adaptee;

    /**
       @roseuid 3E961A1603E0
     */
    ViewForm_this_mouseAdapter(ViewForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E961A1603E2
     */
    public void mousePressed(MouseEvent e) {
    adaptee.this_mousePressed(e);
    }

    /**
       @roseuid 3E961A17000C
     */
    public void mouseReleased(MouseEvent e) {
    adaptee.this_mouseReleased(e);
    }
}
class ViewForm_CreateObjectMenu_actionAdapter implements ActionListener {
    ViewForm adaptee;

    /**
       @roseuid 3E961A17002B
     */
    ViewForm_CreateObjectMenu_actionAdapter(ViewForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E961A17002D
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.CreateObjectMenu_actionPerformed(e);
    }
}
