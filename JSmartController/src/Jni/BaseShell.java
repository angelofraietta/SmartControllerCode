// Source file: c:/develop/smartController/controller/source/engineinterface/PatchEditorInterface/Jni/BaseShell.java

package Jni;

/*
BaseShell Documentation: Provides Java to Native Interface for BaseShell

*/

/**
   Provides Java to Native Interface for BaseShell
 */
public class BaseShell {
    
    BaseShell() {
    }
    /**
       Gets the number of attributes for the int parameter.  The  Number of Attributes is returned as parameter
       @roseuid 3E669E2C0148
     */
    public static native int GetNumAttributes(int pQuestion, int objKey);
    
    /**
       Gets the name of the attribute defininded by the int and index  parameters.  The  Attribute name is returned as parameters
       @roseuid 3E669E2C0152
     */
    public static native String GetAttributeName(int pQuestion, int objKey, int attribute_key);
    
    /**
       Gets the Attribute defininded by the P_BaseShell and index  parameters.  The Attribute value is returned as a parameter. Function returns true if the Attribute is valid
       @roseuid 3E669E2C0166
     */
    public static native String GetAttribute(int pQuestion, int objKey, int attribute_key);
    
    /**
       Sets the Attribute defininded by the int and index  parameters.  Function returns true if the Attribute has been set.
       @roseuid 3E669E2C0170
     */
    public static native boolean SetAttribute(int pQuestion, int objKey, int attribute_key, String new_value);
    
    /**
       Gets the number of attributes for the int parameter.  The  Number of Attributes is returned as parameter
       @roseuid 3E669E2C0184
     */
    public static native int GetNumResetAttributes(int pQuestion, int objKey);
    
    /**
       Gets the name of the attribute defininded by the int and index  parameters.  The  Attribute name is returned as parameters
       @roseuid 3E669E2C018E
     */
    public static native String GetResetAttributeName(int pQuestion, int objKey, int attribute_key);
    
    /**
       Gets the Attribute defininded by the P_BaseShell and index  parameters.  The Attribute value is returned as a parameter. Function returns true if the Attribute is valid
       @roseuid 3E669E2C01A2
     */
    public static native String GetResetAttribute(int pQuestion, int objKey, int attribute_key);
    
    /**
       Sets the Attribute defininded by the int and index  parameters.  Function returns true if the Attribute has been set.
       @roseuid 3E669E2C01AC
     */
    public static native boolean SetResetAttribute(int pQuestion, int objKey, int attribute_key, String new_value);
    
    /**
       Resets the baseshell
       @roseuid 3E669E2C01C0
     */
    public static native void Reset(int pQuestion, int dwpShell);
    
    /**
       @roseuid 3E669E2C01D5
     */
    public static native void Send(int pQuestion, int dwpShell);
    
    /**
       @roseuid 3E669E2C01E9
     */
    public static native int Create(int pQuestion, String Type, int pParent);
    
    /**
       @roseuid 3E669E2C01F3
     */
    public static native int GetNumInlets(int pQuestion, int dwpShell);
    
    /**
       @roseuid 3E669E2C0207
     */
    public static native int GetNumOutlets(int pQuestion, int dwpShell);
    
    /**
       @roseuid 3E669E2C021B
     */
    public static native String GetInletName(int pQuestion, int dwpShell, int wSocketNum);
    
    /**
       @roseuid 3E669E2C0225
     */
    public static native String GetOutletName(int pQuestion, int dwpShell, int wSocketNum);
    
    /**
       @roseuid 3E669E2C0243
     */
    public static native int GetNumInletConnectors(int pQuestion, int dwpShell, int wSocketNum);
    
    /**
       @roseuid 3E669E2C024D
     */
    public static native int GetNumOutletConnectors(int pQuestion, int dwpShell, int wSocketNum);
    
    /**
       @roseuid 3E669E2C0261
     */
    public static native boolean CanConnectInlet(int pQuestion, int dwpShell, int wSocketNum, int dwpCon);
    
    /**
       @roseuid 3E669E2C0275
     */
    public static native boolean CanConnectOutlet(int pQuestion, int dwpShell, int wSocketNum, int dwpCon);
    
    /**
       @roseuid 3E669E2C027F
     */
    public static native int GetInletConnector(int pQuestion, int dwpShell, int wSocketNum, int Index);
    
    /**
       @roseuid 3E669E2C0293
     */
    public static native int GetOutletConnector(int pQuestion, int dwpShell, int wSocketNum, int Index);
    
    /**
       @roseuid 3E669E2C029D
     */
    public static native int FindInletConnectorIndex(int pQuestion, int dwpShell, int wSocketNum, int dwpCon);
    
    /**
       @roseuid 3E669E2C02BB
     */
    public static native int FindOutletConnectorIndex(int pQuestion, int dwpShell, int wSocketNum, int dwpCon);
    
    /**
       @roseuid 3E669E2C02CF
     */
    public static native void SwapOutletConnector(int pQuestion, int dwpShell, int outlet_number, int connector1_index, int connector2_index);
    
    /**
       Gets the number of attributes for the P_BASESHELL parameter.  The  Number of Attributes is returned as parameter
       @roseuid 3E7927CF02C5
     */
    public static native synchronized int GetNumObjectTypes(int pQuestion);
    
    /**
       Gets the name of the Object type defined by index  parameters.  The  Objectname is returned as parameters
       @roseuid 3E7927D00077
     */
    public static native synchronized String GetObjectType(int pQuestion, int index);
    
    /**
       @roseuid 3E7935A2038B
     */
    public static native boolean CanHaveChildren(int pQuestion, int dwpShell);
    
    /**
       @roseuid 3E7935A401B8
     */
    public static native boolean CanChangeSize(int pQuestion, int dwpShell);
    
    /**
       Gets the Attribute defininded by the P_BaseShell and index  parameters.  The Attribute value is returned as a parameter. Function returns true if the Attribute is valid
       @roseuid 3EADFB150373
     */
    public static native String GetDefaultAttribute(int pQuestion, int objKey);
}
