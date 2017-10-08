// Source file: c:/develop/PatchEditor/ViewForms/Graphics/CLineFollower.java

/*
Angelo Fraietta

*/

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import java.awt.Point;
import javax.swing.*;


/**
   Distance for the first and last segments
 */
public class CLineFollower {
    /**
       This is the ammout of space required as a leader for lines that go in the opposite direction. i.i. if the line direction is opposite to the positioning of the objects
     */
    public static int _segment_leader = 10;
    /**
       The starting point of the Segments
     */
    public Point _start_point = new Point();
    /**
       The end point
     */
    public Point _end_point = new Point();
    /**
       This si the maximum number of points apart from _start_point and _end_point
     */
    private static final int _num_points = 6;
    /**
       This is the x offset from the centre of the line. This ofset prevents lines from topfollowers overlapping those from bottom followers
     */
    private static final int _line_offset = 2;

    static CLineFollower _current_line; // this is the selected Line

    public CTopFollower _top;
    public CBottomFollower _bottom;
    protected Color _colour = Color.black;
    protected boolean is_coloured = false;

    /**
       The CLineFollower creates and positions the CLineSegments on the ViewFormPanel
     */
    public Vector _segments = new Vector();
    public ViewFormPanel _parent;
    public Point _line_points[] = new Point [_num_points];
    public int _tag = 0;
    JPopupMenu jPopupMenu1 = new JPopupMenu();
    JMenuItem DeleteMenu = new JMenuItem();
    JMenuItem mnuEditConnector = new JMenuItem();
    JMenuItem mnuMake5Line = new JMenuItem();
    JMenuItem mnuMake3Line = new JMenuItem();
    JMenuItem mnuMake7Line = new JMenuItem();
    JMenuItem mnuSetColour = new JMenuItem();
    JMenuItem mnuClearColour = new JMenuItem(); // value that will be used for colour

    /**
       @roseuid 3B68F13002AC
     */
    public CLineFollower(CTopFollower top, CBottomFollower bottom, ViewFormPanel parent) {
      _parent = parent;
      _top = top;
      _start_point = top.GetCentrePosition();
			_start_point.x -= _line_offset;

      _bottom = bottom;
      _end_point = bottom.GetCentrePosition();
			_end_point.x += _line_offset;
      _top.AddFollower (this);
      _bottom.AddFollower (this);
       createSegments();

       try {
           jbInit();
         }
         catch(Exception e) {
           e.printStackTrace();
         }

    }

    public void SetColour(Color c)
    {
      int num_segments = _segments.size();

      for (int i = 0; i < num_segments; i++)
      {
        CLineSegment segment = (CLineSegment) _segments.get(i);
        segment.setForeground (c);
        segment.setBackground(c);
        segment.placeSegment();
        segment.repaint();
      }
    }

    public void ClearColour()
    {
      int num_segments = _segments.size();

      for (int i = 0; i < num_segments; i++)
      {
        CLineSegment segment = (CLineSegment) _segments.get(i);

        if (i == num_segments -1) // then it is the BottomSegment
        {
          segment.setForeground(CBottomFollower._colour);
          segment.setBackground(CBottomFollower._colour);
        }
        else
        {
          segment.setForeground(CTopFollower._colour);
          segment.setBackground(CTopFollower._colour);
        }
        segment.placeSegment();
        segment.repaint();
      }
    }

    /**
       Frees all references in other objects to this object
       @roseuid 3B69DD3E011C
     */
    public synchronized void destroy() {
      if (_top != null)
      {
        _top.RemoveFollower (this);
      }

      if (_bottom != null)
      {
        _bottom.RemoveFollower (this);
      }

      // now destroy all lines
       // first destroy all followers
      int num_elements = _segments.size();
      for (int i = 0; i < num_elements; i++)
      {
        CLineSegment follower = (CLineSegment)_segments.elementAt(i);
        follower.destroy();
        _parent.remove (follower);
      }

      _segments.removeAllElements();

      // remove reference to _parent
      _parent = null;

    }

    public void RemoveSegments()
    {
      // now destroy all lines
      // first destroy all followers
      int num_elements = _segments.size();
      for (int i = 0; i < num_elements; i++)
      {
        CLineSegment follower = (CLineSegment)_segments.elementAt(i);
        follower.destroy();
        _parent.remove (follower);
      }

      _segments.removeAllElements();

    }

    public void Build3SegmentLine()
    {
      RemoveSegments();
      Rectangle min_size = CalculateMinDimensions();
      Create3Segments (min_size);
      mnuMake7Line.setEnabled(true);
      mnuMake5Line.setEnabled(true);
      mnuMake3Line.setEnabled(true);
    }

    public void Build5SegmentLine()
    {
      RemoveSegments();
      Rectangle min_size = CalculateMinDimensions();
      Create5Segments (min_size);
      mnuMake3Line.setEnabled(true);
      mnuMake5Line.setEnabled(true);
      mnuMake7Line.setEnabled(true);
    }

    public void Build7SegmentLine()
    {
      RemoveSegments();
      Rectangle min_size = CalculateMinDimensions();
      Create7Segments (min_size);
      mnuMake3Line.setEnabled(true);
      mnuMake5Line.setEnabled(true);
      mnuMake7Line.setEnabled(true);

    }

    /**
       Creates the segments and joins them from _top to _bottom with three segments
       @roseuid 3B69FE4100F6
     */
    private void createSegments() {
      Rectangle min_size = CalculateMinDimensions();

      if (_start_point.y <= min_size.y)
      {
        Create5Segments (min_size);
      }
      else
      {
        Create3Segments (min_size);
      }
    }

    /**
       Calculates the minimum rectangle which defines the positions of the segments
       @roseuid 3B6A0287035C
     */
    private Rectangle CalculateMinDimensions() {
      // first get the the Positions of the top and bottom
      Point start = _top.GetCentrePosition();
      Point end = _bottom.GetCentrePosition();

      int height;
      int width;
      int x;
      int y;

      if (start.x < end.x)
      {
        x = start.x;
        width = end.x - start.x;
      }
      else
      {
        x = end.x;
        width = start.x - end.x;
      }

      if (start.y < end.y)
      {
        y = start.y;
        height = end.y - start.y;
      }
      else
      {
        y = end.y;
        height = start.y - end.y;
      }

      return new Rectangle (x, y, width, height);
    }

    /**
       Create the Segments in the direction of stepping down to the left
       Assumes _start_point.y <= _end_point.y
       @roseuid 3B6A33D90322
     */
    private void Create5Segments(Rectangle area) {
      // in this instance we will step down before we step up,
      //creating five segments instead of three

      //also set the first and last segments to have the default cursor

      // first see if we are drawing left or right
      //boolean moving_right = area.x == _start_point.x;
      boolean moving_right = _start_point.x < _end_point.x;

      CLineSegment current_segment;
      Point current_point = new Point(_start_point);
      Point end_point = new Point(current_point);
      end_point.y -= _segment_leader;

      // create the top segment first with a height of The segment leader
      _line_points [0] = new Point (end_point);
      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _start_point;
      current_segment._end_point = _line_points [0];
      current_segment.placeSegment();
			current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));
			current_segment.setForeground (_colour);
			current_segment.setBackground (_colour);

      current_segment.repaint();
      _segments.addElement (current_segment);

      // create a leader accross
      current_point.x = end_point.x;
      current_point.y = end_point.y;

      if (moving_right)
      {
        //end_point.x += _segment_leader;
        end_point.x += area.width / 2;
      }
      else
      {
        end_point.x -= area.width / 2; //_segment_leader;
      }

      _line_points [1] = new Point (end_point);

      current_segment = new CHorizLineSegment (this);
      _parent.add(current_segment, null);

      current_segment._start_point = _line_points [0];
      current_segment._end_point = _line_points [1];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);

      // create segment going down into the centre of the two
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      end_point.y += area.height + _segment_leader * 2 ;

      _line_points [2] = new Point (end_point);


      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _line_points [1];
      current_segment._end_point = _line_points [2];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);


      // create segment going above _leader
      current_point.x = end_point.x;
      current_point.y = end_point.y ;
      end_point.x = _end_point.x;
      _line_points [3] = new Point (end_point);

      current_segment = new CHorizLineSegment (this);
      _parent.add(current_segment, null);

      current_segment._start_point = _line_points [2];
      current_segment._end_point = _line_points [3];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);


      // create last segment
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      end_point = _end_point;

      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _line_points [3];
      current_segment._end_point = _end_point;

      current_segment.placeSegment();
      current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));
      current_segment.setForeground (_colour);
      current_segment.setBackground (_colour);

      current_segment.repaint();
      _segments.addElement (current_segment);
    }

    private void Create7Segments(Rectangle area) {
      // in this instance we will step down before we step up,
      //creating five segments instead of three

      //also set the first and last segments to have the default cursor

      // first see if we are drawing left or right
      //boolean moving_right = area.x == _start_point.x;
      boolean moving_right = _start_point.x < _end_point.x;

      CLineSegment current_segment;
      Point current_point = new Point(_start_point);
      Point end_point = new Point(current_point);
      end_point.y -= _segment_leader;

      // create the top segment first with a height of The segment leader
      _line_points [0] = new Point (end_point);
      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _start_point;
      current_segment._end_point = _line_points [0];
      current_segment.placeSegment();
                        current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));
                        current_segment.setForeground (_colour);
                        current_segment.setBackground (_colour);

      current_segment.repaint();
      _segments.addElement (current_segment);

      // create a leader accross
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      if (moving_right)
      {
        end_point.x += _segment_leader;
      }
      else
      {
        end_point.x -= _segment_leader;
      }
      _line_points [1] = new Point (end_point);

      current_segment = new CHorizLineSegment (this);
      _parent.add(current_segment, null);

      current_segment._start_point = _line_points [0];
      current_segment._end_point = _line_points [1];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);

      // create segment going down into the centre of the two
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      end_point.y += area.height / 2 + _segment_leader;

      _line_points [2] = new Point (end_point);


      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _line_points [1];
      current_segment._end_point = _line_points [2];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);


      //create the segment going accross
      current_point.x = end_point.x;
      current_point.y = end_point.y;

      if (moving_right)
      {
        end_point.x = _end_point.x - _segment_leader;
      }
      else
      {
        end_point.x = _end_point.x + _segment_leader;
      }

      _line_points [3] = new Point (end_point);

      current_segment = new CHorizLineSegment (this);
      _parent.add(current_segment, null);

      current_segment._start_point = _line_points [2];
      current_segment._end_point = _line_points [3];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);

      // create segment going beyond distance of _leader
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      end_point.y = _end_point.y + _segment_leader;

      _line_points [4] = new Point (end_point);
      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _line_points [3];
      current_segment._end_point = _line_points [4];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);

      // create segment going above _leader
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      end_point.x = _end_point.x;
      _line_points [5] = new Point (end_point);

      current_segment = new CHorizLineSegment (this);
      _parent.add(current_segment, null);

      current_segment._start_point = _line_points [4];
      current_segment._end_point = _line_points [5];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);


      // create last segment
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      end_point = _end_point;

      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _line_points [5];
      current_segment._end_point = _end_point;

      current_segment.placeSegment();
      current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));
      current_segment.setForeground (_colour);
      current_segment.setBackground (_colour);

      current_segment.repaint();
      _segments.addElement (current_segment);


    }

    /**
       Create the Segments in the direction of stepping down to the right
       Assumes _start_point.x <= _end_point.x and
       _start_point.y <= _end_point.y
       @roseuid 3B6A34490200
     */
    private void Create3Segments(Rectangle area) {
      // in this instance we will create leaders of length zero

      CLineSegment current_segment;
      Point current_point = new Point(_start_point);
      Point end_point = new Point(current_point);

			// set the y to half the distance of the height
      end_point.y = area.y + area.height / 2;

      // create the top segment first with a height of The segment leader
      _line_points [0] = new Point (end_point);
      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _start_point;
      current_segment._end_point = _line_points [0];
      current_segment.placeSegment();
      current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));
      current_segment.setForeground (_colour);
      current_segment.setBackground (_colour);
      current_segment.repaint();
      _segments.addElement (current_segment);


      //create the segment going accross
      current_point.x = end_point.x;
      current_point.y = end_point.y;

      end_point.x = _end_point.x;

      _line_points [1] = new Point (end_point);

      current_segment = new CHorizLineSegment (this);
      _parent.add(current_segment, null);

      current_segment._start_point = _line_points [0];
      current_segment._end_point = _line_points [1];

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);

      // create last segment
      end_point = _end_point;

      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment._start_point = _line_points [1];
      current_segment._end_point = _end_point;

      current_segment.placeSegment();
      current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));
      current_segment.setForeground (_colour);
      current_segment.setBackground (_colour);
      current_segment.repaint();
      _segments.addElement (current_segment);

    }

    /**
       Follows when _top moves
       @roseuid 3B6A4048013E
     */
    public void FollowTop() {
      Point new_start = _top.GetCentrePosition();

			new_start.x -= _line_offset;

      //_start_point = new_start;
      // Make the first and second segments follow by assigning new point positions
      CLineSegment first_segment = (CLineSegment)_segments.elementAt (0);
      CLineSegment next_segment = (CLineSegment)_segments.elementAt (1);

      _line_points [0].x = _start_point.x;
      first_segment.SetStartPoint (new_start);
      first_segment._end_point.x = new_start.x;

      first_segment.placeSegment();
      first_segment.repaint();

      next_segment.SetStartPoint (first_segment._end_point);
      next_segment.placeSegment();
      next_segment.repaint();

      _start_point = new_start;
    }

    /**
       follows when _bottom moves
       @roseuid 3B6A40580141
     */
    public void FollowBottom() {
      Point new_end = _bottom.GetCentrePosition();
			new_end.x += _line_offset;

      int num_segments = _segments.size();

      // Make the first and second segments follow by assigning new point positions
      CLineSegment last_segment = (CLineSegment)_segments.elementAt (num_segments -1);
      CLineSegment prev_segment = (CLineSegment)_segments.elementAt (num_segments - 2);

      last_segment.SetEndPoint (new_end);
      last_segment._start_point.x = new_end.x;

      last_segment.placeSegment();
      last_segment.repaint();

      prev_segment.placeSegment();
      prev_segment.repaint();

      _end_point = new_end;

    }

    public void Redraw (boolean highlight){
      int num_segments = _segments.size();

      for (int i = 0; i < num_segments; i++)
      {
        CLineSegment segment = (CLineSegment) _segments.get(i);
        segment.Highlight(highlight);
        segment.placeSegment();
        segment.repaint();
      }

    }
    /**
       Returns true if segment can be dragged
       @roseuid 3B6E327E002E
     */
    public boolean CanDrag(CLineSegment pLine) {
      boolean ret = false;
      if (_segments.contains (pLine))
      {
					ret = (pLine != _segments.elementAt (0) && pLine != _segments.elementAt (_segments.size() - 1));
      }

      return ret;
    }

    public void NotifyChange(){

    }
    /**
       Proccesses the drag by updating the segments around this segment that is being dragged
       @roseuid 3B6E32E700C5
     */
    public boolean ProcessDrag(CLineSegment pLine) {
      boolean ret = false;
      if (_segments.contains (pLine))
      {
        //get index of this line
        int index = _segments.indexOf (pLine);

        // fist update this one
        pLine.placeSegment();
        pLine.repaint();

        //update segment before
        CLineSegment seg = (CLineSegment)_segments.elementAt (index -1);
        seg.placeSegment();
        seg.repaint();

        //update segment after
        seg = (CLineSegment)_segments.elementAt (index +1);
        seg.placeSegment();
        seg.repaint();
        NotifyChange();
      }
      return ret;
    }

    /**
       Commences the start drag and sets the active _dragObject
       @roseuid 3B6E35140293
     */
    public void startDrag(CDragObject dragObject) {
      _parent.startDrag (dragObject);

    }

    public void ProcessPopup (MouseEvent e){
      if (e.isPopupTrigger())
      {
        //System.out.println("Line popup");
        jPopupMenu1.show(e.getComponent(),
                             e.getX(), e.getY());
      }
    }

    public void ProcessClick(){
      //System.out.println("Line Clicked");
      if (_current_line != null)
      {
        _current_line.Redraw(false);
      }
      _current_line = this;
      Redraw (true);
    }

  public CLineFollower() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  private void jbInit() throws Exception {
    DeleteMenu.setText("Delete Connector");
    DeleteMenu.addActionListener(new CLineFollower_DeleteMenu_actionAdapter(this));
    mnuEditConnector.setText("Edit Connector");
    mnuEditConnector.addActionListener(new CLineFollower_mnuEditConnector_actionAdapter(this));
    mnuMake5Line.setText("Make 5 Segment Connector");
    mnuMake5Line.addActionListener(new CLineFollower_mnuMake5Line_actionAdapter(this));
    mnuMake3Line.setText("Make 3 Segment Connector");
    mnuMake3Line.addActionListener(new CLineFollower_mnuMake3Line_actionAdapter(this));
    mnuMake7Line.setText("Make 7 Segment Connector");
    mnuMake7Line.addActionListener(new CLineFollower_mnuMake7Line_actionAdapter(this));
    mnuSetColour.setText("Set Connector Colour");
    mnuSetColour.addActionListener(new CLineFollower_mnuSetColour_actionAdapter(this));
    mnuClearColour.setText("Clear Connector Colour");
    mnuClearColour.addActionListener(new CLineFollower_mnuClearColour_actionAdapter(this));
    jPopupMenu1.setDefaultLightWeightPopupEnabled(false);
    jPopupMenu1.add(mnuEditConnector);
    jPopupMenu1.add(DeleteMenu);
    jPopupMenu1.add(mnuMake3Line);
    jPopupMenu1.add(mnuMake5Line);
    jPopupMenu1.add(mnuMake7Line);
    jPopupMenu1.addSeparator();
    jPopupMenu1.add(mnuSetColour);
    jPopupMenu1.add(mnuClearColour);
  }

  public void PerformDelete(){
// overriddedn by superclass
  }

  public void PerformDisplayEdit(){
    // overriddedn by superclass
  }

  void DeleteMenu_actionPerformed(ActionEvent e) {
    // we need to delete the connector completely
    PerformDelete();
  }

  void mnuEditConnector_actionPerformed(ActionEvent e) {
    PerformDisplayEdit();
  }

  void mnuMake5Line_actionPerformed(ActionEvent e) {
    Build5SegmentLine();
  }

  void mnuMake3Line_actionPerformed(ActionEvent e) {
    Build3SegmentLine();
  }

  void mnuMake7Line_actionPerformed(ActionEvent e) {
    Build7SegmentLine();
  }

  void mnuSetColour_actionPerformed(ActionEvent e) {
    Color newColor = JColorChooser.showDialog(null, "Dialog Title", _colour);
    _colour = newColor;
    SetColour (newColor);

  }

  void mnuClearColour_actionPerformed(ActionEvent e) {
    ClearColour();
  }
}

class CLineFollower_DeleteMenu_actionAdapter implements java.awt.event.ActionListener {
  CLineFollower adaptee;

  CLineFollower_DeleteMenu_actionAdapter(CLineFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.DeleteMenu_actionPerformed(e);
  }
}

class CLineFollower_mnuEditConnector_actionAdapter implements java.awt.event.ActionListener {
  CLineFollower adaptee;

  CLineFollower_mnuEditConnector_actionAdapter(CLineFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuEditConnector_actionPerformed(e);
  }
}

class CLineFollower_mnuMake5Line_actionAdapter implements java.awt.event.ActionListener {
  CLineFollower adaptee;

  CLineFollower_mnuMake5Line_actionAdapter(CLineFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuMake5Line_actionPerformed(e);
  }
}

class CLineFollower_mnuMake3Line_actionAdapter implements java.awt.event.ActionListener {
  CLineFollower adaptee;

  CLineFollower_mnuMake3Line_actionAdapter(CLineFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuMake3Line_actionPerformed(e);
  }
}

class CLineFollower_mnuMake7Line_actionAdapter implements java.awt.event.ActionListener {
  CLineFollower adaptee;

  CLineFollower_mnuMake7Line_actionAdapter(CLineFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuMake7Line_actionPerformed(e);
  }
}

class CLineFollower_mnuSetColour_actionAdapter implements java.awt.event.ActionListener {
  CLineFollower adaptee;

  CLineFollower_mnuSetColour_actionAdapter(CLineFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuSetColour_actionPerformed(e);
  }
}

class CLineFollower_mnuClearColour_actionAdapter implements java.awt.event.ActionListener {
  CLineFollower adaptee;

  CLineFollower_mnuClearColour_actionAdapter(CLineFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuClearColour_actionPerformed(e);
  }
}
