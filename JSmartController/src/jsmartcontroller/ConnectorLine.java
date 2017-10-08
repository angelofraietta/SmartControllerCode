// Source file: C:/develop/JSmartController/src/jsmartcontroller/ConnectorLine.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import ViewForms.Graphics.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import ViewForms.Graphics.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import ViewForms.Graphics.*;


public class ConnectorLine extends CLineFollower {
    public ConnectorHook _pHook;

    /**
       Construictor Representing a Connector
       @roseuid 3E877D0B020D
     */
    public ConnectorLine(BaseShellInlet top, BaseShellOutlet bottom, ViewForm parent, ConnectorHook pHook, ViewConnector pViewParams) {
      super (top, bottom, parent);
      _pHook = pHook;

      if (pViewParams != null)
      {
        // clear all segments from form
        RebuildLine (pViewParams);
      }
    }

    // Select the line in superclass
    public void ProcessClick(){
      super.ProcessClick();
      this.GetPatchForm().SetSelectedConnector(_pHook);
    }

    public void PerformDisplayEdit(){
        _pHook.DisplayEditForm();
      }

    public void PerformDelete(){
      int patch = ((ViewForm)_parent)._patch;
      GetPatchForm().SetSelectedConnector(null);
      GetPatchForm().DeleteConnector(_pHook);
      Patch.DetachConnector(_pHook._presentation, patch, _pHook._pObject);
    }

    /**
       Rebuild the Line Based On New Parameters
       @roseuid 3E925EBD030D
     */
    public void RebuildLine(ViewConnector pViewParams) {
      int num_elements = _segments.size();
      for (int i = 0; i < num_elements; i++) {
        CLineSegment follower = (CLineSegment) _segments.elementAt(i);
        follower.destroy();
        _parent.remove(follower);
      }

      _segments.removeAllElements();

      CLineSegment current_segment;
      Point current_point = new Point(_start_point);
      Point end_point = new Point(current_point);
      Point next_start_point;
      Point next_end_point;
      end_point.y -= pViewParams.ReadValue(0);

      // create the top segment first with a height of The segment leader
      _line_points [0] = new Point (end_point);
      next_start_point = _start_point;
      next_end_point = _line_points [0];

      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);
      current_segment.FollowStartPoint(next_start_point);
      current_segment.FollowEndPoint(next_end_point);

      next_start_point = next_end_point;

      current_segment.placeSegment();
      current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));

      if (is_coloured)
      {
        current_segment.setForeground (_colour);
        current_segment.setBackground (_colour);
      }
      else
      {
        current_segment.setForeground (CTopFollower._colour);
        current_segment.setBackground (CTopFollower._colour);
      }
      current_segment.repaint();
      _segments.addElement (current_segment);

      // create a leader accross
      current_point.x = end_point.x;
      current_point.y = end_point.y;

      end_point.x -= pViewParams.ReadValue(1);

      _line_points [1] = new Point (end_point);

      next_end_point = _line_points [1];

      current_segment = new CHorizLineSegment (this);
      _parent.add(current_segment, null);

      current_segment.FollowStartPoint(next_start_point);
      current_segment.FollowEndPoint(next_end_point);

      next_start_point = next_end_point;


      next_start_point = next_end_point;

      current_segment.placeSegment();

      current_segment.repaint();
      _segments.addElement (current_segment);

      if (pViewParams.NumValues() > 3)
      {
        // create segment going down into the centre of the two
        current_point.x = end_point.x;
        current_point.y = end_point.y;
        end_point.y -= pViewParams.ReadValue(2);

        _line_points[2] = new Point(end_point);
        next_end_point = _line_points[2];

        current_segment = new CVerticalLineSegment(this);
        _parent.add(current_segment, null);

        current_segment.FollowStartPoint(next_start_point);
        current_segment.FollowEndPoint(next_end_point);
        next_start_point = next_end_point;

        current_segment.placeSegment();

        current_segment.repaint();
        _segments.addElement(current_segment);

        //create the segment going accross
        current_point.x = end_point.x;
        current_point.y = end_point.y;

        end_point.x -= pViewParams.ReadValue(3);

        _line_points[3] = new Point(end_point);
        next_end_point = _line_points[3];

        current_segment = new CHorizLineSegment(this);
        _parent.add(current_segment, null);

        current_segment.FollowStartPoint(next_start_point);
        current_segment.FollowEndPoint(next_end_point);
        next_start_point = next_end_point;

        current_segment.placeSegment();

        current_segment.repaint();
        _segments.addElement(current_segment);

        // create segment going beyond distance of _leader
        current_point.x = end_point.x;
        current_point.y = end_point.y;
        end_point.y -= pViewParams.ReadValue(4);

        _line_points[4] = new Point(end_point);

        next_end_point = _line_points[4];

        current_segment = new CVerticalLineSegment(this);
        _parent.add(current_segment, null);

        current_segment.FollowStartPoint(next_start_point);
        current_segment.FollowEndPoint(next_end_point);
        next_start_point = next_end_point;
        current_segment.placeSegment();

        current_segment.repaint();
        _segments.addElement(current_segment);

        // create segment going above _leader
        current_point.x = end_point.x;
        current_point.y = end_point.y;
        end_point.x -= pViewParams.ReadValue(5);

        _line_points[5] = new Point(end_point);
        next_end_point = _line_points[5];

        current_segment = new CHorizLineSegment(this);
        _parent.add(current_segment, null);

        current_segment.FollowStartPoint(next_start_point);
        current_segment.FollowEndPoint(next_end_point);
        next_start_point = next_end_point;
        current_segment.placeSegment();

        current_segment.repaint();
        _segments.addElement(current_segment);

        _tag =  pViewParams.ReadValue(6);
      }
      else
      {
        _tag =  pViewParams.ReadValue(2);
      }

      // create last segment
      current_point.x = end_point.x;
      current_point.y = end_point.y;
      end_point = _end_point;

      current_segment = new CVerticalLineSegment (this);
      _parent.add(current_segment, null);

      current_segment.FollowStartPoint (next_start_point);
      current_segment.FollowEndPoint(_end_point);

      current_segment.placeSegment();
      current_segment.setCursor (new Cursor (Cursor.DEFAULT_CURSOR));

      if (is_coloured)
      {
        current_segment.setForeground (_colour);
        current_segment.setBackground (_colour);
      }
      else
      {
        current_segment.setForeground (CBottomFollower._colour);
        current_segment.setBackground (CBottomFollower._colour);
      }


      current_segment.repaint();
      _segments.addElement (current_segment);
    }

    /**
       @roseuid 3EB1FF1B03B7
     */
    public void NotifyChange() {
      GetPatchForm().SetModified();
    }

    /**
       @roseuid 3EB1FF49011E
     */
    public PatchForm GetPatchForm() {
      return ((ViewForm) _parent)._patch_form;
    }
}
