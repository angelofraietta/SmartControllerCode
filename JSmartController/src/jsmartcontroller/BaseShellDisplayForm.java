// Source file: C:/develop/JSmartController/src/jsmartcontroller/BaseShellDisplayForm.java

package jsmartcontroller;

//import java.awt.*;
//import java.awt.event.*;
import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.JTextField;
import Jni.*;
import javax.swing.event.*;
import java.util.*;

public class BaseShellDisplayForm extends JFrame {
  public BaseShellHook _pHook;

  DefaultListModel AttributeListModel = new DefaultListModel();
  DefaultListModel ResetAttributeListModel = new DefaultListModel();

  JPanel TopPanel = new JPanel();
  FlowLayout TopLayout = new FlowLayout();
  JTextField _Name = new JTextField();
  JPanel BottomPanel = new JPanel();
  JButton SendButton = new JButton();
  FlowLayout BottomLayout = new FlowLayout();
  JButton ResetButton = new JButton();
  JButton ReloadButton = new JButton();
  JLabel NameLabel = new JLabel();
  JTabbedPane TabbedPanels = new JTabbedPane();
  JPanel AttributesPanel = new JPanel();
  JPanel Attributes = new JPanel();
  JPanel ResetAttributes = new JPanel();

  GridLayout gridLayout1 = new GridLayout();
  JLabel AttributesLabel = new JLabel();
  JList AttributesList = new JList();
  JTextField AttributeValue = new JTextField();
  JLabel ResetAttributesLabel = new JLabel();
  JList ResetAttributesList = new JList();
  JScrollPane ResetScrollPane = new JScrollPane(ResetAttributesList);
  JScrollPane NonResetScrollPane = new JScrollPane(AttributesList);
  JTextField ResetAttributesValue = new JTextField();
  JPanel ConnectorPanel = new JPanel();
  JPanel CommentsPanel = new JPanel();
  CardLayout cardLayout1 = new CardLayout();
  JTextArea _Comment = new JTextArea();
  JTabbedPane inletsTab = new JTabbedPane();
  JTabbedPane outletsTab = new JTabbedPane();
  JLabel inletsLabel = new JLabel();
  JLabel outletsLabel = new JLabel();
  Vector inlets_list = new Vector();
  Vector outlets_list = new Vector ();
  JButton UpButton = new JButton();
  JButton DownButton = new JButton();
  JButton DisplayConnectorButton = new JButton();
  ConnectorHook selected_connector = null;

  JList _current_outlets_list = null;
  volatile boolean _list_loading = false;

    /**
       The Name Field
     */

    /**
       Constructor Using BaseShellHook as parameter
       @roseuid 3E78FE3500AE
     */
    public BaseShellDisplayForm(BaseShellHook pHook) {
      try {
        // perform new creation here as builder does not like it in the initialiser
        AttributesList = new JList(AttributeListModel);
        NonResetScrollPane = new JScrollPane(AttributesList);
        ResetAttributesList = new JList(ResetAttributeListModel);
        ResetScrollPane = new JScrollPane(ResetAttributesList);
        jbInit();
      }
      catch (Exception e) {
        e.printStackTrace();
      }
      _pHook = pHook;
      loadForm();
      this.setBounds(400, 350, 400, 350);
      this.setVisible(true);
    }

    private void LoadAttributesList(){
      AttributeListModel.clear();
      ResetAttributeListModel.clear();

      int number_attributes = BaseShell.GetNumAttributes(_pHook._presentation, _pHook._pObject);
      for (int i = 0; i < number_attributes; i++)
      {
					String Attribute_name = BaseShell.GetAttributeName(_pHook._presentation, _pHook._pObject, i);
					String Attribute_value = BaseShell.GetAttribute(_pHook._presentation, _pHook._pObject, i);
					AttributeListModel.addElement(Attribute_name + " " + Attribute_value);
      }

      number_attributes = BaseShell.GetNumResetAttributes(_pHook._presentation, _pHook._pObject);
      for (int i = 0; i < number_attributes; i++)
      {
					String Attribute_name = BaseShell.GetResetAttributeName(_pHook._presentation, _pHook._pObject, i);
					String Attribute_value = BaseShell.GetResetAttribute(_pHook._presentation, _pHook._pObject, i);
					ResetAttributeListModel.addElement(Attribute_name + " " + Attribute_value);
      }

    }

    private synchronized void LoadConnectionsList(){
      LoadInletsTab();
      LoadOutletsTab();
    }

    public PatchForm GetPatchForm(){
      return _pHook.GetPatchForm();
    }

    private void LoadInletsTab(){
      _list_loading = true;
      inletsTab.removeAll();
      inlets_list.clear();
      int presentation = _pHook._presentation;
      int object = _pHook._pObject;

      // add a tab for all the inlets
      int num_tabs = BaseShell.GetNumInlets(presentation, object);
      for (int i = 0; i < num_tabs; i++)
      {
        DefaultListModel InletListModel = new DefaultListModel();
        JList ConnectorList = new JList(InletListModel);
        ConnectorList.addMouseListener(new BaseShellDisplayForm_InletsList_mouseAdapter(this, ConnectorList, i));
        ConnectorList.addListSelectionListener(new BaseShellDisplayForm_InletsList_listSelectionAdapter(this, ConnectorList, i));

        //String tab_name = BaseShell.GetInletName(presentation, object, i);
        inletsTab.addTab(new String("" + (i+1)), ConnectorList);
        inlets_list.add(InletListModel);
      }

      LoadInletsList();
      _list_loading = false;
    }

    void LoadInletsList(){

      DisplayConnectorButton.setEnabled(false);
      selected_connector = null;
      int presentation = _pHook._presentation;
      int object = _pHook._pObject;
      int index = inletsTab.getSelectedIndex();
      if (index < 0) index = 0;


      if (index < inlets_list.size())
      {
        String tab_name = BaseShell.GetInletName(presentation, object, index);
        inletsLabel.setText(tab_name);

        DefaultListModel tab = (DefaultListModel) inlets_list.elementAt(index);
        tab.clear();
        // load all the connectors into this inlet
        int num_con = BaseShell.GetNumInletConnectors(presentation, object, index);

        for (int i = 0; i < num_con; i++)
        {
          int pCon = BaseShell.GetInletConnector(presentation, object, index, i);
          ConnectorHook pConHook = GetPatchForm().GetConnectorHook(pCon);
          if (pConHook != null)
          {
            tab.addElement(pConHook.getName());
          }
        }
      }
      else
      {
        inletsLabel.setText("");
      }
    }

    private void LoadOutletsTab(){
      _list_loading = true;
      outletsTab.removeAll();
      outlets_list.clear();
      int presentation = _pHook._presentation;
      int object = _pHook._pObject;

      // add a tab for all the inlets
      int num_tabs = BaseShell.GetNumOutlets(presentation, object);
      for (int i = 0; i < num_tabs; i++)
      {
        DefaultListModel OutletListModel = new DefaultListModel();
        JList ConnectorList = new JList(OutletListModel);
        ConnectorList.addMouseListener(new BaseShellDisplayForm_OutletsList_mouseAdapter(this, ConnectorList, i));
        ConnectorList.addListSelectionListener(new BaseShellDisplayForm_OutletsList_listSelectionAdapter(this, ConnectorList, i));
        //String tab_name = BaseShell.GetInletName(presentation, object, i);
        outletsTab.addTab(new String("" + (i+1)), ConnectorList);
        outlets_list.add(OutletListModel);
      }

      LoadOutletsList();
      _list_loading = false;
    }

    void EnableChangeOrderExecution(JList list, int port){
      int list_size = list.getModel().getSize();
      if (list_size < 2)
      {
        UpButton.setEnabled(false);
        DownButton.setEnabled(false);
        _current_outlets_list = null;
      }
      else
      {
        UpButton.setEnabled (list.getSelectedIndex() > 0);
        DownButton.setEnabled (list.getSelectedIndex() < list_size -1);
        _current_outlets_list = list;
      }
    }

    void LoadOutletsList(){
      DisplayConnectorButton.setEnabled(false);
      selected_connector = null;

      int presentation = _pHook._presentation;
      int object = _pHook._pObject;
      int index = outletsTab.getSelectedIndex();
      if (index < 0) index = 0;

      if (index < outlets_list.size())
      {
        String tab_name = BaseShell.GetOutletName(presentation, object, index);
        outletsLabel.setText(tab_name);

        DefaultListModel tab = (DefaultListModel) outlets_list.elementAt(index);
        tab.clear();
        // load all the connectors into this inlet
        int num_con = BaseShell.GetNumOutletConnectors(presentation, object, index);

        for (int i = 0; i < num_con; i++)
        {
          int pCon = BaseShell.GetOutletConnector(presentation, object, index, i);
          ConnectorHook pConHook = GetPatchForm().GetConnectorHook(pCon);
          if (pConHook != null)
          {
            tab.addElement(pConHook.getName());
          }
        }
      }
      else
      {
        outletsLabel.setText("");
      }
    }

    private void Reset(){
      BaseShell.Reset(_pHook._presentation, _pHook._pObject);
      this.loadForm();
    }

    private void SaveAttribute (){
      int index = AttributesList.getSelectedIndex();
      String new_value = AttributeValue.getText();
      BaseShell.SetAttribute(_pHook._presentation, _pHook._pObject, index, new_value);
    }

    private void ReloadAttribute(){
      int index = AttributesList.getSelectedIndex();
      AttributeValue.setText(BaseShell.GetAttribute(_pHook._presentation, _pHook._pObject, index));
    }

    private void SaveResetAttribute (){
      int index = ResetAttributesList.getSelectedIndex();
      String new_value = ResetAttributesValue.getText();
      BaseShell.SetResetAttribute(_pHook._presentation, _pHook._pObject, index, new_value);

    }

    private void ReloadResetAttribute(){
      int index = ResetAttributesList.getSelectedIndex();
      ResetAttributesValue.setText(BaseShell.GetResetAttribute(_pHook._presentation, _pHook._pObject, index));
    }

    private void loadComment(){
      _Comment.setText(_pHook.getComment());
    }
    /**
       @roseuid 3E793CCF024C
     */
    public synchronized void loadForm() {
      this.setTitle(_pHook.getType());
      this._Name.setText(_pHook.getName());
      this._Comment.setText(_pHook.getComment());
      this.ResetAttributesValue.setText("");
      this.AttributeValue.setText("");
      // now load attribute List
      if (AttributesList.isVisible())
      {
        LoadAttributesList();
      }

      if (_Comment.isVisible())
      {
        loadComment();
      }
    }

    private void ClearObject(){
          _pHook._pEditform = null;
          _pHook = null;
    }
    /**
       @roseuid 3E794C950109
     */
    protected void finalize() throws Throwable {
        super.finalize();
    }

    /**
       @roseuid 3E794C950162
     */
    public BaseShellDisplayForm() {
      // this function is used by JBuilder
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    }

    /**
       @roseuid 3E794C950177
     */
    private void jbInit() throws Exception {
    TopPanel.setLayout(TopLayout);
    TopPanel.setMinimumSize(new Dimension(10, 20));
    TopPanel.setPreferredSize(new Dimension(10, 40));
    _Name.setMaximumSize(new Dimension(2147483647, 2147483647));
    _Name.setMinimumSize(new Dimension(100, 20));
    _Name.setPreferredSize(new Dimension(100, 20));
    _Name.setRequestFocusEnabled(true);
    _Name.setText("jTextField1");
    _Name.addKeyListener(new BaseShellDisplayForm__Name_keyAdapter(this));
    TopLayout.setAlignment(FlowLayout.LEFT);
    BottomPanel.setMinimumSize(new Dimension(10, 40));
    BottomPanel.setPreferredSize(new Dimension(10, 40));
    BottomPanel.setLayout(BottomLayout);
    SendButton.setMaximumSize(new Dimension(70, 25));
    SendButton.setMinimumSize(new Dimension(70, 25));
    SendButton.setPreferredSize(new Dimension(70, 25));
    SendButton.setText("Send");
    SendButton.addActionListener(new BaseShellDisplayForm_SendButton_actionAdapter(this));
    ResetButton.setMaximumSize(new Dimension(70, 25));
    ResetButton.setMinimumSize(new Dimension(70, 25));
    ResetButton.setPreferredSize(new Dimension(70, 25));
    ResetButton.setText("Reset");
    ResetButton.addActionListener(new BaseShellDisplayForm_ResetButton_actionAdapter(this));
    ReloadButton.setMaximumSize(new Dimension(70, 25));
    ReloadButton.setMinimumSize(new Dimension(70, 25));
    ReloadButton.setPreferredSize(new Dimension(70, 25));
    ReloadButton.setText("Reload");
    ReloadButton.addActionListener(new BaseShellDisplayForm_ReloadButton_actionAdapter(this));
    NameLabel.setText("Name");
    AttributesPanel.setLayout(gridLayout1);
    AttributesLabel.setBorder(null);
    AttributesLabel.setMaximumSize(new Dimension(2147483647, 15));
    AttributesLabel.setMinimumSize(new Dimension(170, 15));
    AttributesLabel.setPreferredSize(new Dimension(170, 15));
    AttributesLabel.setRequestFocusEnabled(true);
    AttributesLabel.setToolTipText("");
    AttributesLabel.setText("Attributes");
    AttributesList.setBorder(BorderFactory.createLoweredBevelBorder());
    AttributesList.setMaximumSize(new Dimension(2147483647, 2147483647));
    AttributesList.setMinimumSize(new Dimension(170, 130));
    AttributesList.setOpaque(true);
    AttributesList.setPreferredSize(new Dimension(170, 130));
    AttributesList.addMouseListener(new BaseShellDisplayForm_AttributesList_mouseAdapter(this));
    AttributeValue.setBorder(BorderFactory.createLoweredBevelBorder());
    AttributeValue.setMinimumSize(new Dimension(17, 21));
    AttributeValue.setPreferredSize(new Dimension(170, 21));
    AttributeValue.setSelectionStart(0);
    AttributeValue.setText("");
    AttributeValue.addKeyListener(new BaseShellDisplayForm_AttributeValue_keyAdapter(this));
    Attributes.setBorder(BorderFactory.createRaisedBevelBorder());
    ResetAttributes.setBorder(BorderFactory.createRaisedBevelBorder());
    ResetAttributesLabel.setMaximumSize(new Dimension(2147483647, 15));
    ResetAttributesLabel.setMinimumSize(new Dimension(17, 15));
    ResetAttributesLabel.setPreferredSize(new Dimension(170, 15));
    ResetAttributesLabel.setText("Reset Attributes");
    ResetAttributesList.setBorder(BorderFactory.createLoweredBevelBorder());
    ResetAttributesList.setMaximumSize(new Dimension(2147483647, 2147483647));
    ResetAttributesList.setMinimumSize(new Dimension(17, 130));
    ResetAttributesList.setOpaque(true);
    ResetAttributesList.setPreferredSize(new Dimension(170, 130));
    ResetAttributesList.addMouseListener(new BaseShellDisplayForm_ResetAttributesList_mouseAdapter(this));
    ResetAttributesValue.setBorder(BorderFactory.createLoweredBevelBorder());
    ResetAttributesValue.setMaximumSize(new Dimension(2147483647, 2147483647));
    ResetAttributesValue.setMinimumSize(new Dimension(17, 21));
    ResetAttributesValue.setPreferredSize(new Dimension(170, 21));
    ResetAttributesValue.setToolTipText("");
    ResetAttributesValue.setText("");
    ResetAttributesValue.addKeyListener(new BaseShellDisplayForm_ResetAttributesValue_keyAdapter(this));
    CommentsPanel.setLayout(cardLayout1);
    _Comment.setMaximumSize(new Dimension(2147483647, 2147483647));
    _Comment.setMargin(new Insets(0, 0, 0, 0));
    _Comment.setLineWrap(true);
    _Comment.setWrapStyleWord(true);

    _Comment.addKeyListener(new BaseShellDisplayForm__Comment_keyAdapter(this));
    this.setCursor(null);
    this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    this.setState(Frame.NORMAL);
    this.addComponentListener(new BaseShellDisplayForm_this_componentAdapter(this));
    this.addWindowListener(new BaseShellDisplayForm_this_windowAdapter(this));
    ConnectorPanel.setLayout(null);
    inletsTab.setAlignmentX((float) 0.5);
    inletsTab.setBorder(BorderFactory.createLoweredBevelBorder());
    inletsTab.setBounds(new Rectangle(3, 28, 170, 129));
    inletsTab.addChangeListener(new BaseShellDisplayForm_inletsTab_changeAdapter(this));
    outletsTab.setBorder(BorderFactory.createLoweredBevelBorder());
    outletsTab.setBounds(new Rectangle(173, 28, 170, 128));
    outletsTab.addChangeListener(new BaseShellDisplayForm_outletsTab_changeAdapter(this));
    inletsLabel.setText("Inlets");
    inletsLabel.setBounds(new Rectangle(9, 10, 103, 16));
    outletsLabel.setText("Outlets");
    outletsLabel.setBounds(new Rectangle(175, 10, 105, 18));
    ConnectorPanel.addComponentListener(new BaseShellDisplayForm_ConnectorPanel_componentAdapter(this));
    UpButton.setBounds(new Rectangle(337, 116, 25, 20));
    UpButton.setEnabled(false);
    UpButton.setToolTipText("Move Connector Up");
    UpButton.setIcon(new ImageIcon(BaseShellDisplayForm.class.getResource("up.png")));
    UpButton.setText("");
    UpButton.addActionListener(new BaseShellDisplayForm_UpButton_actionAdapter(this));
    DownButton.setBounds(new Rectangle(337, 135, 25, 20));
    DownButton.setEnabled(false);
    DownButton.setToolTipText("Move Connector Down");
    DownButton.setIcon(new ImageIcon(BaseShellDisplayForm.class.getResource("down.png")));
    DownButton.setText("");
    DownButton.addActionListener(new BaseShellDisplayForm_DownButton_actionAdapter(this));
    DisplayConnectorButton.setBounds(new Rectangle(109, 164, 124, 21));
    DisplayConnectorButton.setText("Display Connector");
    DisplayConnectorButton.addActionListener(new BaseShellDisplayForm_DisplayConnectorButton_actionAdapter(this));
    this.getContentPane().add(TopPanel, BorderLayout.NORTH);
    TopPanel.add(NameLabel, null);
    TopPanel.add(_Name, null);
    BottomPanel.add(SendButton, null);
    BottomPanel.add(ResetButton, null);
    this.getContentPane().add(BottomPanel, BorderLayout.SOUTH);
    BottomPanel.add(ReloadButton, null);
    this.getContentPane().add(TabbedPanels, BorderLayout.CENTER);
    TabbedPanels.add(AttributesPanel,  "Attributes");
    AttributesPanel.add(Attributes, null);
    Attributes.add(AttributesLabel, null);
    AttributesPanel.add(ResetAttributes, null);
    ResetAttributes.add(ResetAttributesLabel, null);
    Attributes.add(NonResetScrollPane, null);
    Attributes.add(AttributeValue, null);
    ResetAttributes.add(ResetScrollPane, null);
    //ResetAttributes.add(ResetAttributesList, null);
    ResetAttributes.add(ResetAttributesValue, null);
    TabbedPanels.add(ConnectorPanel,   "Connections");
    ConnectorPanel.add(inletsTab, null);
    TabbedPanels.add(CommentsPanel,  "Comments");
    CommentsPanel.add(_Comment, "jTextArea1");
    ConnectorPanel.add(inletsLabel, null);
    ConnectorPanel.add(outletsTab, null);
    ConnectorPanel.add(outletsLabel, null);
    ConnectorPanel.add(UpButton, null);
    ConnectorPanel.add(DownButton, null);
    ConnectorPanel.add(DisplayConnectorButton, null);
    }

  void ReloadButton_actionPerformed(ActionEvent e) {
    loadForm();
  }

  void OutletsList_ListSlected(JList list, int port) {
    int index = list.getSelectedIndex();
    int presentation = _pHook._presentation;
    int object = _pHook._pObject;

    int pCon = BaseShell.GetOutletConnector(presentation, object, port, index);
    ConnectorHook pConHook = GetPatchForm().GetConnectorHook(pCon);
    if (pConHook != null)
    {
      DisplayConnectorButton.setText(pConHook.getName());
      DisplayConnectorButton.setEnabled(true);
      selected_connector = pConHook;
      GetPatchForm().DisplaySelectedConnectorLine(pConHook);
      EnableChangeOrderExecution (list, port);
    }
  }

  void InletsList_ListSlected(JList list, int port) {
    int index = list.getSelectedIndex();
    int presentation = _pHook._presentation;
    int object = _pHook._pObject;

    int pCon = BaseShell.GetInletConnector(presentation, object, port, index);
    ConnectorHook pConHook = GetPatchForm().GetConnectorHook(pCon);
    if (pConHook != null)
    {
      DisplayConnectorButton.setText(pConHook.getName());
      DisplayConnectorButton.setEnabled(true);
      selected_connector = pConHook;
      GetPatchForm().DisplaySelectedConnectorLine(pConHook);
    }

  }

  void AttributesList_mouseClicked(MouseEvent e) {
    ReloadAttribute ();
  }

  void ResetAttributesList_mouseClicked(MouseEvent e) {
    ReloadResetAttribute();
  }

  void this_windowClosing(WindowEvent e) {
    ClearObject();
  }

  void this_componentHidden(ComponentEvent e) {
    ClearObject();
  }

  void AttributeValue_keyTyped(KeyEvent e) {
    if (e.getKeyChar() == e.VK_ENTER)
    {
      SaveAttribute();
      this.loadForm();
    }
    else if (e.getKeyChar() == e.VK_ESCAPE)
    {
      ReloadAttribute();
    }

  }

  void ResetAttributesValue_keyTyped(KeyEvent e) {
    if (e.getKeyChar() == e.VK_ENTER)
    {
      SaveResetAttribute();
      this.loadForm();
    }
    else if (e.getKeyChar() == e.VK_ESCAPE)
    {
      ReloadResetAttribute();
    }

  }

  void ResetButton_actionPerformed(ActionEvent e) {
    Reset();
  }

  void _Name_keyPressed(KeyEvent e) {
    if (e.getKeyChar() == e.VK_ENTER)
    {
      _pHook.setName(_Name.getText());
    }
    else if (e.getKeyChar() == e.VK_ESCAPE)
    {
      loadForm();
    }
  }

  void _Comment_keyPressed(KeyEvent e) {
    if (e.getKeyChar() == e.VK_ENTER)
    {
      String newText =  _Comment.getText();
      newText= newText.replace('\r', ' ');
      newText= newText.replace('\n', ' ');
      _pHook.setComment(newText);
      this.loadComment();
    }
    else if (e.getKeyChar() == e.VK_ESCAPE)
    {
      loadForm();
    }

  }

  void SendButton_actionPerformed(ActionEvent e) {
    BaseShell.Send(_pHook._presentation, _pHook._pObject);
  }

  void ConnectorPanel_componentShown(ComponentEvent e) {
    LoadConnectionsList();
  }

  void inletsTab_stateChanged(ChangeEvent e) {
    if (!_list_loading)
      LoadInletsList();
  }

  void outletsTab_stateChanged(ChangeEvent e) {
    if (!_list_loading)
      LoadOutletsList();
  }

  void DisplayConnectorButton_actionPerformed(ActionEvent e) {
    if (selected_connector != null)
      selected_connector.DisplayEditForm();
  }

  void UpButton_actionPerformed(ActionEvent e) {
    // move slelected connector up one level
    if (_current_outlets_list != null)
    {
      int index = _current_outlets_list.getSelectedIndex();
      int port = outletsTab.getSelectedIndex();
      int new_index = index - 1;
      if (new_index >= 0) {
        BaseShell.SwapOutletConnector(_pHook._presentation, _pHook._pObject,port,
                                      index, new_index);
        LoadOutletsList();

        _current_outlets_list.setSelectedIndex(new_index);
        EnableChangeOrderExecution (_current_outlets_list, port);
      }
    }
  }

  void DownButton_actionPerformed(ActionEvent e) {
    // move slelected connector down one level
    if (_current_outlets_list != null)
    {
      int index = _current_outlets_list.getSelectedIndex();
      int port = outletsTab.getSelectedIndex();
      int new_index = index + 1;
      if (new_index < _current_outlets_list.getModel().getSize()) {
        BaseShell.SwapOutletConnector(_pHook._presentation, _pHook._pObject,port,
                                      index, new_index);
        LoadOutletsList();

        _current_outlets_list.setSelectedIndex(new_index);
        EnableChangeOrderExecution (_current_outlets_list, port);
      }
    }

  }
}
/*
BaseShellDisplayForm.GetIntval(){return 1;}

*/

class BaseShellDisplayForm_ReloadButton_actionAdapter implements java.awt.event.ActionListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_ReloadButton_actionAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.ReloadButton_actionPerformed(e);
  }
}

class BaseShellDisplayForm_AttributesList_mouseAdapter extends java.awt.event.MouseAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_AttributesList_mouseAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
    adaptee.AttributesList_mouseClicked(e);
  }
}




class BaseShellDisplayForm_ResetAttributesList_mouseAdapter extends java.awt.event.MouseAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_ResetAttributesList_mouseAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
    adaptee.ResetAttributesList_mouseClicked(e);
  }
}

class BaseShellDisplayForm_this_windowAdapter extends java.awt.event.WindowAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_this_windowAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void windowClosing(WindowEvent e) {
    adaptee.this_windowClosing(e);
  }
}

class BaseShellDisplayForm_this_componentAdapter extends java.awt.event.ComponentAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_this_componentAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void componentHidden(ComponentEvent e) {
    adaptee.this_componentHidden(e);
  }
}

class BaseShellDisplayForm_AttributeValue_keyAdapter extends java.awt.event.KeyAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_AttributeValue_keyAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void keyTyped(KeyEvent e) {
    adaptee.AttributeValue_keyTyped(e);
  }
}

class BaseShellDisplayForm_ResetAttributesValue_keyAdapter extends java.awt.event.KeyAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_ResetAttributesValue_keyAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void keyTyped(KeyEvent e) {
    adaptee.ResetAttributesValue_keyTyped(e);
  }
}

class BaseShellDisplayForm_ResetButton_actionAdapter implements java.awt.event.ActionListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_ResetButton_actionAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.ResetButton_actionPerformed(e);
  }
}

class BaseShellDisplayForm__Name_keyAdapter extends java.awt.event.KeyAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm__Name_keyAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void keyPressed(KeyEvent e) {
    adaptee._Name_keyPressed(e);
  }
}

class BaseShellDisplayForm__Comment_keyAdapter extends java.awt.event.KeyAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm__Comment_keyAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void keyPressed(KeyEvent e) {
    adaptee._Comment_keyPressed(e);
  }
}

class BaseShellDisplayForm_SendButton_actionAdapter implements java.awt.event.ActionListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_SendButton_actionAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.SendButton_actionPerformed(e);
  }
}

class BaseShellDisplayForm_ConnectorPanel_componentAdapter extends java.awt.event.ComponentAdapter {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_ConnectorPanel_componentAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void componentShown(ComponentEvent e) {
    adaptee.ConnectorPanel_componentShown(e);
  }
}

class BaseShellDisplayForm_inletsTab_changeAdapter implements javax.swing.event.ChangeListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_inletsTab_changeAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void stateChanged(ChangeEvent e) {
    adaptee.inletsTab_stateChanged(e);
  }
}

class BaseShellDisplayForm_outletsTab_changeAdapter implements javax.swing.event.ChangeListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_outletsTab_changeAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void stateChanged(ChangeEvent e) {
    adaptee.outletsTab_stateChanged(e);
  }
}

class BaseShellDisplayForm_DisplayConnectorButton_actionAdapter implements java.awt.event.ActionListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_DisplayConnectorButton_actionAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.DisplayConnectorButton_actionPerformed(e);
  }
}

class BaseShellDisplayForm_OutletsList_listSelectionAdapter implements javax.swing.event.ListSelectionListener {
  JList adaptee;
  int outlet_number;
  BaseShellDisplayForm owner;


  BaseShellDisplayForm_OutletsList_listSelectionAdapter(BaseShellDisplayForm owner, JList adaptee, int port_num) {
    this.adaptee = adaptee;
    this.outlet_number= port_num;
    this.owner = owner;
  }

  public void valueChanged(ListSelectionEvent e) {
    owner.OutletsList_ListSlected(adaptee, outlet_number);
  }
}

class BaseShellDisplayForm_OutletsList_mouseAdapter extends java.awt.event.MouseAdapter {
  JList adaptee;
  int outlet_number;
  BaseShellDisplayForm owner;

  BaseShellDisplayForm_OutletsList_mouseAdapter(BaseShellDisplayForm owner, JList adaptee, int port_num) {
    this.adaptee = adaptee;
    this.outlet_number= port_num;
    this.owner = owner;
  }
  public void mouseClicked(MouseEvent e) {
    owner.OutletsList_ListSlected(adaptee, outlet_number);
  }
}

class BaseShellDisplayForm_InletsList_listSelectionAdapter implements javax.swing.event.ListSelectionListener {
  JList adaptee;
  int inlet_number;
  BaseShellDisplayForm owner;

  BaseShellDisplayForm_InletsList_listSelectionAdapter(BaseShellDisplayForm owner, JList adaptee, int port_num) {
    this.adaptee = adaptee;
    this.inlet_number= port_num;
    this.owner = owner;
  }
  public void valueChanged(ListSelectionEvent e) {
    owner.InletsList_ListSlected(adaptee, inlet_number);
  }
}

class BaseShellDisplayForm_InletsList_mouseAdapter extends java.awt.event.MouseAdapter {
  JList adaptee;
  int inlet_number;
  BaseShellDisplayForm owner;

  BaseShellDisplayForm_InletsList_mouseAdapter(BaseShellDisplayForm owner, JList adaptee, int port_num) {
    this.adaptee = adaptee;
    this.inlet_number= port_num;
    this.owner = owner;
  }
  public void mouseClicked(MouseEvent e) {
    owner.InletsList_ListSlected(adaptee, inlet_number);
  }
}

class BaseShellDisplayForm_UpButton_actionAdapter implements java.awt.event.ActionListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_UpButton_actionAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.UpButton_actionPerformed(e);
  }
}

class BaseShellDisplayForm_DownButton_actionAdapter implements java.awt.event.ActionListener {
  BaseShellDisplayForm adaptee;

  BaseShellDisplayForm_DownButton_actionAdapter(BaseShellDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.DownButton_actionPerformed(e);
  }
}
