// Source file: C:/develop/JSmartController/src/jsmartcontroller/ConnectorDisplayForm.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;


public class ConnectorDisplayForm extends JFrame {
    public ConnectorHook _pHook;
    JPanel TopPanel = new JPanel ();
    JTextField _Name = new JTextField ();
    JPanel BottomPanel = new JPanel ();
    JTextArea _Comment = new JTextArea ();
    JLabel CommentLabel = new JLabel ();
    BorderLayout borderLayout1 = new BorderLayout ();
    JLabel NameLabel = new JLabel ();
    FlowLayout flowLayout1 = new FlowLayout ();
    BorderLayout borderLayout2 = new BorderLayout ();
  JPanel CentrePanel = new JPanel();
  JTextArea OutletDetails = new JTextArea();
  JTextArea InletDetails = new JTextArea();
  JLabel jLabel1 = new JLabel();
  JLabel jLabel2 = new JLabel();
  JButton DisplayOutlet = new JButton();
  JButton DisplayInlet = new JButton();
  BaseShellHook pOutletBase = null;
  BaseShellHook pInletBase = null;
  JLabel OrderOfConnectionText = new JLabel();

    /**
       Constructor Using Connector Hook
       @roseuid 3E879C360080
     */
    public ConnectorDisplayForm(ConnectorHook pHook) {
      try {
        jbInit();
      }
      catch(Exception e) {
        e.printStackTrace();
      }

      _pHook = pHook;
      loadForm();
      this.setBounds(400, 350, 400, 350);
      this.setVisible(true);

    }

    /**
       Removes references to pHook
       @roseuid 3E879C8502D3
     */
    public void ClearObject() {
      _pHook._pEditform = null;
      _pHook = null;
    }

    /**
       @roseuid 3E87A25F01D2
     */
    ConnectorDisplayForm() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    }

    /**
       @roseuid 3E87A25F022C
     */
    private void loadForm() {
      this._Name.setText(_pHook.getName());
      this._Comment.setText(_pHook.getComment());
      LoadOutletDetails();
      LoadInletDetails();
    }

    synchronized void LoadOutletDetails(){
      int presentation = _pHook._presentation;
      int pCon = _pHook._pObject;
      // display the outlet details
      int p_base = Connector.GetOutletBase(presentation, pCon);
      BaseShellHook b_hook = _pHook.GetPatchForm().GetBaseShellHook(p_base);
      int port_number = Connector.GetOutletNum(presentation, pCon);
      String PortName = BaseShell.GetOutletName(presentation, p_base, port_number);
      OutletDetails.setText("Type - " + b_hook.getType() + "\n"
                            + "Name - " + b_hook.getName() +  "\n" +
                            "Outlet " + (port_number +1 ) + "\n" + PortName);
      pOutletBase = b_hook;

      int connector_order = Connector.GetOutletIndex(presentation, pCon) + 1;
      OrderOfConnectionText.setText("Order of execution: " + connector_order);

    }

    synchronized void LoadInletDetails(){
      int presentation = _pHook._presentation;
      int pCon = _pHook._pObject;
      // display the outlet details
      int p_base = Connector.GetInletBase(presentation, pCon);
      BaseShellHook b_hook = _pHook.GetPatchForm().GetBaseShellHook(p_base);
      int port_number = Connector.GetInletNum(presentation, pCon);
      String PortName = BaseShell.GetInletName(presentation, p_base, port_number);
      InletDetails.setText("Type - "  + b_hook.getType() + "\n"
                           + "Name - " + b_hook.getName() +  "\n" +
                            "Inlet " + (port_number + 1) + "\n" + PortName);
       pInletBase = b_hook;
    }

    /**
       @roseuid 3E87A25F024A
     */
    private void jbInit() throws Exception {
    TopPanel.setBorder(BorderFactory.createRaisedBevelBorder());
    TopPanel.setPreferredSize(new Dimension(30, 30));
    TopPanel.setLayout(flowLayout1);
    _Name.setPreferredSize(new Dimension(150, 21));
    _Name.setText("jTextField1");
    _Name.addKeyListener(new ConnectorDisplayForm__Name_keyAdapter(this));
    BottomPanel.setBorder(BorderFactory.createRaisedBevelBorder());
    BottomPanel.setPreferredSize(new Dimension(80, 80));
    BottomPanel.setLayout(borderLayout2);
    _Comment.setBorder(null);
    _Comment.setText("jTextArea1");
    _Comment.setLineWrap(true);
    _Comment.setWrapStyleWord(true);
    _Comment.addKeyListener(new ConnectorDisplayForm__Comment_keyAdapter(this));
    CommentLabel.setPreferredSize(new Dimension(20, 20));
    CommentLabel.setText("Comment");
    NameLabel.setDebugGraphicsOptions(0);
    NameLabel.setToolTipText("");
    NameLabel.setText("Name");
    flowLayout1.setAlignment(FlowLayout.LEFT);
    this.addComponentListener(new ConnectorDisplayForm_this_componentAdapter(this));
    this.addWindowListener(new ConnectorDisplayForm_this_windowAdapter(this));
    this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    CentrePanel.setLayout(null);
    OutletDetails.setEnabled(false);
    OutletDetails.setBorder(BorderFactory.createLoweredBevelBorder());
    OutletDetails.setText("Outlet Details");
    OutletDetails.setBounds(new Rectangle(12, 55, 174, 113));
    InletDetails.setBounds(new Rectangle(205, 55, 174, 113));
    InletDetails.setText("Inlet Details");
    InletDetails.setEnabled(false);
    InletDetails.setBorder(BorderFactory.createLoweredBevelBorder());
    jLabel1.setText("Outlet Details");
    jLabel1.setBounds(new Rectangle(11, 32, 117, 20));
    jLabel2.setText("InletDetails");
    jLabel2.setBounds(new Rectangle(204, 32, 120, 16));
    DisplayOutlet.setBounds(new Rectangle(13, 169, 173, 21));
    DisplayOutlet.setText("Display Object");
    DisplayOutlet.addActionListener(new ConnectorDisplayForm_DisplayOutlet_actionAdapter(this));
    DisplayInlet.setText("Display Object");
    DisplayInlet.addActionListener(new ConnectorDisplayForm_DisplayInlet_actionAdapter(this));
    DisplayInlet.setBounds(new Rectangle(206, 169, 173, 21));
    OrderOfConnectionText.setText("jLabel3");
    OrderOfConnectionText.setBounds(new Rectangle(11, 4, 381, 20));
    this.getContentPane().add(TopPanel, BorderLayout.NORTH);
    TopPanel.add(NameLabel, null);
    TopPanel.add(_Name, null);
    this.getContentPane().add(BottomPanel, BorderLayout.SOUTH);
    BottomPanel.add(CommentLabel, BorderLayout.NORTH);
    BottomPanel.add(_Comment, BorderLayout.CENTER);
    this.getContentPane().add(CentrePanel, BorderLayout.CENTER);
    CentrePanel.add(DisplayOutlet, null);
    CentrePanel.add(DisplayInlet, null);
    CentrePanel.add(OutletDetails, null);
    CentrePanel.add(InletDetails, null);
    CentrePanel.add(jLabel1, null);
    CentrePanel.add(jLabel2, null);
    CentrePanel.add(OrderOfConnectionText, null);
    }

  void this_componentHidden(ComponentEvent e) {
    ClearObject();
  }

  void this_windowClosing(WindowEvent e) {
    ClearObject();
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
      this._Comment.setText(_pHook.getComment());
    }
    else if (e.getKeyChar() == e.VK_ESCAPE)
    {
      loadForm();
    }

  }

  public PatchForm GetPatchForm(){
    return _pHook.GetPatchForm();
  }

  void DisplayOutlet_actionPerformed(ActionEvent e) {
    if (pOutletBase != null)
    {
      pOutletBase.DisplayEditForm();
      GetPatchForm().SetSelectedBaseShellHook(pOutletBase);
    }
  }

  void DisplayInlet_actionPerformed(ActionEvent e) {
    if (pInletBase != null)
      {
        pInletBase.DisplayEditForm();
        GetPatchForm().SetSelectedBaseShellHook(pInletBase);
      }
  }

}
/*
ConnectorDisplayForm.LoadForm(){

    }

*/

class ConnectorDisplayForm_this_componentAdapter extends java.awt.event.ComponentAdapter {
  ConnectorDisplayForm adaptee;

  ConnectorDisplayForm_this_componentAdapter(ConnectorDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void componentHidden(ComponentEvent e) {
    adaptee.this_componentHidden(e);
  }
}

class ConnectorDisplayForm_this_windowAdapter extends java.awt.event.WindowAdapter {
  ConnectorDisplayForm adaptee;

  ConnectorDisplayForm_this_windowAdapter(ConnectorDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void windowClosing(WindowEvent e) {
    adaptee.this_windowClosing(e);
  }
}

class ConnectorDisplayForm__Name_keyAdapter extends java.awt.event.KeyAdapter {
  ConnectorDisplayForm adaptee;

  ConnectorDisplayForm__Name_keyAdapter(ConnectorDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void keyPressed(KeyEvent e) {
    adaptee._Name_keyPressed(e);
  }
}

class ConnectorDisplayForm__Comment_keyAdapter extends java.awt.event.KeyAdapter {
  ConnectorDisplayForm adaptee;

  ConnectorDisplayForm__Comment_keyAdapter(ConnectorDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void keyPressed(KeyEvent e) {
    adaptee._Comment_keyPressed(e);
  }
}

class ConnectorDisplayForm_DisplayOutlet_actionAdapter implements java.awt.event.ActionListener {
  ConnectorDisplayForm adaptee;

  ConnectorDisplayForm_DisplayOutlet_actionAdapter(ConnectorDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.DisplayOutlet_actionPerformed(e);
  }
}

class ConnectorDisplayForm_DisplayInlet_actionAdapter implements java.awt.event.ActionListener {
  ConnectorDisplayForm adaptee;

  ConnectorDisplayForm_DisplayInlet_actionAdapter(ConnectorDisplayForm adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.DisplayInlet_actionPerformed(e);
  }
}
