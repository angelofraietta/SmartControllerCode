


// Source file: c:/develop/PatchEditor/ViewForms/Graphics/ViewFormPanel.java

/*
Angelo Fraietta

*/

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import java.awt.Panel;
import java.awt.ScrollPane;
import javax.swing.*;

public class ViewFormPanel extends Panel {

  private static boolean show_mouse = false;
    /**
       This is the starting point of a line that will be used to represent a dragged line
     */
    private Point start_drag_point = null;
    /**
       This is the end point of a line that will be used to represent a dragged line
     */
    private Point end_drag_point = null;
    public ScrollPane _parent;
    public CDragObject _dragObject = null;

    /**
       @roseuid 3B660C3801EC
     */
    public ViewFormPanel(ScrollPane parent) {
      _parent = parent;
    }

    /**
       Updates the size of the window if required. Tests the size against its current size
       @roseuid 3B673A91035D
     */
    public void updateSize(int x, int y) {
        boolean size_change = false;

        Dimension new_size = this.getSize();

        if (y > new_size.height)
        {
          new_size.height = y + 10;
          size_change = true;
        }

        if (x > new_size.width)
        {
          new_size.width = x + 10;
          size_change = true;
        }

        if (size_change)
        {
          this.setSize(new_size);
          if (_parent != null)
          {
            _parent.doLayout();
          }
        }

    }

    /**
       Commences the start drag and sets the active _dragObject
       @roseuid 3B69E8BD0088
     */
    public void startDrag(CDragObject dragObject) {
      _dragObject = dragObject;
    }

    /**
       Adds a CObject box to this and rezisez if necessary
       @roseuid 3B6A384F0388
     */
    public void AddObjectBox(CObjectBox new_object) {
      this.add (new_object, null);
      updateSize (new_object.getLocation().x + new_object.getSize().width,
                  new_object.getLocation().y + new_object.getSize().height);
    }

    /**
       @roseuid 3B6F295302BE
     */
    public void mouseDragged(MouseEvent evt) {
      if (show_mouse)
      {
        System.out.println("Mouse Dragged");
      }

      int x = evt.getX();
      int y = evt.getY();
      if ((x > 0) && (y > 0) && (_dragObject != null))
      {
        _dragObject.processDrag (evt, x, y);
      }
    }

    /**
       @roseuid 3B6F29640273
     */
    public void mouseReleased(MouseEvent evt) {
      if (show_mouse)
      {
        System.out.println("Mouse Released");
      }

      int x = evt.getX();
      int y = evt.getY();

      if (_dragObject != null)
      {
        _dragObject.endDrag(evt, x, y);
      }

      _dragObject = null;

    }

    /**
       @roseuid 3B85AC9C00D2
     */
    public void paint(Graphics g) {
      //g.setXORMode (getBackground());
      if (start_drag_point != null && end_drag_point != null)
      {
        g.drawLine(start_drag_point.x, start_drag_point.y,
                   end_drag_point.x, end_drag_point.y);

        start_drag_point = null;
        end_drag_point = null;
      }
    }

    /**
       Sets the start and end points of the drag line
       @roseuid 3B85B3E60248
     */
    public void DrawDragLine(Point start, Point end) {
				start_drag_point = start;
				end_drag_point = end;
    }

    /**
       Make the connection
       @roseuid 3B85C2E203D5
     */
    public void DoConnection(CTopFollower top, CBottomFollower bottom) {
    }
}
