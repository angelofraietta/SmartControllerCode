package ViewForms.Graphics.test;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
//import com.sun.java.swing.*;
//import borland.jbcl.control.*;
//import borland.jbcl.layout.*;
import ViewForms.*;
import javax.swing.*;

/*
	<applet code="Frame1" width=200 height=60>
	</applet>

*/

public class Frame1 extends JFrame {

		JPanel contentPane;
  GridLayout gridLayout1 = new GridLayout();
  ViewForms.Graphics.CObjectBox last_panel = null;
  TextField LeftField = new TextField();
  ScrollPane scrollPane1 = new ScrollPane();
  ViewForms.Graphics.ViewFormPanel panel2 = new ViewForms.Graphics.ViewFormPanel(scrollPane1);
  //add("South", panel1);
  //Construct the frame
		
  public Frame1() {
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try  {
      init();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
		createObjects();
  }
		
//Component initialization

  private void init() {
			contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(null);
    this.setSize(new Dimension(481, 386));
    panel2.setBackground(Color.green);
    panel2.setBounds(new Rectangle(22, 92, 391, 196));
    panel2.setLayout(null);
    scrollPane1.setBounds(new Rectangle(20, 142, 400, 204));
    //this.setTitle("My title");
    contentPane.setBackground(Color.white);
    //this.add(panel2, null);
    contentPane.add(scrollPane1, null);
    scrollPane1.add(panel2, null);
		panel2.doLayout();
		scrollPane1.doLayout();
		panel2.repaint();
  }
//Overriden so we can exit on System Close
		
  protected void processWindowEvent(WindowEvent e) {
    super.processWindowEvent(e);
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      System.exit(0);
    }
  }
		
  void createObjects() {
    ViewForms.Graphics.CTopFollower top;
    ViewForms.Graphics.CBottomFollower bottom;

    ViewForms.Graphics.CObjectBox new_panel = new ViewForms.Graphics.CObjectBox(panel2);
    new_panel.setLocation (100, 100);
    panel2.AddObjectBox (new_panel);

		new_panel.SetNumBottomFollowers (2);
		new_panel.SetNumTopFollowers (2);

    // now make a second  CObjectBox and connect
    new_panel = new ViewForms.Graphics.CObjectBox(panel2);
    new_panel.setLocation (10, 10);
    panel2.AddObjectBox (new_panel);

		new_panel.SetNumBottomFollowers (2);
		new_panel.SetNumTopFollowers (2);


  }

  void button1_actionPerformed(ActionEvent e) {
    if (last_panel != null)
    {
      Point p = last_panel.getLocation();
      LeftField.setText (p.toString ());
      last_panel.repaint();
    }

  }

  void scrollPane1_componentResized(ComponentEvent e) {
  }

  void FreeMemButton_actionPerformed(ActionEvent e) {
    Runtime r = Runtime.getRuntime();
    r.gc();

  }

  void DeleteObjectButton_actionPerformed(ActionEvent e) {
    if (last_panel != null)
    {
      last_panel.destroy();
      last_panel = null;
    }
  }
}


