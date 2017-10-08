// Source file: C:/develop/JSmartController/src/ViewForms/Graphics/CBottomFollower.java

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

/**
   Object that sits on the Bottom of CObjectBox
 */
public class CBottomFollower extends CObjectFollower {
    public static final Color _colour = Color.red;


    /**
       @roseuid 3B68C3F50361
     */
    public CBottomFollower(CObjectBox parent, int index) {
      super (parent, index);
				setForeground (_colour);
    }

    /**
       method used to calculate the position of this object on its parent
       @roseuid 3B68CBFF039C
     */
    public Point calculatePosition() {
      int x = 0;
      int y = _parent.GetHeight() - getSize().height;

      if (_index > 0)
      {
        int BoundaryWidth = _parent.GetWidth() - getSize().width;

        //_bottomFollowers.size() must be > 0
        int Spacing = BoundaryWidth / (_parent._bottomFollowers.size() -1);
        x = _index * Spacing;
      }

      return new Point (x,y);
    }

    /**
       @roseuid 3B6E111600A9
     */
    public void notifyFollowers() {
      int num_elements = _followers.size();
      for (int i = 0; i < num_elements; i++)
      {
        CLineFollower follower = (CLineFollower)_followers.elementAt(i);
        follower.FollowBottom();
      }
    }

    /**
       @roseuid 3B73805D0257
     */
    protected void SetMouseOver() {
				_mouseOverBottom = this;
    }

    /**
       @roseuid 3B73805D027F
     */
    protected void ClearMouseOver() {
				_mouseOverBottom = null;
    }

    /**
       @roseuid 3B7382960075
     */
    public boolean CanConnect(CObjectFollower connector) {
				//check that connector does not exist as the bottom of any of my followers
				boolean ret = true;
				int num_elements = _followers.size();
				for (int i = 0; i < num_elements && ret; i++)
						{
								CLineFollower follower = (CLineFollower)_followers.elementAt(i);
								if (follower._top == connector)
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
       @roseuid 3B7385AA0213
     */
    protected void processDrag(int x, int y) {
				DrawDragline (x, y);
				if (_mouseOverTop != null)
						{
								_mouseOverTop.CanConnect(this);
						}
    }

    /**
       @roseuid 3B85C35602D7
     */
    protected void performConnection() {
      if (_mouseOverTop != null)
      {
        if (_mouseOverTop.CanConnect(this))
        {
          final ViewFormPanel line_parent = _parent._parent;
          final CBottomFollower me = this;
          try {
            // make a new segment using the top and this
            javax.swing.SwingUtilities.invokeLater(new Runnable() {
              public void run() {
                new CLineFollower (_mouseOverTop, me, line_parent);
              }
            });
          }
          catch(Exception e) {
            e.printStackTrace();
          }


          // new CLineFollower (_mouseOverTop, this, line_parent);
        }
      }

    }
  }
