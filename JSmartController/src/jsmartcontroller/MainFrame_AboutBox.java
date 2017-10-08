package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

/**
 * <p>Title: CV to OSC Converter</p>
 * <p>Description: Converts Control Voltages to OSC messages</p>
 * <p>Copyright: Copyright Angelo Fraietta (c) 2004</p>
 * <p>Company: Angelo Fraietta</p>
 * @author Angelo Fraietta
 * @version 1.0
 */

public class MainFrame_AboutBox extends JDialog implements ActionListener {

  JPanel panel1 = new JPanel();
  JPanel panel2 = new JPanel();
  JPanel insetsPanel1 = new JPanel();
  JPanel insetsPanel3 = new JPanel();
  JButton button1 = new JButton();
  JLabel imageLabel = new JLabel();
  JLabel label1 = new JLabel();
  JLabel label2 = new JLabel();
  JLabel label3 = new JLabel();
  JLabel label4 = new JLabel();
  ImageIcon image1 = new ImageIcon();
  BorderLayout borderLayout2 = new BorderLayout();
  GridLayout gridLayout1 = new GridLayout();
  String product = "CV to OSC Converter";
  String version = "1.0";
  String copyright = "Copyright Angelo Fraietta (c) 2004";
  String comments = "Converts Control Voltages to OSC messages";
  JTextArea jTextArea1 = new JTextArea();
  public MainFrame_AboutBox(Frame parent) {
    super(parent);
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  //Component initialization
  private void jbInit() throws Exception  {
    image1 = new ImageIcon(jsmartcontroller.MainFrame.class.getResource("about.png"));
    imageLabel.setIcon(new ImageIcon(MainFrame_AboutBox.class.getResource("OzcoLogo.gif")));
    imageLabel.setIconTextGap(4);
    imageLabel.setBounds(new Rectangle(49, 117, 292, 85));
    this.setModal(true);
    this.setTitle("About");
    panel1.setLayout(null);
    panel2.setLayout(borderLayout2);
    gridLayout1.setRows(4);
    gridLayout1.setColumns(1);
    label1.setText("Smart Controller");
    label2.setText("Version 2.8");
    label3.setText(copyright);
    label4.setText("Enables integration of CV, MIDI, OSC and Programable Logic Control");
    insetsPanel3.setLayout(gridLayout1);
    insetsPanel3.setBorder(BorderFactory.createEmptyBorder(10, 60, 10, 10));
    insetsPanel3.setPreferredSize(new Dimension(287, 80));
    button1.setText("Ok");
    button1.addActionListener(this);
    jTextArea1.setBackground(UIManager.getColor("control"));
    jTextArea1.setEnabled(false);
    jTextArea1.setVerifyInputWhenFocusTarget(true);
    jTextArea1.setDisabledTextColor(Color.black);
    jTextArea1.setEditable(false);
    jTextArea1.setText("This project has been assisted by the Commonwealth Government through " +
    "the Australia Council, its arts funding and advisory body.");
    jTextArea1.setLineWrap(true);
    jTextArea1.setWrapStyleWord(true);
    jTextArea1.setBounds(new Rectangle(29, 205, 358, 60));
    insetsPanel1.setBounds(new Rectangle(0, 265, 400, 35));
    panel2.setBounds(new Rectangle(0, 0, 400, 115));
    panel1.setPreferredSize(new Dimension(400, 320));
    this.getContentPane().add(panel1, null);
    insetsPanel3.add(label1, null);
    insetsPanel3.add(label2, null);
    insetsPanel3.add(label3, null);
    insetsPanel3.add(label4, null);
    panel1.add(jTextArea1, null);
    panel1.add(imageLabel, null);
    panel2.add(insetsPanel3, BorderLayout.CENTER);
    insetsPanel1.add(button1, null);
    panel1.add(insetsPanel1, null);
    panel1.add(panel2, null);
    setResizable(false);
  }
  //Overridden so we can exit when window is closed
  protected void processWindowEvent(WindowEvent e) {
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      cancel();
    }
    super.processWindowEvent(e);
  }
  //Close the dialog
  void cancel() {
    dispose();
  }
  //Close the dialog on a button event
  public void actionPerformed(ActionEvent e) {
    if (e.getSource() == button1) {
      cancel();
    }
  }
}