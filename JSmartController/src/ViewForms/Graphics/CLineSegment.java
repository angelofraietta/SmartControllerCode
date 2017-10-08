// Source file: c:/develop/PatchEditor/ViewForms/Graphics/CLineSegment.java

/*
Angelo Fraietta

*/

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import java.awt.Panel;


/**
   This class is a segment of a line
 */
public abstract class CLineSegment extends Panel {
    protected Point _start_point = new Point();
    protected Point _end_point = new Point();
    protected int _segment_thickness = 2;
    static final int _default_thickness = 2;
    static final int _highlight_thickness = 4;
    /**
       The CLineFollower creates and positions the CLineSegments on the ViewFormPanel
     */
    public CLineFollower _controller;

    public void Highlight (boolean highlight){
      if (highlight)
      {
        _segment_thickness = _highlight_thickness;
      }
      else
      {
        _segment_thickness = _default_thickness;
      }
    }

    /**
       Constructor
       @roseuid 3B69FEFE0134
     */
    public CLineSegment(CLineFollower controller) {
      _controller = controller;
      this.setBackground(Color.black);
      this.setForeground (Color.black);

      this.addMouseListener(new CLineSegment_this_mouseAdapter(this));

			// comment the following to generate with Rose
			addMouseMotionListener (new MouseMotionAdapter(){
							public void mouseDragged(MouseEvent evt) {
									processDrag (evt.getX(), evt.getY());
							}
					});

			addMouseListener (new MouseAdapter(){
							public void mouseEntered(MouseEvent evt) {
									processMouseEntered (evt.getX(), evt.getY());
							}

							public void mouseExited(MouseEvent evt) {
									processMouseExited (evt.getX(), evt.getY());
							}

					});

    }

    /**
       Frees all references in other objects to this object
       @roseuid 3B69F8530270
     */
    public synchronized void destroy() {
      _controller = null;
    }

    /**
       @roseuid 3B6A481B010C
     */
    public abstract void placeSegment();

  public abstract int getPlacementSize();
    /**
       Assigns the Point values
       @roseuid 3B6E02B201F6
     */
    public void SetStartPoint(Point new_val) {
      _start_point.x = new_val.x;
      _start_point.y = new_val.y;

    }

    public void FollowStartPoint(Point new_val) {
      _start_point = new_val;

    }

    /**
       Assigns the Point values
       @roseuid 3B6E02DD0112
     */
    public void SetEndPoint(Point new_val) {
      _end_point.x = new_val.x;
      _end_point.y = new_val.y;

    }

    public void FollowEndPoint(Point new_val) {
      _end_point = new_val;
    }

    /**
       Process the Mouse Drag
       @roseuid 3B6E360802A8
     */
    protected void processDrag(int x, int y) {
    }

    /**
       Process the Mouse Drag
       @roseuid 3B722A34005B
     */
    protected void processMouseEntered(int x, int y) {
				//System.out.println ("Mouse Entered");
    }

    /**
       Process the Mouse Drag
       @roseuid 3B722A360036
     */
    protected void processMouseExited(int x, int y) {
				//System.out.println ("Mouse EXITED");

    }

  public CLineSegment() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  private void jbInit() throws Exception {
    this.addMouseListener(new CLineSegment_this_mouseAdapter(this));
  }

  void this_mouseClicked(MouseEvent e) {
    _controller.ProcessClick();
  }

  void this_mousePressed(MouseEvent e) {
    _controller.ProcessPopup(e);
  }

  void this_mouseReleased(MouseEvent e) {
    _controller.ProcessPopup(e);
  }
}

class CLineSegment_this_mouseAdapter extends java.awt.event.MouseAdapter {
  CLineSegment adaptee;

  CLineSegment_this_mouseAdapter(CLineSegment adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
    adaptee.this_mouseClicked(e);
  }
  public void mousePressed(MouseEvent e) {
    adaptee.this_mousePressed(e);
  }
  public void mouseReleased(MouseEvent e) {
    adaptee.this_mouseReleased(e);
  }
}
