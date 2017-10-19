package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 * <p>Title: CV to OSC Converter</p>
 * <p>Description: Converts Control Voltages to OSC messages</p>
 * <p>Copyright: Copyright Angelo Fraietta (c) 2004</p>
 * <p>Company: Angelo Fraietta</p>
 * @author Angelo Fraietta
 * @version 1.0
 */

public class CVSim extends JFrame {
  JPanel contentPane;
  final int num_controls = 16;
  final int max_cv = 1023; // Modify this value as we increase the reesolution Of the Harware deivce
  JSlider sliders [] = new JSlider [num_controls];
  JCheckBox checkboxes [] = new JCheckBox[num_controls];
  static CVSim sim = null;

  JPanel CVPanel = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel DigPanel = new JPanel();
  CardLayout cardLayout1 = new CardLayout();
  GridLayout gridLayout1 = new GridLayout();
  CardLayout cardLayout2 = new CardLayout();
  GridLayout gridLayout2 = new GridLayout();
  boolean dig_states [] = new boolean [num_controls];
  CVSimUpdater _updater = null;
  JMenuBar jMenuBar1 = new JMenuBar();
  JMenu mnuShowOutputs = new JMenu();

  //Construct the frame
  public CVSim() {
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    _updater = new CVSimUpdater (this, 100);
    _updater.Start();
  }
  //Component initialization
  private void jbInit() throws Exception  {
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(borderLayout1);
    this.setSize(new Dimension(600, 200));
    this.setTitle("Smart Controller Simulator Inputs");

    CVPanel.setBorder(BorderFactory.createLoweredBevelBorder());
    CVPanel.setLayout(gridLayout1);
    DigPanel.setBorder(BorderFactory.createLoweredBevelBorder());
    DigPanel.setLayout(gridLayout2);
    contentPane.setPreferredSize(new Dimension(20, 28));
    mnuShowOutputs.setText("Show Simulator Outputs");
    mnuShowOutputs.addActionListener(new CVSim_mnuShowOutputs_actionAdapter(this));
    jMenuBar1.add(mnuShowOutputs);
    contentPane.add(CVPanel,  BorderLayout.CENTER);
    contentPane.add(DigPanel,  BorderLayout.SOUTH);

    for (int i=0; i < num_controls; i++)
    {
      sliders[i] = new JSlider();
      JSlider Slider = sliders[i];
      Slider.setOrientation(JSlider.VERTICAL);
      Slider.setToolTipText(new String ("CV " + (i+1)));
      Slider.setMaximum(max_cv);
      Slider.setValue(0);
      Slider.setBounds(new Rectangle(11, 33, 30, 79));
      Slider.addChangeListener(new CVSim_Sliders_changeAdapter(this, i));
      CVPanel.add(Slider, null);
    }

    for (int i=0; i < num_controls; i++)
    {
      checkboxes[i] = new JCheckBox();
      JCheckBox CheckBox = checkboxes[i];
      CheckBox.setHorizontalAlignment(SwingConstants.CENTER);
      CheckBox.setHorizontalTextPosition(SwingConstants.CENTER);
      CheckBox.setText(new String ("Dig" + (i+1)));
      CheckBox.setVerticalAlignment(SwingConstants.BOTTOM);
      CheckBox.setVerticalTextPosition(SwingConstants.BOTTOM);
      dig_states [i] = false;
      CheckBox.addMouseListener(new CVSim_Checkboxes_changeAdapter(this, i));
      DigPanel.add(CheckBox, null);
    }


  }

  public static void ShowCVSim() {
    if (sim == null)
    {
      sim = new CVSim();
    }
    sim.setVisible(true);

  }

  public static CVSim GetCVSim(){
    return sim;
  }

  void Slider_stateChanged(ChangeEvent e, int index) {
    float f = sliders[index].getValue();
    f /= sliders[index].getMaximum();
    //System.out.println("/angelo/cv" + (index +1) + " " + (f));
    Jni.PatchEditor.AddAnalogueValue(index, f);
  }

  void Checkbox_stateChanged(int index) {
    //int value = 0;
    //if (checkboxes[index].isSelected())
    //{
    //  value = 1;
    //}
    //System.out.println("/angelo/dig" + (index + 1)+" " + value);
    Jni.PatchEditor.AddDigitalValue(index, checkboxes[index].isSelected());
    dig_states[index] = checkboxes[index].isSelected();
  }

  public void RefreshView(){
    for (int i = 0; i < num_controls; i++)
    {
      if (dig_states[i] != checkboxes[i].isSelected())
      {
        Jni.PatchEditor.AddDigitalValue(i, checkboxes[i].isSelected());
        dig_states[i] = checkboxes[i].isSelected();
      }
    }
  }

  void mnuShowOutputs_actionPerformed(ActionEvent e) {
    CVOutSim.ShowCVOutSim();
  }


}




class CVSim_Sliders_changeAdapter implements javax.swing.event.ChangeListener {
  CVSim adaptee;
  int index;

  CVSim_Sliders_changeAdapter(CVSim adaptee, int index) {
    this.adaptee = adaptee;
    this.index = index;
  }
  public void stateChanged(ChangeEvent e) {
    adaptee.Slider_stateChanged(e, index);
  }
}

class CVSim_Checkboxes_changeAdapter extends java.awt.event.MouseAdapter {
  CVSim adaptee;
  int index;

  CVSim_Checkboxes_changeAdapter(CVSim adaptee, int index) {
    this.adaptee = adaptee;
    this.index = index;
  }
  public void mouseClicked(MouseEvent e)  {
    adaptee.Checkbox_stateChanged(index);
  }
}

class CVSimUpdater implements ActionListener {
    javax.swing.Timer timer;
    CVSim _parent;

    /**
       @roseuid 3EB1ED750021
     */
    CVSimUpdater(CVSim parent, int time) {
    timer = new javax.swing.Timer(time, this);
    _parent = parent;
    }

    /**
       @roseuid 3EB1ED750024
     */
    public void actionPerformed(ActionEvent e) {
      _parent.RefreshView();
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

class CVSim_mnuShowOutputs_actionAdapter implements java.awt.event.ActionListener {
  CVSim adaptee;

  CVSim_mnuShowOutputs_actionAdapter(CVSim adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuShowOutputs_actionPerformed(e);
  }
}
