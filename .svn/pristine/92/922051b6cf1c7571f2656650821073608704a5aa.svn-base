
import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import Jni.*;

/*
	<applet code="Frame1" width=200 height=60>
	</applet>

*/

public class Frame1 extends Frame {

		
  public Frame1() {
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
			int presentation = PatchEditor.GetCurrentInterface();
			System.out.println(presentation);
    try  {
      init();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
		
//Component initialization

  private void init() {
    this.setLayout(null);
    this.setSize(new Dimension(481, 386));
  }
//Overriden so we can exit on System Close
		
  protected void processWindowEvent(WindowEvent e) {
    super.processWindowEvent(e);
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      System.exit(0);
    }
  }

}


