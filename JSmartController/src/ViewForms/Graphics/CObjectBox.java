// Source file: C:/develop/JSmartController/src/ViewForms/Graphics/CObjectBox.java

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import java.awt.Panel;


/**
   Superclass of graphic Object Boxes
   Displays A box, inlets and outlets, and a text string
 */
public class CObjectBox extends Panel {
    protected Dimension boxSize = new Dimension (50, 20);
    private static Dimension minSize = new Dimension (20, 20);
    private boolean _isdragging = false;
    private boolean _is_highlighted = false;
    private boolean _painted_highlighted = false;
    /**
       The size a follower goes into the height of this object
     */
    public final int follower_depth = 5;
    private String display_text = new String ("default");
    private String last_string = new String ("");
    /**
       Relation ship for dragging of object
     */
    public ViewFormPanel _parent = null;
    public Vector _topFollowers = new Vector ();
    public Vector _bottomFollowers = new Vector ();

    protected void finalize() throws Throwable {
      super.finalize();
      _parent = null;
      //uncomment next to see memory released
      //System.out.println ("CObjectBox::finalize");
    }
    /**
       @roseuid 3B6600CA02B7
     */
    public CObjectBox(ViewFormPanel parent) {
      _parent = parent;
      //this.setBackground(Color.white);
      //this.setForeground (Color.black);
      //this.setColor (Color.black);
      this.setLocation (10, 10);
      this.setSize (boxSize);
      this.setLayout(null);


      // the following function must be commented out when generating with Rose
      //Add listener so we can drag

      addMouseMotionListener (new MouseMotionAdapter(){
        public void mouseDragged(MouseEvent evt) {
          processDrag (evt.getX(), evt.getY());
        }
      });


    }

    /**
       Process the Mouse Drag
       @roseuid 3B662F1D0313
     */
    protected void CompleteDrag(){
      if (_isdragging)
      {
        _isdragging = false;
        this.notifyFollowers();
      }
    }
    private void processDrag(int x, int y) {
      //let us find our centre
      Point p = getLocation();
      _isdragging = true;

      if (IsResizing())
      {
        int new_width = x ;
        int new_height = y ;
        resizeBox (new Dimension (new_width, new_height));
        this.notifyFollowers();


      }
      else
      {
        if (p.x + x > 0 && p.y + y > 0) // we are still visible on the secreen
        {
          this.setLocation (p.x + x - boxSize.width / 2 , p.y + y - boxSize.height / 2);
          _parent.updateSize  (p.x + x, p.y + y);
        }
      }

      NotifyChange(); // call methos to superclass
    }

    public String GetLastString() {
      return last_string;
    }

    public boolean PaintedHighlighted(){
      return _painted_highlighted;
    }
    public void NotifyChange(){
    }
    /**
       @roseuid 3B6750AB024A
     */
    public boolean resizeBox(Dimension new_size) {
      boolean ret = false;
      if (new_size.width >= minSize.width && new_size.height >= minSize.height)
      {
        boxSize = new_size;
        this.setSize (boxSize);
        this.notifyFollowers();
        ret = true;
      }
      return ret;
    }

    /**
       @roseuid 3B67515C0118
     */
    protected void paintBox(Graphics g) {
      //g.setColor(Color.black);

      // we subtract 2 from the next width and height so the whole rectangle will be shown
      if (GetHighlighted())
      {
        g.setColor(Color.gray);
        g.fillRect(0, 0, boxSize.width-2, boxSize.height-2);
        _painted_highlighted = true;
      }
      else
        {
          _painted_highlighted = false;
          g.setColor(Color.black);
          g.clearRect(0, 0, boxSize.width-2, boxSize.height-2);
          g.drawRect(0, 0, boxSize.width-2, boxSize.height-2);
        }

      g.setColor(Color.black);
      last_string = GetText();
      g.drawString (last_string, 2, boxSize.height - follower_depth);
    }

    // function Is Overridden
    public boolean GetHighlighted(){
      return _is_highlighted;
    }

    public void SetHighlighted(boolean highlighted){
      _is_highlighted = highlighted;
      last_string = null; // force a repaint of the text
    }

    /**
       @roseuid 3B6766C40321
     */
    public void paint(Graphics g) {
      paintBox(g);
    }

    /**
       Adds A follower
       @roseuid 3B68C49A0340
     */
    protected void AddFollower(CTopFollower follower) {
      if (_parent != null)
      {
        _topFollowers.addElement(follower);
        this.add (follower, null);
        follower.follow();
        follower.repaint();
      }
    }

    /**
       Adds A follower
       @roseuid 3B68C4CA005A
     */
    protected void AddFollower(CBottomFollower follower) {
      if (_parent != null)
      {
        _bottomFollowers.addElement(follower);
        this.add (follower, null);
        follower.follow();
        follower.repaint();
      }
    }

    /**
       Virtual method which returns the string that must be wriiten in the box
       @roseuid 3B68D1F10097
     */
    public String GetText() {
      return display_text;
    }

    /**
       returns the width
       @roseuid 3B68D3F10292
     */
    public int GetWidth() {
      return boxSize.width;
    }

    /**
       returns the Height
       @roseuid 3B68D4070031
     */
    public int GetHeight() {
      return boxSize.height;
    }

    /**
       Tells the followers to follow
       @roseuid 3B68E62F0193
     */
    protected void notifyFollowers() {
      int num_elements = _topFollowers.size();
      for (int i = 0; i < num_elements; i++)
      {
        CTopFollower follower = (CTopFollower)_topFollowers.elementAt(i);
        follower.follow();
      }

      num_elements = _bottomFollowers.size();
      for (int i = 0; i < num_elements; i++)
      {
        CBottomFollower follower = (CBottomFollower)_bottomFollowers.elementAt(i);
        follower.follow();
      }

    }

    /**
       Frees all references in other objects to this object
       @roseuid 3B69DD3402A8
     */
    public synchronized void destroy() {
      // first destroy all followers
      int num_elements = _topFollowers.size();
      for (int i = 0; i < num_elements; i++)
      {
        CTopFollower follower = (CTopFollower)_topFollowers.elementAt(i);
        follower.destroy();
      }

      num_elements = _bottomFollowers.size();
      for (int i = 0; i < num_elements; i++)
      {
        CBottomFollower follower = (CBottomFollower)_bottomFollowers.elementAt(i);
        follower.destroy();
      }

      // remove reference to parent
      if (_parent != null)
      {
        _parent.remove (this);
      }

      _parent = null;
    }

    /**
       Sets the Number of Top Followers
       @roseuid 3B85E80C0367
     */
    public void SetNumTopFollowers(int num_followers) {
      int existing = _topFollowers.size();

      if (existing < num_followers)
      {
        for (int i = existing; i < num_followers; i++)
        {
          CTopFollower follower = new CTopFollower (this, i);
          AddFollower (follower);
        }
      }
    }

    /**
       Sets the Number of BottomFollowers
       @roseuid 3B85E886015A
     */
    public void SetNumBottomFollowers(int num_followers) {
      int existing = _bottomFollowers.size();

      if (existing < num_followers)
      {
        for (int i = existing; i < num_followers; i++)
        {
          CBottomFollower follower = new CBottomFollower (this, i);
          AddFollower (follower);
        }
      }
    }

    /**
       @roseuid 3E83CE8403E2
     */
    public boolean IsResizing() {
      return false;
    }

  public CObjectBox() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  private void jbInit() throws Exception {
    this.addMouseListener(new CObjectBox_this_mouseAdapter(this));
  }

  void this_mouseClicked(MouseEvent e) {
    SetHighlighted (!_is_highlighted);
    this.invalidate();
  }
}

class CObjectBox_this_mouseAdapter extends java.awt.event.MouseAdapter {
  CObjectBox adaptee;

  CObjectBox_this_mouseAdapter(CObjectBox adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
    adaptee.this_mouseClicked(e);
  }
}
