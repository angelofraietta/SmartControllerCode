// Source file: c:/develop/PatchEditor/ViewForms/Graphics/CHorizLineSegment.java

/*
Angelo Fraietta

*/

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class CHorizLineSegment extends CLineSegment {

    /**
       @roseuid 3B6A4856012F
     */
    public void placeSegment() {
      int length = _start_point.x - _end_point.x;

      int y = _end_point.y;
      int x = _end_point.x;

      if (length < 0)
      {
        length = -length;
        x = _start_point.x;
      }

      setSize (length, _segment_thickness);
      setLocation (x, y);

    }

    public int getPlacementSize(){
      return _start_point.x - _end_point.x;
    }

    /**
       Constructor
       @roseuid 3B6A488402BC
     */
    public CHorizLineSegment(CLineFollower controller) {
      super (controller);
			setCursor (new Cursor (Cursor.N_RESIZE_CURSOR));
    }

    /**
       Process the Mouse Drag
       @roseuid 3B6E3C51005D
     */
    public void processDrag(int x, int y) {
				if (_controller.CanDrag (this))
				{
						_start_point.y += y;
						_end_point.y += y;
						_controller.ProcessDrag (this);
				}
    }
}
