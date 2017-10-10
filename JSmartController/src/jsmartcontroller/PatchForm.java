// Source file: C:/develop/JSmartController/src/jsmartcontroller/PatchForm.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import javax.swing.tree.*;
import Jni.*;
import javax.swing.event.*;
import java.beans.*;
import java.util.*;
import ViewForms.Graphics.*;
import java.io.*;
import javax.swing.filechooser.*;


class PatchForm_this_windowAdapter extends WindowAdapter {
    PatchForm adaptee;

    /**
       @roseuid 3E8287260087
     */
    PatchForm_this_windowAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8287260089
     */
    public void windowClosing(WindowEvent e) {
    adaptee.this_windowClosing(e);
    }
}
class PatchForm_SaveButton_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E9610870387
     */
    PatchForm_SaveButton_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E9610870389
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.SaveButton_actionPerformed(e);
    }
}
class PatchForm_jMenu1_mouseAdapter extends MouseAdapter {
    PatchForm adaptee;

    /**
       @roseuid 3E8287260114
     */
    PatchForm_jMenu1_mouseAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8287260116
     */
    public void mouseClicked(MouseEvent e) {
    adaptee.jMenu1_mouseClicked(e);
    }
}
class PatchForm_ValueBtn_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3EB1ED760127
     */
    PatchForm_ValueBtn_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3EB1ED760129
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.ValueBtn_actionPerformed(e);
    }
}
class PatchForm_jTree1_mouseAdapter extends MouseAdapter {
    PatchForm adaptee;

    /**
       @roseuid 3E82872600E1
     */
    PatchForm_jTree1_mouseAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E82872600E3
     */
    public void mouseClicked(MouseEvent e) {
    adaptee.jTree1_mouseClicked(e);
    }

    /**
       @roseuid 3E82872600E5
     */
    public void mouseReleased(MouseEvent e) {
    adaptee.jTree1_mouseReleased(e);
    }

    /**
       @roseuid 3E82872600E7
     */
    public void mousePressed(MouseEvent e) {
    adaptee.jTree1_mousePressed(e);
    }
}
class PatchForm_NameBtn_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3EB1ED76014F
     */
    PatchForm_NameBtn_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3EB1ED760151
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.NameBtn_actionPerformed(e);
    }
}
class PatchForm_EditObjectMenu_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E8287260146
     */
    PatchForm_EditObjectMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8287260148
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.EditObjectMenu_actionPerformed(e);
    }
}
class PatchForm__tree_model_treeModelAdapter implements TreeModelListener {
    PatchForm adaptee;

    /**
       @roseuid 3E82872600B9
     */
    PatchForm__tree_model_treeModelAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E82872600BB
     */
    public void treeNodesChanged(TreeModelEvent e) {
    adaptee._tree_model_treeNodesChanged(e);
    }

    /**
       @roseuid 3E82872600BD
     */
    public void treeNodesInserted(TreeModelEvent e) {
    }

    /**
       @roseuid 3E82872600BF
     */
    public void treeNodesRemoved(TreeModelEvent e) {
    }

    /**
       @roseuid 3E82872600C1
     */
    public void treeStructureChanged(TreeModelEvent e) {
    }
}
class PatchForm_SaveViewMenu_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E9610870374
     */
    PatchForm_SaveViewMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E9610870376
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.SaveViewMenu_actionPerformed(e);
    }
}
/**
   Patch form.
   The Form Used to Display a patch tree and views
 */
class ViewUpdater implements ActionListener {
    javax.swing.Timer timer;
    PatchForm _parent;

    /**
       @roseuid 3EB1ED750021
     */
    ViewUpdater(PatchForm parent, int time) {
    timer = new javax.swing.Timer(time, this);
    _parent = parent;
    }

    /**
       @roseuid 3EB1ED750024
     */
    public void actionPerformed(ActionEvent e) {
     _parent.RefreshViewForm();
    }

    /**
       @roseuid 3EB1ED750026
     */
    public synchronized void Start() {
    if (!timer.isRunning())
    {
      timer.start();
    }
    }

    /**
       @roseuid 3EB1ED750027
     */
    public synchronized void Stop() {
    if (timer.isRunning())
    {
      timer.stop();
    }

    }
}
class PatchForm_jMenuCreate_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E8287260055
     */
    PatchForm_jMenuCreate_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E8287260057
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.jMenuCreate_actionPerformed(e);
    }
}
class PatchForm_SaveAsMenu_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E96108703C3
     */
    PatchForm_SaveAsMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E96108703C5
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.SaveAsMenu_actionPerformed(e);
    }
}
public class PatchForm extends JFrame {
    int _pinterface = 0;
    int _pPatch = 0;
    int object_count = 0;
    boolean _is_simulator = true;
    /**
       flag to determine whether patch is modified
     */
    private boolean _modified = false;
    PatchTree _PatchTree;
    IdentityTreeNode _last_node = null;
    JPanel contentPane;
    JMenuBar jMenuBar1 = new JMenuBar ();
    JMenu jMenu1 = new JMenu ();
    JMenuItem jMenuCreate = new JMenuItem ();
    DefaultTreeModel _tree_model;
    JTree jTree1;
    JScrollPane treeView;
    BorderLayout borderLayout1 = new BorderLayout ();
    JMenuItem EditObjectMenu = new JMenuItem ();
    JPopupMenu TreePopupMenu = new JPopupMenu ();
    JMenuItem PopupEdit = new JMenuItem ();
    JMenuItem PopupDelete = new JMenuItem ();
    TreeMap _object_map = new TreeMap ();
    TreeMap _connector_map = new TreeMap ();
    ScrollPane ViewScrollPanel = new ScrollPane ();
    ViewForm _view_panel;
    JToolBar jToolBar = new JToolBar ();
    JLabel statusBar = new JLabel ();
    JButton SaveButton = new JButton ();
    JMenu ViewsMenu = new JMenu ();
    JMenuItem SaveViewMenu = new JMenuItem ();
    String _filename = null;
    JMenu FileMenu = new JMenu ();
    JMenuItem CloseMenu = new JMenuItem ();
    static String _smp_ext = new String (".smp");
    JMenuItem SaveMenu = new JMenuItem ();
    JMenuItem SaveAsMenu = new JMenuItem ();
    ButtonGroup _display_type = new ButtonGroup ();
    JRadioButton ObjectTypeBtn = new JRadioButton ();
    JRadioButton NameBtn = new JRadioButton ();
    JRadioButton ValueBtn = new JRadioButton ();
    ViewUpdater _updater;
    JMenuItem NewViewMenu = new JMenuItem();
    JCheckBox chkDragResize = new JCheckBox();
    JMenu ConnectorMenu = new JMenu();
    JMenuItem EditConnectorMenu = new JMenuItem();
    JMenuItem DeleteConnectorMenu = new JMenuItem();
    ConnectorHook _selected_connector = null;
    BaseShellBox _selected_object = null;
  JMenuItem DeleteObjectMenu = new JMenuItem();
  JMenuItem RemoveFromViewMenu = new JMenuItem();
  JCheckBox chkForceUpdate = new JCheckBox();
  JCheckBoxMenuItem mnuAutoUpdate = new JCheckBoxMenuItem();
  JMenuItem mnuShowSim = new JMenuItem();
  JMenuItem mnuSimOutput = new JMenuItem();
  JButton ReloadButton = new JButton();
  BaseShellTransferHandler bash_shell_transfer;
    /**
       @roseuid 3E8287260019
     */
    public PatchForm(int p_interface, int pPatch) {
    _pinterface = p_interface;
    _pPatch = pPatch;
    _PatchTree = new PatchTree (p_interface, pPatch, this);
    _PatchTree.setHook(new  BaseShellHook(p_interface, pPatch));

    _tree_model = new DefaultTreeModel (_PatchTree);
    _PatchTree.SetTreeModel(_tree_model);
    jTree1 = new JTree(_tree_model);
    treeView = new JScrollPane(jTree1);
    bash_shell_transfer = new BaseShellTransferHandler();

    _filename = Patch.GetFileName(p_interface, pPatch);

    System.out.println("Filename " + _filename);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }

    _PatchTree.DisplayView(0);
    chkDragResize.setSelected(BaseShellBox.DisableResize());
    chkForceUpdate.setSelected(BaseShellBox.ForceUpdate());
    if (BaseShellBox.ForceUpdate())
    {
      _updater.Start();
    }
  }

    /**
       @roseuid 3E828726001C
     */
    public PatchForm() {
    JTree jTree1 = new JTree();
    treeView = new JScrollPane(jTree1);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    }

    /**
       @roseuid 3E828726001D
     */
    private void DeinitialisePatch() {
      _updater.Stop();

      if (GetModified())
      {
        JOptionPane save_option = new JOptionPane();

        int selection = save_option.showConfirmDialog(this,
            "Do you Want To Save your Patch", "Save", JOptionPane.YES_NO_OPTION,
            JOptionPane.WARNING_MESSAGE);

        if (selection == JOptionPane.YES_OPTION) {
          Save();
        }
      }

    _PatchTree.ClearNode();
    }

    /**
       @roseuid 3E828726001E
     */
    private void jbInit() throws Exception {
    JPopupMenu.setDefaultLightWeightPopupEnabled(false);

    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(borderLayout1);
    jMenu1.setAlignmentX((float) 0.5);
    jMenu1.setText("Objects");
    jMenu1.setToolTipText("");
    jMenu1.setText("Objects");
    jMenu1.addMouseListener(new PatchForm_jMenu1_mouseAdapter(this));
    jMenuCreate.setText("Create");
    jMenuCreate.addActionListener(new PatchForm_jMenuCreate_actionAdapter(this));
    this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    this.addWindowStateListener(new PatchForm_this_windowStateAdapter(this));
    this.addWindowListener(new PatchForm_this_windowAdapter(this));
    _tree_model.addTreeModelListener(new PatchForm__tree_model_treeModelAdapter(this));
    jTree1.addMouseListener(new PatchForm_jTree1_mouseAdapter(this));
    EditObjectMenu.setText("Edit Object");
    EditObjectMenu.addActionListener(new PatchForm_EditObjectMenu_actionAdapter(this));
    PopupEdit.setText("Edit");
    PopupEdit.addActionListener(new PatchForm_PopupEdit_actionAdapter(this));
    PopupDelete.setToolTipText("");
    PopupDelete.setText("Delete");
    PopupDelete.addActionListener(new PatchForm_PopupDelete_actionAdapter(this));
    statusBar.setMaximumSize(new Dimension(20, 20));
    statusBar.setMinimumSize(new Dimension(20, 20));
    statusBar.setPreferredSize(new Dimension(20, 20));
    ViewsMenu.setToolTipText("");
    ViewsMenu.setText("View");
    SaveViewMenu.setToolTipText("");
    SaveViewMenu.setText("Save View");
    SaveViewMenu.addActionListener(new PatchForm_SaveViewMenu_actionAdapter(this));
    SaveButton.addActionListener(new PatchForm_SaveButton_actionAdapter(this));
    FileMenu.setText("File");
    CloseMenu.setToolTipText("");
    CloseMenu.setText("Close");
    CloseMenu.addActionListener(new PatchForm_CloseMenu_actionAdapter(this));
    SaveMenu.setText("Save");
    SaveMenu.addActionListener(new PatchForm_SaveMenu_actionAdapter(this));
    SaveAsMenu.setText("Save As");
    SaveAsMenu.addActionListener(new PatchForm_SaveAsMenu_actionAdapter(this));
    SaveButton.setText("Save Patch");
    ObjectTypeBtn.setToolTipText("Display the types of objects");
    ObjectTypeBtn.setSelected(true);
    ObjectTypeBtn.setText("Display Type");
    ObjectTypeBtn.addActionListener(new PatchForm_ObjectTypeBtn_actionAdapter(this));
    NameBtn.setToolTipText("Display the names of the objects");
    NameBtn.setText("Display Name");
    NameBtn.addActionListener(new PatchForm_NameBtn_actionAdapter(this));
    ValueBtn.setToolTipText("Display the values of the objects");
    ValueBtn.setActionCommand("jRadioButton1");
    ValueBtn.setText("Display Values");
    ValueBtn.addActionListener(new PatchForm_ValueBtn_actionAdapter(this));
    NewViewMenu.setText("CreateView");
    NewViewMenu.addActionListener(new PatchForm_NewViewMenu_actionAdapter(this));
    chkDragResize.setToolTipText("Enables objects to be resized using the mouse");
    chkDragResize.setActionCommand("jCheckBox1");
    chkDragResize.setText("Disable Resize");
    chkDragResize.addActionListener(new PatchForm_chkDragResize_actionAdapter(this));
    ConnectorMenu.setEnabled(false);
    ConnectorMenu.setText("Connector");
    EditConnectorMenu.setText("Edit");
    EditConnectorMenu.addActionListener(new PatchForm_EditConnectorMenu_actionAdapter(this));
    DeleteConnectorMenu.setToolTipText("");
    DeleteConnectorMenu.setText("Delete");
    DeleteConnectorMenu.addActionListener(new PatchForm_DeleteConnectorMenu_actionAdapter(this));
    DeleteObjectMenu.setText("Delete");
    DeleteObjectMenu.addActionListener(new PatchForm_DeleteObjectMenu_actionAdapter(this));
    RemoveFromViewMenu.setText("Remove From View");
    RemoveFromViewMenu.addActionListener(new PatchForm_RemoveFromViewMenu_actionAdapter(this));
    jTree1.addTreeSelectionListener(new PatchForm_jTree1_treeSelectionAdapter(this));
    chkForceUpdate.setActionCommand("jCheckBox1");
    chkForceUpdate.setText("Force Update");
    chkForceUpdate.addActionListener(new PatchForm_chkForceUpdate_actionAdapter(this));
    mnuAutoUpdate.setToolTipText("Causes Object value to allways be updated");
    mnuAutoUpdate.setText("Automatic Update");
    mnuAutoUpdate.addActionListener(new PatchForm_mnuAutoUpdate_actionAdapter(this));
    mnuShowSim.setText("Show Sim Inputs");
    mnuShowSim.addActionListener(new PatchForm_mnuShowSim_actionAdapter(this));
    mnuSimOutput.setText("Show Simulator Outputs");
    mnuSimOutput.addActionListener(new PatchForm_mnuSimOutput_actionAdapter(this));
    ReloadButton.setActionCommand("jButton1");
    ReloadButton.setText("Redraw View");
    ReloadButton.addActionListener(new PatchForm_ReloadButton_actionAdapter(this));
//    jTree1.addMouseMotionListener(new PatchForm_jTree1_mouseMotionAdapter(this));
    jMenuBar1.add(FileMenu);
    jMenuBar1.add(jMenu1);
    jMenuBar1.add(ConnectorMenu);
    jMenuBar1.add(ViewsMenu);

    jMenu1.add(jMenuCreate);
    jMenu1.add(EditObjectMenu);
    jMenu1.add(mnuAutoUpdate);
    jMenu1.add(RemoveFromViewMenu);
    jMenu1.addSeparator();
    jMenu1.add(DeleteObjectMenu);
    jTree1.setAutoscrolls(true);
    jTree1.setBorder(BorderFactory.createRaisedBevelBorder());
    jTree1.setEditable(true);
    jTree1.getSelectionModel().setSelectionMode
        (TreeSelectionModel.SINGLE_TREE_SELECTION);
    jTree1.setShowsRootHandles(true);


    this.setJMenuBar(jMenuBar1);
    jToolBar.add(SaveButton);
    jToolBar.add(ReloadButton, null);
    jToolBar.add(ObjectTypeBtn, null);
    contentPane.add(jToolBar, BorderLayout.NORTH);
    contentPane.add(statusBar, BorderLayout.SOUTH);

    //getContentPane().add(jTree1,  BorderLayout.WEST);
    getContentPane().add(treeView,  BorderLayout.WEST);

    TreePopupMenu.setDefaultLightWeightPopupEnabled(false);
    TreePopupMenu.add(PopupEdit);
    TreePopupMenu.add(PopupDelete);
    contentPane.add(ViewScrollPanel, BorderLayout.CENTER);
    ViewsMenu.add(NewViewMenu);
    ViewsMenu.add(SaveViewMenu);
    ViewsMenu.addSeparator();
    ViewsMenu.add(mnuShowSim);
    ViewsMenu.add(mnuSimOutput);
    FileMenu.add(CloseMenu);
    FileMenu.add(SaveMenu);
    FileMenu.add(SaveAsMenu);
    _display_type.add(ObjectTypeBtn);
    jToolBar.add(NameBtn, null);
    _display_type.add(NameBtn);
    jToolBar.add(ValueBtn, null);
    jToolBar.add(chkDragResize, null);
    jToolBar.add(chkForceUpdate, null);
    _display_type.add(ValueBtn);
    ConnectorMenu.add(EditConnectorMenu);
    ConnectorMenu.add(DeleteConnectorMenu);
    _updater = new ViewUpdater (this, 100);
    }

    /**
       Displays Text in status window
       @roseuid 3EB1EDB80352
     */
    public void DisplayText(String text) {
      statusBar.setText(text);
    }

    public void DisplaySelectedConnectorLine (ConnectorHook pHook){
       if (_view_panel != null)
         {
           ConnectorLine pLine = _view_panel.GetConnectorLine(pHook);
           if (pLine != null)
           {
             pLine.ProcessClick();
           }
         }
         SetSelectedConnector(pHook);
    }

    public void SetSelectedConnector(ConnectorHook pHook){
      _selected_connector = pHook;
      ConnectorMenu.setEnabled(_selected_connector != null);
      if (_selected_connector != null)
      {
        PatchTreeNode pNode = pHook.GetTreeNode();
        SelectTreeNode(pNode);
      }
      // we cannot drag a connector
      jTree1.setDragEnabled(false);
    }

    public void SelectTreeNode (PatchTreeNode pNode){
      if (pNode != null)
      {
        TreeNode [] ptr = pNode.getPath();
        TreePath path = new TreePath(ptr);
        jTree1.setSelectionPath (path);

        //jTree1.scrollPathToVisible (path);

      }
      RefreshViewForm();
    }

    public void SetSelectedBaseShellHook(BaseShellHook pHook){
      if (_view_panel != null)
      {
        BaseShellBox pbox = _view_panel.GetBaseShellBox(pHook);
        SetSelectedObject (pbox);
        if (pbox != null)
        {
          // Must already be in View
         jTree1.setDragEnabled(false);

         pbox.SetHighlighted(true);
        }
        else
        {
          // we can drag a Box
          if (_view_panel._patch ==  Identity.GetParent(this._pinterface,  pHook._pObject))
          {
            jTree1.setDragEnabled(true);
            bash_shell_transfer.SetHook(pHook);
            bash_shell_transfer.SetTarget(_view_panel);
            contentPane.setTransferHandler(bash_shell_transfer);
            jToolBar.setTransferHandler(bash_shell_transfer);
          }
          else
          {
            jTree1.setDragEnabled(false);
          }
        }

      }
    }

    public void SetSelectedObject(BaseShellBox pBox){
      // first see if we have to deselect a previous one
      if (_selected_object != null && pBox != _selected_object)
      {
        _selected_object.SetHighlighted(false);
        _selected_object.invalidate();
      }
     _selected_object = pBox;

     if (_selected_object != null)
     {
       _last_node = _selected_object._pHook.GetTreeNode();
       SelectTreeNode (_last_node);
     }
     else
     {
       //_last_node = null;
     }

     EditObjectMenu.setEnabled(_last_node != null);
     RemoveFromViewMenu.setEnabled(_selected_object != null);
     DeleteObjectMenu.setEnabled(_last_node != null);
     mnuAutoUpdate.setEnabled(_last_node != null);
     if (_selected_object != null)
     {
       mnuAutoUpdate.setState(!_selected_object.DisableUpdate());
     }
     else
     {
       mnuAutoUpdate.setState(false);
     }
     RefreshViewForm();
    }

    /**
       @roseuid 3E828726001F
     */
    void AddObject(int pShell, int pPatch, Point Position) {
      BaseShellTreeNode pNode = _PatchTree.AddBaseShell(pShell);

      if (_view_panel != null)
      {
        ViewObject view_object = new ViewObject ();
        view_object.setHook(pNode._pHook);

        if (Position == null)
        {
          view_object.left = 10;
          view_object.top = 10;
        }
        else
        {
          view_object.left = Position.x;
          view_object.top = Position.y;
        }
        _view_panel.AddObject(view_object);
        _view_panel.update();
      }
    }

    /**
       @roseuid 3E8287260022
     */
    void jMenuCreate_actionPerformed(ActionEvent e) {
    ObjectsList list = new ObjectsList(_pinterface, _pPatch, this, null);
    list.pack();
    list.setVisible(true);
    }


    public void RequestKill(){
      _is_simulator = false;
       _updater.Stop();
    }
    /**
       @roseuid 3E8287260024
     */
    void this_windowClosing(WindowEvent e) {
      DeinitialisePatch();
      boolean kill_patch = true;

      if (!_is_simulator)
      {
        kill_patch = IsConnected(); // dont offer opportunity to kill if we are not connected
        if (kill_patch)
        {
          JOptionPane save_option = new JOptionPane();

          int selection = save_option.showConfirmDialog(this,
              "Do you Want To kill this Patch", "Kill Patch",
              JOptionPane.YES_NO_OPTION,
              JOptionPane.WARNING_MESSAGE);

          if (selection == JOptionPane.YES_OPTION) {
            kill_patch = true;
          }
          else {
            kill_patch = false;
          }
        }


      }

      if (kill_patch)
      {
        Patch.Destroy(_pinterface, _pPatch);
      }
    }

    /**
       @roseuid 3E8287260026
     */
    void _tree_model_treeNodesChanged(TreeModelEvent e) {
    DefaultMutableTreeNode node;
           node = (DefaultMutableTreeNode)
                    (e.getTreePath().getLastPathComponent());

           /*
            * If the event lists children, then the changed
            * node is the child of the node we've already
            * gotten.  Otherwise, the changed node and the
            * specified node are the same.
            */
           try {
               int index = e.getChildIndices()[0];
               node = (DefaultMutableTreeNode)
                      (node.getChildAt(index));
           } catch (NullPointerException exc) {}

           if (node == null) return;

           PatchTreeNode tree_node = (PatchTreeNode) node;

           if (!tree_node.CanEdit())
           {
             System.out.println("Cannot Change Name");
             tree_node.setUserObject(tree_node.GetDefaultName());
           }
           else
           {
             String newName = (String) node.getUserObject();
             IdentityTreeNode id_node = (IdentityTreeNode) node;
             IdentityHook pHook = id_node.GetHook();
             if (pHook.getName() != newName)
             {
               pHook.setName(newName);
             }
           }

    }

    /**
       @roseuid 3E8287260028
     */
    void jTree1_mouseClicked(MouseEvent e) {
      DefaultMutableTreeNode node = (DefaultMutableTreeNode)  jTree1.getLastSelectedPathComponent();

      if (node == null) return;
      PatchTreeNode tree_node = (PatchTreeNode) node;

      if (!tree_node.CanEdit())
      {
        _last_node = null;
      }
      else
      {
        _last_node = (IdentityTreeNode) tree_node;
        _last_node.DisplayMouseClick();
      }


    }

    /**
       @roseuid 3E828726002A
     */
    void jMenu1_mouseClicked(MouseEvent e) {
    EditObjectMenu.setEnabled(_last_node != null);
    mnuAutoUpdate.setEnabled(_last_node != null);
    RemoveFromViewMenu.setEnabled(_last_node != null);
    }

    /**
       @roseuid 3E828726002C
     */
    void EditObjectMenu_actionPerformed(ActionEvent e) {
    if (_last_node != null)
    {
      _last_node.GetHook().DisplayEditForm();
    }

    }

    /**
       @roseuid 3E828726002E
     */
    void PopupEdit_actionPerformed(ActionEvent e) {
    if (_last_node != null)
    {
        _last_node.GetHook().DisplayEditForm();

    }
    }

    /**
       @roseuid 3E8287260030
     */
    void jTree1_mouseReleased(MouseEvent e) {
    if (e.isPopupTrigger())
    {
      if (_last_node != null)
      {
        TreePopupMenu.show(e.getComponent(),
                           e.getX(), e.getY());
      }
    }


    }

    /**
       @roseuid 3E8287260032
     */
    void jTree1_mousePressed(MouseEvent e) {
    if (e.isPopupTrigger())
    {
      if (_last_node != null)
      {
        TreePopupMenu.show(e.getComponent(),
                           e.getX(), e.getY());
      }
    }

    }

    /**
       Adds BaseShell object to Object Map
       @roseuid 3E828AEA01D8
     */
    public void AddObject(BaseShellHook pShellHook, BaseShellTreeNode node) {
      _object_map.put(pShellHook, node);
    }

    /**
       Returns the BaseShellTreeNode Pointed to By this Node
       @roseuid 3E828BF403C5
     */
    public BaseShellTreeNode GetObjectNode(BaseShellHook pShellHook) {
      BaseShellTreeNode ret = null;
      if (_object_map.containsKey(pShellHook))
      {
        ret = (BaseShellTreeNode) _object_map.get(pShellHook);
      }
      return ret;
    }

    /**
       returns BaseShell Hook if exists
       @roseuid 3E890AE20036
     */
    public BaseShellHook GetBaseShellHook(int dwpShell) {
      BaseShellHook pHook = null;
      BaseShellHook temp = new BaseShellHook (0, dwpShell);

      BaseShellTreeNode pNode = GetObjectNode(temp);

      if (pNode != null)
      {
        pHook = pNode._pHook;
      }

      return pHook;
    }

    /**
       Finds and Removes the requested BaseShell from PatchForm
       @roseuid 3E828C17036B
     */
    public synchronized boolean DeleteObject(BaseShellHook pShellHook) {
      boolean ret = false;
      SetSelectedConnector(null);
      SetSelectedObject(null);

      if (_object_map.containsKey(pShellHook))
       {
         BaseShellTreeNode node = (BaseShellTreeNode) _object_map.get(pShellHook);

         node.ClearNode();
         _object_map.remove(pShellHook);
         TreeNode parent_node = node.getParent();
         if (parent_node != null)
         {
           _tree_model.removeNodeFromParent(node);
           ret = true;
         }

         // remove from all Nodes
         PatchTree patch_node = (PatchTree)parent_node.getParent();
         patch_node._views_node.RemoveObject(pShellHook);

         Patch.DetachBaseShellObject(_pinterface, _pPatch,  pShellHook._pObject);

         int dead_connector = Patch.GetDeadConnector(_pinterface, _pPatch);

         while (dead_connector != 0)
         {
           System.out.println("Deleting Connector id " + dead_connector);
           ConnectorHook pCon = new ConnectorHook (_pinterface, dead_connector);
           this.DeleteConnector(pCon);
           dead_connector = Patch.GetDeadConnector(_pinterface, _pPatch);
         }
       }
      return ret;
    }

    /**
       @roseuid 3E83825A013C
     */
    void PopupDelete_actionPerformed(ActionEvent e) {
    if (_last_node != null)
    {
      if (_last_node.GetHook().getClass() == new BaseShellHook(0, 0).getClass())
      {
        DeleteObject( (BaseShellHook) _last_node.GetHook());
      }

    }

    }

    /**
       Adds a connector to the connector map
       @roseuid 3E8398950186
     */
    public void AddConnector(ConnectorHook pHook, ConnectorTreeNode pNode) {
      _connector_map.put(pHook, pNode);
    }

    /**
       Returns the connector Node given a Connector Hook
       @roseuid 3E8398B103C1
     */
    public ConnectorTreeNode GetConnectorNode(ConnectorHook pHook) {
      ConnectorTreeNode ret = null;
      if (_connector_map.containsKey(pHook))
      {
        ret = (ConnectorTreeNode) _connector_map.get(pHook);
      }
      return ret;

    }

    /**
       Removes Connector And Node from Connector Map
       @roseuid 3E83992D0365
     */
    public synchronized boolean DeleteConnector(ConnectorHook pHook) {
      boolean ret = false;

      SetSelectedConnector(null);
      if (_connector_map.containsKey(pHook))
       {
         ConnectorTreeNode node = (ConnectorTreeNode) _connector_map.get(pHook);
         node.ClearNode();
         _connector_map.remove(pHook);
         TreeNode parent_node = node.getParent();
         if (parent_node != null)
         {
           _tree_model.removeNodeFromParent(node);
           ret = true;
           // remove from all Nodes
           PatchTree patch_node = (PatchTree)parent_node.getParent();
           patch_node._views_node.RemoveConnector(pHook);

         }
       }
      return ret;

    }

    /**
       Add connector to Patch Form
       @roseuid 3E8788BC008B
     */
    ConnectorHook AddConnector(int pCon, int pPatch) {
      ConnectorTreeNode pNode = _PatchTree.AddConnector(pCon);
      ConnectorHook pHook = pNode._pHook;
      _connector_map.put(pHook, pNode);
      pHook.Print();
      return pHook;
    }

    void RedrawView(){
      System.out.println("RedrawView");
      ViewScrollPanel.add (_view_panel, null);
      _view_panel.setLayout(null);
      _view_panel.doLayout();
      ViewScrollPanel.doLayout();
    }

    /**
       Creates new View Form to Patch Form and returns value
       @roseuid 3E8CBB0F0298
     */
    public ViewForm AddViewForm(ViewHook view_hook) {
      if (_view_panel != null)
      {
        _view_panel.SaveView();
        _view_panel.destroy();
      }

      _view_panel = new ViewForm (ViewScrollPanel, view_hook);
      _view_panel.setBackground(Color.white);
      RedrawView();
      return _view_panel;
    }

    public void AddNewView(){
      _PatchTree.AddNewView();
    }
    /**
       Sees if the connector is in t3E8CEC940052he connector Map and returns it if it is
       @roseuid
     */
    public ConnectorHook GetConnectorHook(int pCon) {
      ConnectorHook ret = null;
      ConnectorHook temp = new ConnectorHook(0, pCon);

      if (_connector_map.containsKey(temp))
      {
        ConnectorTreeNode pNode = (ConnectorTreeNode)_connector_map.get(temp);
        ret = pNode._pHook;
      }
      else
      {
        System.out.println("Connector Not Found");
      }
      return ret;
    }

    /**
       @roseuid 3E9610870048
     */
    public void SaveCurrentView() {
      if (_view_panel != null)
      {
        _view_panel.SaveView();
      }
    }

    /**
       @roseuid 3E9610870098
     */
    void Save(String filename) {

      if (!filename.endsWith(_smp_ext))
      {
        JFileChooser SaveDialog = new JFileChooser();
        SaveDialog.setFileFilter(new PatchFileFilter());
        String init_dir = PatchEditor.GetDefaultDirectory();

        if (init_dir != null)
        {
          File f = new File (init_dir);
          SaveDialog.setCurrentDirectory(f);
        }


        int ret = SaveDialog.showSaveDialog(this);
        if (ret == JFileChooser.APPROVE_OPTION)
        {
          File file = SaveDialog.getSelectedFile();
          filename = file.getName();

          String filepath = SaveDialog.getCurrentDirectory().getAbsolutePath() + file.separatorChar;
          String current_path = PatchEditor.GetDefaultDirectory();

          PatchEditor.SetDefaultDirectory(filepath);

          if (!filename.endsWith(_smp_ext))
          {
            filename += _smp_ext;
          }

          System.out.println("Path: " + filepath + filename );
          if (Patch.Save(this._pinterface, this._pPatch, filename))
          {
            System.out.println("SetFileName " + filename );
            Patch.SetFileName(this._pinterface, this._pPatch, filename);
            _filename = filename;
            _modified = false;
          }

        }
        else
        {
            System.out.println("Open command cancelled by user.");
        }

      }

      else if (Patch.Save(this._pinterface, this._pPatch, filename))
      {
        _filename = filename;
      }

    }

    /**
       @roseuid 3E961087025B
     */
    void SaveViewMenu_actionPerformed(ActionEvent e) {
    SaveCurrentView();
    }

    /**
       @roseuid 3E9610870279
     */
    void SaveButton_actionPerformed(ActionEvent e) {
      Save();
    }

    public void Save(){
      SaveCurrentView();
      Save(_filename);
    }
    /**
       @roseuid 3E9610870297
     */
    void CloseMenu_actionPerformed(ActionEvent e) {
    DeinitialisePatch();
    Patch.Destroy(_pinterface, _pPatch);
    this.dispose();
    }

    /**
       @roseuid 3E96108702B5
     */
    void SaveMenu_actionPerformed(ActionEvent e) {
      Save();
    }

    /**
       @roseuid 3E96108702D3
     */
    void SaveAsMenu_actionPerformed(ActionEvent e) {
    Save ("");
    }

    /**
       Returns true if Types are to be displayed
       @roseuid 3E96109B03C2
     */
    public boolean DisplayTypes() {
      return ObjectTypeBtn.isSelected();
    }

    /**
       Returns true if Names are to be displayed
       @roseuid 3E9610AA01ED
     */
    public boolean DisplayNames() {
      return NameBtn.isSelected();
    }

    /**
       Returns true if Values are to be displayed
       @roseuid 3E9610AB00A4
     */
    public boolean DisplayValues() {
      return ValueBtn.isSelected();
    }

    public boolean IsConnected(){
      return PatchEditor.IsConnected(this._pinterface);
    }
    /**
       @roseuid 3EB1ED76002C
     */
    public void RefreshViewForm() {
      if (_view_panel != null)
      {
        if (IsConnected())
        {
          _view_panel.RefreshDisplay();
        }
        else // not connected
        {
          _view_panel.setVisible(false);
          this.setTitle(this.getTitle() + "- Disconnected");
          System.out.println("Disconnected");
          _updater.Stop();
        }
      }
    }

    /**
       @roseuid 3EB1ED760036
     */
    void ValueBtn_actionPerformed(ActionEvent e) {
    RefreshViewForm();
    _updater.Start();
  }

    /**
       @roseuid 3EB1ED760054
     */
    void ObjectTypeBtn_actionPerformed(ActionEvent e) {
      if (!BaseShellBox.ForceUpdate())
      {
        _updater.Stop();
      }
    RefreshViewForm ();
    }

    /**
       @roseuid 3EB1ED760072
     */
    void NameBtn_actionPerformed(ActionEvent e) {
      if (!BaseShellBox.ForceUpdate())
      {
        _updater.Stop();
      }

    RefreshViewForm ();
    }

    /**
       Returns true if file patch needs saving
       @roseuid 3EB1F89A016E
     */
    public boolean GetModified() {
      return _modified || Identity.GetModified(_pinterface, _pPatch);
    }

    /**
       Forces Patch to Require saving
       @roseuid 3EB1F8B90295
     */
    public void SetModified() {
      _modified = true;
    }

  void NewViewMenu_actionPerformed(ActionEvent e) {
    AddNewView();
  }

  void chkDragResize_actionPerformed(ActionEvent e) {
    BaseShellBox.DisableResize(!BaseShellBox.DisableResize());
  }

  void DeleteConnectorMenu_actionPerformed(ActionEvent e) {
    if (_selected_connector != null)
    {
      DeleteConnector(_selected_connector);
      SetSelectedConnector (null);
    }
  }

  void EditConnectorMenu_actionPerformed(ActionEvent e) {
     if (_selected_connector != null)
     {
       _selected_connector.DisplayEditForm();
     }
  }

  void RemoveFromViewMenu_actionPerformed(ActionEvent e) {
     if (_selected_object != null)
     {
       ViewForm pForm = (ViewForm)(_selected_object._parent);
       pForm.RemoveObject(_selected_object._pHook);
       SetSelectedObject(null);
     }
  }

  void DeleteObjectMenu_actionPerformed(ActionEvent e) {
    if (_selected_object != null)
    {
      BaseShellHook pHook = _selected_object._pHook;
      SetSelectedObject(null);
      DeleteObject(pHook);
    }

  }

  void jTree1_valueChanged(TreeSelectionEvent e) {
    DefaultMutableTreeNode node = (DefaultMutableTreeNode)  jTree1.getLastSelectedPathComponent();

    if (node == null) return;
    PatchTreeNode tree_node = (PatchTreeNode) node;

    if (!tree_node.CanEdit())
    {
      _last_node = null;
    }
    else
    {
      _last_node = (IdentityTreeNode) tree_node;
      _last_node.DisplayMouseClick();
    }

  }

  void this_windowStateChanged(WindowEvent e) {
    RedrawView();
  }

  void chkForceUpdate_actionPerformed(ActionEvent e) {
    BaseShellBox.ForceUpdate(!BaseShellBox.ForceUpdate());
    if (BaseShellBox.ForceUpdate())
    {
      _updater.Start();
    }
    else if (!ValueBtn.isSelected())
    {
      _updater.Stop();
    }
  }

  void mnuAutoUpdate_actionPerformed(ActionEvent e) {
    if (_selected_object != null)
    {
      _selected_object.DisableUpdate(!_selected_object.DisableUpdate());
      mnuAutoUpdate.setState(!_selected_object.DisableUpdate());
    }
    else
    {
      mnuAutoUpdate.setState(false);
    }

  }

  void mnuShowSim_actionPerformed(ActionEvent e) {
    CVSim.ShowCVSim();
  }

  void mnuSimOutput_actionPerformed(ActionEvent e) {
    CVOutSim.ShowCVOutSim();
  }

  void ReloadButton_actionPerformed(ActionEvent e) {
    RedrawView();
  }

  void jTree1_mouseDragged(MouseEvent e) {
    if (_selected_object != null)
    {
      JComponent c = (JComponent) e.getSource();
      bash_shell_transfer.SetHook(_selected_object._pHook);
      bash_shell_transfer.exportAsDrag(c, e, TransferHandler.COPY);
      //System.out.println("Drag Tree");
    }
  }
}
class PatchForm_ObjectTypeBtn_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3EB1ED76013B
     */
    PatchForm_ObjectTypeBtn_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3EB1ED76013D
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.ObjectTypeBtn_actionPerformed(e);
    }
}
class PatchForm_SaveMenu_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E96108703AF
     */
    PatchForm_SaveMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E96108703B1
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.SaveMenu_actionPerformed(e);
    }
}
class PatchForm_CloseMenu_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E961087039B
     */
    PatchForm_CloseMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E961087039D
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.CloseMenu_actionPerformed(e);
    }
}
class PatchForm_PopupDelete_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E83825A0178
     */
    PatchForm_PopupDelete_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E83825A017A
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.PopupDelete_actionPerformed(e);
    }
}
class PatchForm_PopupEdit_actionAdapter implements ActionListener {
    PatchForm adaptee;

    /**
       @roseuid 3E8287260178
     */
    PatchForm_PopupEdit_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
    }

    /**
       @roseuid 3E828726017A
     */
    public void actionPerformed(ActionEvent e) {
    adaptee.PopupEdit_actionPerformed(e);
    }
}

class PatchForm_NewViewMenu_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_NewViewMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.NewViewMenu_actionPerformed(e);
  }
}

class PatchForm_chkDragResize_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_chkDragResize_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.chkDragResize_actionPerformed(e);
  }
}

class PatchForm_DeleteConnectorMenu_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_DeleteConnectorMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.DeleteConnectorMenu_actionPerformed(e);
  }
}

class PatchForm_EditConnectorMenu_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_EditConnectorMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.EditConnectorMenu_actionPerformed(e);
  }
}

class PatchForm_RemoveFromViewMenu_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_RemoveFromViewMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.RemoveFromViewMenu_actionPerformed(e);
  }
}

class PatchForm_DeleteObjectMenu_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_DeleteObjectMenu_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.DeleteObjectMenu_actionPerformed(e);
  }
}

class PatchForm_jTree1_treeSelectionAdapter implements javax.swing.event.TreeSelectionListener {
  PatchForm adaptee;

  PatchForm_jTree1_treeSelectionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void valueChanged(TreeSelectionEvent e) {
    adaptee.jTree1_valueChanged(e);
  }
}

class PatchForm_this_windowStateAdapter implements java.awt.event.WindowStateListener {
  PatchForm adaptee;

  PatchForm_this_windowStateAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void windowStateChanged(WindowEvent e) {
    adaptee.this_windowStateChanged(e);
  }
}

class PatchForm_chkForceUpdate_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_chkForceUpdate_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.chkForceUpdate_actionPerformed(e);
  }
}

class PatchForm_mnuAutoUpdate_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_mnuAutoUpdate_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuAutoUpdate_actionPerformed(e);
  }
}

class PatchForm_mnuShowSim_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_mnuShowSim_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuShowSim_actionPerformed(e);
  }
}

class PatchForm_mnuSimOutput_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_mnuSimOutput_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuSimOutput_actionPerformed(e);
  }
}

class PatchForm_ReloadButton_actionAdapter implements java.awt.event.ActionListener {
  PatchForm adaptee;

  PatchForm_ReloadButton_actionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.ReloadButton_actionPerformed(e);
  }
}

class PatchForm_jTree1_mouseMotionAdapter extends java.awt.event.MouseMotionAdapter {
  PatchForm adaptee;

  PatchForm_jTree1_mouseMotionAdapter(PatchForm adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseDragged(MouseEvent e) {
    adaptee.jTree1_mouseDragged(e);
  }
}
