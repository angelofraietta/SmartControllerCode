// Source file: c:/develop/WinsmartController/controller/source/engineinterface/PatchEditorInterface/Jni/View.java

package Jni;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;


/**
   JNI interface for View
   Also contains the Parameters as an Object
 */
public class View {
    public int top;
    public int left;
    public int width;
    public int tag;
    public int dwpShell;
    public int height;
    
    /**
       returns the Number of Views in a Patch
       @roseuid 3E8E067F01C8
     */
    public static native int GetNumViews(int pQuestion, int dwpPatch);
    
    /**
       Returns the Number of Objects within a view
       @roseuid 3E8E067F01D1
     */
    public static native int GetNumViewObjects(int pQuestion, int dwpPatch, int viewNum);
    
    /**
       Returns a BaseShell pointer of the Objects within the View
       @roseuid 3E8E067F01D5
     */
    public static native int GetViewObject(int pQuestion, int dwpPatch, int viewNum, int objectNum);
    
    /**
       Returns the display parameters of the object, being, P_Basehell, top, left, height, width, and tag
       Non static Member because the parameters must be returned within the Object class
       @roseuid 3E8E067F01DC
     */
    public native boolean GetViewObjectDisplayParams(int pQuestion, int dwpPatch, int viewNum, int objectNum);
    
    /**
       Adds the display parameters of the object, being, pBasehell, top, left, height, width, and tag
       @roseuid 3E8E067F01E1
     */
    public static native boolean AddViewObject(int pQuestion, int dwpPatch, int viewNum, int pObject, int top, int left, int height, int width, int tag);
    
    /**
       Clears View
       @roseuid 3E8E067F01ED
     */
    public static native boolean ClearView(int pQuestion, int dwpPatch, int viewNum);
    
    /**
       Returns the Name of the view
       @roseuid 3E8E067F01F1
     */
    public static native String GetViewName(int pQuestion, int dwpPatch, int viewNum);
    
    /**
       @roseuid 3E8E067F01F5
     */
    public static native boolean SetViewName(int pQuestion, int dwpPatch, int viewNum, String name);
    
    /**
       Modifiesthe display parameters of the object, being, top, left, height, width, and tag given a Baseshell
       @roseuid 3E8E067F01FB
     */
    public static native boolean ModifyViewObject(int pQuestion, int dwpPatch, int viewNum, int pObject, int top, int left, int height, int width, int tag);
    
    /**
       @roseuid 3E8E067F0207
     */
    public static native int AddView(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E8E067F020B
     */
    public static native void DeleteView(int pQuestion, int dwpPatch, int viewNum);
    
    /**
       Prints to System Out
       @roseuid 3E8E067F020F
     */
    public static void Print() {
    }
    
    /**
       Adds the Connector To View Object
       @roseuid 3E8E167F037D
     */
    public static native int AddViewConnector(int pQuestion, int dwpPatch, int viewNum, int pCon);
    
    /**
       Returns the Number OF View Connectors within View
       @roseuid 3E8E167F0387
     */
    public static native int GetNumViewConnectors(int pQuestion, int dwpPatch, int viewNum);
    
    /**
       Returns the Connector Pointed to at ViewIndex
       @roseuid 3E8E167F0391
     */
    public static native int GetViewConnector(int pQuestion, int dwpPatch, int viewNum, int objectNum);
    
    /**
       Returns the Value Stored at the point
       @roseuid 3E8E167F039B
     */
    public static native int GetViewConnectorValue(int pQuestion, int dwpPatch, int viewNum, int objectNum, int value_num);
    
    /**
       Returns the Number of Values at a given Connector View Point
       @roseuid 3E8E167F03A5
     */
    public static native int GetNumViewConnectorValues(int pQuestion, int dwpPatch, int viewNum, int objectNum);
    
    /**
       Adds A New View Connector Value
       @roseuid 3E8E167F03AA
     */
    public static native boolean AddViewConnectorValue(int pQuestion, int dwpPatch, int viewNum, int objectNum, int new_value);
}
