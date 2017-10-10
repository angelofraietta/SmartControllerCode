// Source file: c:/develop/PatchEditor/ViewForms/Graphics/CVerticalLineSegment.java

/*
Angelo Fraietta

*/

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class CVerticalLineSegment extends CLineSegment {

    /**
       @roseuid 3B6A48560107
     */
    public void placeSegment() {
      int length = _start_point.y - _end_point.y;

      int x = _end_point.x;
      int y = _end_point.y;

      if (length < 0)
      {
        length = -length;
        y = _start_point.y;
      }

      setSize (_segment_thickness, length);
      setLocation (x, y);
    }

    public int getPlacementSize(){
      return _start_point.y - _end_point.y;
    }
    /**
       Constructor
       @roseuid 3B6A4872017F
     */
    public CVerticalLineSegment(CLineFollower controller) {
      super(controller);
			setCursor (new Cursor (Cursor.W_RESIZE_CURSOR));
    }

    /**
       Process the Mouse Drag
       @roseuid 3B6E36060038
     */
    public void processDrag(int x, int y) {
				if (_controller.CanDrag (this))
				{
						_start_point.x += x;
						_end_point.x += x;
						_controller.ProcessDrag (this);
				}
    }
}
