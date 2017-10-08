// Source file: c:/develop/PatchEditor/ViewForms/Graphics/CObjectFollower.java

/*
Angelo Fraietta

*/

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import java.awt.datatransfer.*;
import java.awt.dnd.*;

import java.awt.Panel;
import java.io.*;

/**
   Returns true if we need to highlight (or make larger)
 */
public abstract class CObjectFollower extends Panel
implements DragGestureListener,
DragSourceListener,
DropTargetListener{

    JPopupMenu jPopupMenu1 = new JPopupMenu();
    JMenuItem mnuSetColour = new JMenuItem();
    JMenuItem mnuClearColour = new JMenuItem(); // value that will be used for colour

    /**
       The index of the object. Unique for each subclass
     */
    public int _index;
    protected static final Dimension _size = new Dimension (10,3);
    /**
       Becomes true when one of these objects is being dragged
     */
    private static boolean _dragging = false;
    public CObjectBox _parent;
    public Vector _followers = new Vector();

    private Color _last_colour = Color.BLACK;
    /**
       Is set by TopFollowers when the mouse goes over them
     */
    protected static CTopFollower _mouseOverTop = null;
    /**
       Set by bottom followers when mouse goes over
     */
    protected static CBottomFollower _mouseOverBottom = null;

    protected void finalize() throws Throwable {
        super.finalize();
        //uncomment next to see memory released
        //System.out.println ("CObjectFollower::finalize");
    }


    public CObjectFollower()
    {
      try {
        jbInit();
      }
      catch(Exception e) {
        e.printStackTrace();
      }

    }

    private void jbInit() throws Exception {

      mnuSetColour.setText("Set Connector Colour");
    mnuSetColour.addActionListener(new CObjectFollower_mnuSetColour_actionAdapter(this));
      mnuClearColour.setText("Clear Connector Colour");
    mnuClearColour.addActionListener(new CObjectFollower_mnuClearColour_actionAdapter(this));
      addMouseListener(new CObjectFollower__parent_mouseAdapter(this));

    jPopupMenu1.setDefaultLightWeightPopupEnabled(false);
    jPopupMenu1.add(mnuSetColour);
      jPopupMenu1.add(mnuClearColour);
    }
    /**
       @roseuid 3B68BBFE0228
     */
    public CObjectFollower(CObjectBox parent, int index) {
      _parent = parent;
      _index = index;

      try {
        jbInit();
      }
      catch(Exception e) {
        e.printStackTrace();
      }

      this.setSize (_size);

			// comment the following to generate with Rose
                        new DropTarget(this,DnDConstants.ACTION_COPY_OR_MOVE, this);

			DragSource dragSource = DragSource.getDefaultDragSource();
			// creating the recognizer is all that's necessary - it
			// does not need to be manipulated after creation
			dragSource.createDefaultDragGestureRecognizer
					(
					 this, // component where drag originates
					 DnDConstants.ACTION_COPY_OR_MOVE, // actions
					 this
					 ); // drag gesture listener

			addMouseListener (new MouseAdapter(){
							public void mouseEntered(MouseEvent evt) {
									processMouseEntered (evt.getX(), evt.getY());
							}

							public void mouseExited(MouseEvent evt) {
									processMouseExited (evt.getX(), evt.getY());
							}

							public void mouseReleased(MouseEvent evt) {
									processMouseUp (evt.getX(), evt.getY());
							}

					});

			//Add listener so we can drag

			addMouseMotionListener (new MouseMotionAdapter(){
					public void mouseDragged(MouseEvent evt) {
							processDrag (evt.getX(), evt.getY());
					}
					});


    }

    /**
       method used to calculate the position of this object on its parent
       @roseuid 3B68CBB10141
     */
    public abstract Point calculatePosition();

    /**
       @roseuid 3B68C5350004
     */
    public void paint(Graphics g) {

      g.fillRect (0,0, getSize().width, getSize().height);
    }

    /**
       @roseuid 3B68CB37036C
     */
    public void follow() {
      setLocation (this.calculatePosition());
      notifyFollowers();

    }

    /**
       returns the centre position of the object
       @roseuid 3B68EA7F0096
     */
    public Point GetCentrePosition() {
      Point parent_location = _parent.getLocation();
      Point location = getLocation();
      int x = location.x + (_size.width / 2);
      int y = location.y + (_size.height / 2);

      // now add to the parent's position
      x += parent_location.x;
      y += parent_location.y;

      return new Point (x, y);
    }

    /**
       @roseuid 3B68F677013C
     */
    public void AddFollower(CLineFollower follower) {
      _followers.addElement (follower);

    }

    /**
       Tells the followers to follow
       @roseuid 3B68F6DE02D5
     */
    public abstract void notifyFollowers();

    /**
       Frees all references in other objects to this object
       @roseuid 3B69DC7A01E2
     */
    public synchronized void destroy() {
      int num_elements = _followers.size();
      // work backwards as the element will be removed by the follower
      for (int i = num_elements - 1; i >= 0; i--)
      {
        CLineFollower follower = (CLineFollower)_followers.elementAt(i);
        if (follower != null)
        {
          follower.destroy();
        }
      }

      _parent = null;
    }

    /**
       @roseuid 3B69E37102A5
     */
    public void RemoveFollower(CLineFollower follower) {
      _followers.removeElement (follower);
    }

    /**
       Process the Mouse Drag
       @roseuid 3B7376A400B4
     */
    protected abstract void processDrag(int x, int y);

    /**
       Process the Mouse Drag
       @roseuid 3B7376A400D2
     */
    protected void processMouseEntered(int x, int y) {
      //System.out.println("Mouse Over");
      //if (!_dragging)
      //{
        DrawHighlight();
				//}

      SetMouseOver();
    }

    /**
       Process the Mouse Drag
       @roseuid 3B7376A400E6
     */
    protected void processMouseExited(int x, int y) {
				//System.out.println("Mouse exits");
				setSize(_size);
				setLocation (this.calculatePosition());
				repaint();
				if (!_dragging)
						{
								//System.out.println("Clear Mouse Over");
								ClearMouseOver();
						}
    }

    /**
       Causes the subclass to set that the mouse is over it
       @roseuid 3B737FF40260
     */
    protected abstract void SetMouseOver();

    /**
       Causes the subclass to clear that the mouse is not over it
       @roseuid 3B73801502C2
     */
    protected abstract void ClearMouseOver();

    /**
       returns true if calling object can connect to this object
       @roseuid 3B73825701B5
     */
    protected abstract boolean CanConnect(CObjectFollower connector);

    /**
       Draws the line used in dragging
       @roseuid 3B85A14A0360
     */
    public void DrawDragline(int x, int y) {
				_dragging = true;

				ViewFormPanel line_parent = _parent._parent;
				Point start = calculatePosition();
				Point parent_pos = _parent.getLocation();

				start.x += parent_pos.x + (_size.width / 2); // move to center
				start.y += parent_pos.y;

				Point end = new Point (start.x + x, start.y + y);

				line_parent.DrawDragLine (start, end);

				line_parent.repaint();
    }

    /**
       Process the Mouse Drag
       @roseuid 3B85A9A3001A
     */
    protected void processMouseUp(int x, int y) {
				//System.out.println("Process Mouse Up");
				ViewFormPanel line_parent = _parent._parent;

				line_parent.invalidate();
				line_parent.repaint();
				_dragging = false;
				performConnection();
    }

    public void ProcessPopup (MouseEvent e){
      if (e.isPopupTrigger())
      {
        //System.out.println("Line popup");
        jPopupMenu1.show(e.getComponent(),
                             e.getX(), e.getY());
      }
    }

    /**
       Sets the size to a highlighted size
       @roseuid 3B85BDD400F9
     */
    protected void DrawHighlight() {
				Dimension new_size = new Dimension (_size.width, _size.height * 2);
				setSize(new_size);
				setLocation (this.calculatePosition());
				repaint();

    }

    /**
       @roseuid 3B85C1B00154
     */
    public int getIndex() {
				return _index;
    }

    /**
       @roseuid 3B85C3350352
     */
    protected abstract void performConnection();

		public void dragGestureRecognized(DragGestureEvent e) {
				// drag anything ...
				e.startDrag(DragSource.DefaultCopyDrop, new StringSelection(new String ("Test")), this);
				//System.out.println("DragGestureRecognised");
		}
                public void drop(DropTargetDropEvent e) {
                   try {
                      DataFlavor stringFlavor = DataFlavor.stringFlavor;
                      Transferable tr = e.getTransferable();
                      if(e.isDataFlavorSupported(stringFlavor)) {
                         String filename =
                              (String)tr.getTransferData(stringFlavor);
                         e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
                         e.dropComplete(true);
                      }
                      else {
                         e.rejectDrop();
                      }
                   }
                   catch(IOException ioe) {
                      ioe.printStackTrace();
                   }
                   catch(UnsupportedFlavorException ufe) {
                      ufe.printStackTrace();
                   }
                 }

		public void dragDropEnd(DragSourceDropEvent e)
		{
				//System.out.println("dragDropEnd");
				processMouseUp (0, 0);
				ClearMouseOver();
		}
		public void dragEnter(DragSourceDragEvent e)
		{
				//System.out.println("Source dragDropEnter");
				processDrag (0, 0);

		}

		public void dragExit(DragSourceEvent e) {/*System.out.println("sOURCE dragDropExit")*/;}
		public void dragOver(DragSourceDragEvent e) {}
		public void dropActionChanged(DragSourceDragEvent e) {/*System.out.println("DropActionChanged");*/}

		public void dragEnter(DropTargetDragEvent e)
		{
				//System.out.println("Target DragEnter");
				processMouseEntered (0, 0);
		}

		public void dragExit(DropTargetEvent e)
		{
				//System.out.println("Drag EXit");
				processMouseExited (0, 0);
				ClearMouseOver();
		}

		public void dragOver(DropTargetDragEvent e){}

                public void dropActionChanged(DropTargetDragEvent e) { /*System.out.println("drop Action Changed"); */}

  void _parent_mousePressed(MouseEvent e) {
    ProcessPopup(e);
  }

  void _parent_mouseReleased(MouseEvent e) {
    ProcessPopup(e);
  }

  void mnuSetColour_actionPerformed(ActionEvent e) {

    Color newColor = JColorChooser.showDialog(this, "Dialog Title", _last_colour);
    _last_colour = newColor;
    SetColour (newColor);
  }

  void SetColour (Color c)
  {
    int num_elements = _followers.size();
    // work backwards as the element will be removed by the follower
    for (int i = 0; i < num_elements; i++)
    {
      CLineFollower follower = (CLineFollower)_followers.elementAt(i);
      if (follower != null)
      {
        follower.SetColour(c);
      }
    }
  }

  void mnuClearColour_actionPerformed(ActionEvent e) {
    int num_elements = _followers.size();
    // work backwards as the element will be removed by the follower
    for (int i = 0; i < num_elements; i++)
    {
      CLineFollower follower = (CLineFollower)_followers.elementAt(i);
      if (follower != null)
      {
        follower.ClearColour();
      }
    }

  }

}

class CObjectFollower__parent_mouseAdapter extends java.awt.event.MouseAdapter {
  CObjectFollower adaptee;

  CObjectFollower__parent_mouseAdapter(CObjectFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void mousePressed(MouseEvent e) {
    adaptee._parent_mousePressed(e);
  }
  public void mouseReleased(MouseEvent e) {
    adaptee._parent_mouseReleased(e);
  }
}

class CObjectFollower_mnuSetColour_actionAdapter implements java.awt.event.ActionListener {
  CObjectFollower adaptee;

  CObjectFollower_mnuSetColour_actionAdapter(CObjectFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuSetColour_actionPerformed(e);
  }
}

class CObjectFollower_mnuClearColour_actionAdapter implements java.awt.event.ActionListener {
  CObjectFollower adaptee;

  CObjectFollower_mnuClearColour_actionAdapter(CObjectFollower adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuClearColour_actionPerformed(e);
  }
}
