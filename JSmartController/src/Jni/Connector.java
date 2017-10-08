// Source file: c:/develop/WinsmartController/controller/source/engineinterface/PatchEditorInterface/Jni/Connector.java

package Jni;

/*
Connector Documentation: Provides Java to Native Interface for Connector

*/

/**
   Provides Java to Native Interface for Connector
 */
public class Connector {
    
    Connector() {
    }
    /**
       @roseuid 3E669E420118
     */
    public static native boolean IsValid(int pQuestion, int dwpCon);
    
    /**
       @roseuid 3E669E42012C
     */
    public static native int Create(int pQuestion);
    
    /**
       @roseuid 3E669E420136
     */
    public static native void Delete(int pQuestion, int dwpCon);
    
    /**
       @roseuid 3E669E42014A
     */
    public static native void SetOutletNum(int pQuestion, int dwpCon, int wSocketNum);
    
    /**
       @roseuid 3E669E420154
     */
    public static native void SetOutletBase(int pQuestion, int dwpCon, int dwpShell);
    
    /**
       @roseuid 3E669E420168
     */
    public static native void SetInletNum(int pQuestion, int dwpCon, int wSocketNum);
    
    /**
       @roseuid 3E669E420172
     */
    public static native void SetInletBase(int pQuestion, int dwpCon, int dwpShell);
    
    /**
       @roseuid 3E669E420186
     */
    public static native boolean MakeConnection(int pQuestion, int dwpCon);
    
    /**
       @roseuid 3E669E420190
     */
    public static native int GetOutletNum(int pQuestion, int dwpCon);
    
    /**
       @roseuid 3E669E4201A4
     */
    public static native int GetOutletIndex(int pQuestion, int dwpCon);
    
    /**
       @roseuid 3E669E4201AE
     */
    public static native int GetInletNum(int pQuestion, int dwpCon);
    
    /**
       @roseuid 3E669E4201C2
     */
    public static native int GetOutletBase(int pQuestion, int dwpCon);
    
    /**
       @roseuid 3E669E4201CC
     */
    public static native int GetInletBase(int pQuestion, int dwpCon);
}
