// Source file: C:/develop/JSmartController/src/ViewForms/Graphics/CTopFollower.java

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
   Object that sits on the Top of CObjectBox
 */
public class CTopFollower extends CObjectFollower {
    public static final Color _colour = Color.black;

    /**
       @roseuid 3B68C3D9022A
     */
    public CTopFollower(CObjectBox parent, int index) {
      super (parent, index);
				setForeground (_colour);
    }

    /**
       method used to calculate the position of this object on its parent
       @roseuid 3B68CBF00119
     */
    public Point calculatePosition() {
      int x = 0;
      int y = 0;

      if (_index > 0)
      {
        int BoundaryWidth = _parent.GetWidth() - _size.width;

        //_topFollowers.size() must be > 0
        int Spacing = BoundaryWidth / (_parent._topFollowers.size() -1);
        x = _index * Spacing;
      }
      return new Point (x,y);
    }

    /**
       @roseuid 3B6E1116008B
     */
    public void notifyFollowers() {
      int num_elements = _followers.size();
      for (int i = 0; i < num_elements; i++)
      {
        CLineFollower follower = (CLineFollower)_followers.elementAt(i);
        follower.FollowTop();
      }

    }

    /**
       @roseuid 3B73805D01FD
     */
    protected void SetMouseOver() {
				_mouseOverTop = this;
    }

    /**
       @roseuid 3B73805D021B
     */
    protected void ClearMouseOver() {
				_mouseOverTop = null;
    }

    /**
       @roseuid 3B73829503E5
     */
    public boolean CanConnect(CObjectFollower connector) {
				//check that connector does not exist as the bottom of any of my followers
				boolean ret = true;
				int num_elements = _followers.size();
				for (int i = 0; i < num_elements && ret; i++)
						{
								CLineFollower follower = (CLineFollower)_followers.elementAt(i);
								if (follower._bottom == connector)
										{
												ret = false;
										}

						}
				if (ret)
						{
								DrawHighlight();
						}

				return ret;

    }

    /**
       @roseuid 3B7385AA014A
     */
    protected void processDrag(int x, int y) {
				DrawDragline (x, y);
				if (_mouseOverBottom != null)
						{
								_mouseOverBottom.CanConnect(this);
						}

    }

    /**
       @roseuid 3B85C356029B
     */
    protected void performConnection() {
      if (_mouseOverBottom != null)
      {
        if (_mouseOverBottom.CanConnect(this))
        {
          final ViewFormPanel line_parent = _parent._parent;
          final CTopFollower me = this;
          System.out.println("Try Invoke Later");
          try {
            // make a new segment using the top and this
            javax.swing.SwingUtilities.invokeLater(new Runnable() {

              public void run() {
                new CLineFollower (me, _mouseOverBottom, line_parent);
              }
            });
          }
          catch(Exception e) {
            e.printStackTrace();
          }

          //new CLineFollower (this, _mouseOverBottom, line_parent);
        }
      }

    }
  }
