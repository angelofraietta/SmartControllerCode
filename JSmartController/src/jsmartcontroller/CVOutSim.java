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

public class CVOutSim extends JFrame {
  JPanel contentPane;
  final int num_controls = 16;
  final int max_cv = 255; // Modify this alue as we increase the reesolution Of the Harware deivce
  JSlider sliders [] = new JSlider [num_controls];
  JPanel dig_outputs [] = new JPanel[num_controls];

  boolean dig_states [] = new boolean [num_controls];
  float ana_states [] = new float [num_controls];

  static CVOutSim sim = null;

  JPanel CVPanel = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel DigPanel = new JPanel();
  CardLayout cardLayout1 = new CardLayout();
  GridLayout gridLayout1 = new GridLayout();
  CardLayout cardLayout2 = new CardLayout();
  GridLayout gridLayout2 = new GridLayout();

  CVOutSimUpdater _updater = null;
  //Construct the frame
  public CVOutSim() {
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }

    _updater = new CVOutSimUpdater (this, 100);
    _updater.Start();

  }
  //Component initialization
  private void jbInit() throws Exception  {
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(borderLayout1);
    this.setSize(new Dimension(600, 100));
    this.setTitle("Smart Controller Simulator Outputs");

    CVPanel.setBorder(BorderFactory.createLoweredBevelBorder());
    CVPanel.setLayout(gridLayout1);
    DigPanel.setBorder(BorderFactory.createLoweredBevelBorder());
    DigPanel.setLayout(gridLayout2);
    contentPane.setPreferredSize(new Dimension(20, 28));
    contentPane.add(CVPanel,  BorderLayout.CENTER);
    contentPane.add(DigPanel,  BorderLayout.SOUTH);
    for (int i=0; i < num_controls; i++)
    {
      sliders[i] = new JSlider();
      JSlider Slider = sliders[i];
      Slider.setEnabled(false);
      Slider.setOrientation(JSlider.VERTICAL);
      Slider.setToolTipText(new String ("CV " + (i+1)));
      Slider.setMaximum(max_cv);
      Slider.setValue(0);
      Slider.setBounds(new Rectangle(11, 33, 30, 79));
      CVPanel.add(Slider, null);
      ana_states [i] = 0;
    }

    for (int i=0; i < num_controls; i++)
    {
      dig_outputs[i] = new JPanel();
      JPanel dig_output = dig_outputs[i];
      dig_output.setPreferredSize(new Dimension(20, 20));
      dig_output.setBorder(BorderFactory.createLoweredBevelBorder());
//      dig_output.setForeground(Color.GREEN);
      dig_output.setBackground(Color.GREEN);
      dig_states[i] = false;
      DigPanel.add(dig_output, null);
    }


  }

  void UpdateDigState (int channel, boolean state){
    if (state)
    {
      dig_outputs [channel].setBackground(Color.RED);
    }
    else
    {
      dig_outputs [channel].setBackground(Color.GREEN);
    }
    dig_states[channel] = state;
  }

  void UpdateAnaState (int channel, float state){
    float new_val = state * sliders[channel].getMaximum();
    sliders[channel].setValue((int)new_val);
    ana_states[channel] = state;
  }

  public void RefreshView(){
    for (int i = 0; i < num_controls; i++)
    {
      boolean new_state = Jni.PatchEditor.GetDigitalValue(i);
      if (new_state != dig_states[i])
      {
        UpdateDigState (i, new_state);
      }
      float new_cv = Jni.PatchEditor.GetAnalogueValue(i);
      if (new_cv != ana_states[i])
      {
        UpdateAnaState (i, new_cv);
      }
    }
  }

  public static void ShowCVOutSim() {
    if (sim == null)
    {
      sim = new CVOutSim();
    }

    CVSim in_sim = CVSim.GetCVSim();
    if ( in_sim != null && in_sim.isShowing())
    {
      Point sim_location = new Point (in_sim.getLocation());
      sim.setLocation(sim_location.x, sim_location.y + in_sim.getHeight() );
    }

    sim.setVisible(true);

  }

}


class CVOutSimUpdater implements ActionListener {
    javax.swing.Timer timer;
    CVOutSim _parent;

    /**
       @roseuid 3EB1ED750021
     */
    CVOutSimUpdater(CVOutSim parent, int time) {
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


