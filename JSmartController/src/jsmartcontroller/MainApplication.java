package jsmartcontroller;

import javax.swing.UIManager;
import java.awt.*;
import Jni.*;
/**
 * <p>Title: Smart Controller</p>
 * <p>Description: Smart Controller Patche Editor and Simulator</p>
 * <p>Copyright: Copyright (c) 2003 Angelo Fraietta</p>
 * <p>Company: Angelo Fraietta</p>
 * @author Angelo Fraietta
 * @version 1.0
 */

public class MainApplication {
  boolean packFrame = false;

  //Construct the application
  public MainApplication() {
    MainFrame frame = new MainFrame();
    //Validate frames that have preset sizes
    //Pack frames that have useful preferred size info, e.g. from their layout
    if (packFrame) {
      frame.pack();
    }
    else {
      frame.validate();
    }
    //Center the window
    Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
    Dimension frameSize = frame.getSize();
    if (frameSize.height > screenSize.height) {
      frameSize.height = screenSize.height;
    }
    if (frameSize.width > screenSize.width) {
      frameSize.width = screenSize.width;
    }
    frame.setLocation((screenSize.width - frameSize.width) / 2, (screenSize.height - frameSize.height) / 2);
    frame.setVisible(true);
  }
  //Main method
  public static void main(String[] args) {
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
      if (!Jni.PatchEditor.Initialise())
      {
        System.out.println("Unable to initialise");
      }
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    new MainApplication();
  }
}