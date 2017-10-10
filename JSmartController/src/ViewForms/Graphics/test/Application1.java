
package ViewForms.Graphics.test;

public class Application1 {
  boolean packFrame = false;

  //Construct the application
  
  public Application1() {
    Frame1 frame = new Frame1();
    //Validate frames that have preset sizes
    //Pack frames that have useful preferred size info, e.g. from their layout
    if (packFrame)
      frame.pack();
    else
      frame.validate();

    frame.setVisible(true);

  }
//Main method
  
  public static void main(String[] args) {
			/*try  {
				      UIManager.setLookAndFeel(new com.sun.java.swing.plaf.windows.WindowsLookAndFeel());
      //UIManager.setLookAndFeel(new com.sun.java.swing.plaf.motif.MotifLookAndFeel());
      //UIManager.setLookAndFeel(new com.sun.java.swing.plaf.metal.MetalLookAndFeel());
				
    }
    catch (Exception e) {
    }
			*/
    new Application1();
  }
}

 






