// Source file: c:/develop/WinsmartController/controller/source/engineinterface/PatchEditorInterface/Jni/Identity.java

package Jni;

/*
Identity Documentation: Provides Java to Native Interface for Identity

*/

/**
   Provides Java to Native Interface for Identity
 */
public class Identity {
    
    Identity() {
    }
    /**
       Gets the Attribute defininded by the int and index  parameters.  The Attribute value is returned as a parameter. Function returns true if the Attribute is valid
       @roseuid 3E669DF80266
     */
    public static native String GetDefaultAttribute(int pQuestion, int objKey);
    
    /**
       Gets the name of identity defininded by the int  parameter.  The identity name is returned as parameters.
       @roseuid 3E669DF80270
     */
    public static native String GetName(int pQuestion, int objKey);
    
    /**
       Gets the comment of the identity defininded by the int  parameter.  The identity name is returned as parameters.
       @roseuid 3E669DF8027A
     */
    public static native String GetComment(int pQuestion, int objKey);
    
    /**
       Gets the type of the identity defininded by the int  parameter.  The identity name is returned as parameters.
       @roseuid 3E669DF80284
     */
    public static native String GetType(int pQuestion, int objKey);
    
    /**
       Sets the name defininded by the int parameter.  Function returns true if the name has been set.
       @roseuid 3E669DF8028E
     */
    public static native boolean SetName(int pQuestion, int objKey, String new_value);
    
    /**
       Sets the comment defininded by the int parameter.  Function returns true if the name has been set.
       @roseuid 3E669DF802A2
     */
    public static native boolean SetComment(int pQuestion, int objKey, String new_value);
    
    /**
       Returns true if the identity has been modified
       @roseuid 3E669DF802AC
     */
    public static native boolean GetModified(int pQuestion, int objKey);
    
    /**
       Sets the default attribute defininded by the int parameter.  Function returns true if the name has been set.
       @roseuid 3E669DF802B6
     */
    public static native boolean SetDefaultAttribute(int pQuestion, int objKey, String new_value);
    
    /**
       @roseuid 3E669DF802CA
     */
    public static native boolean CanSave(int pQuestion, int dwpId);
    
    /**
       @roseuid 3E669DF802D4
     */
    public static native int GetParent(int pQuestion, int dwpId);
    
    /**
       @roseuid 3E669DF802DE
     */
    public static native void SetParent(int pQuestion, int dwpId, int dwpParent);
}
