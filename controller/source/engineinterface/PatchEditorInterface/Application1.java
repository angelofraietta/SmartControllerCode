import Jni.*;

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

    new Application1();
		if (PatchEditor.Initialise())
				{
						System.out.println("Successful Initialisation");
						String def_dir =new String("./.");

						PatchEditor.SetDefaultDirectory (def_dir);
				}
		else
				{
						System.out.println("Unable to initialise");
				}
  }
}

 






