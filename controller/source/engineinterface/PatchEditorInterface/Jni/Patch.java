// Source file: c:/develop/WinsmartController/controller/source/engineinterface/PatchEditorInterface/Jni/Patch.java

package Jni;

/*
Patch Documentation: Provides Java to Native Interface for Patch

*/

/**
   Provides Java to Native Interface for Patch
 */
public class Patch {
    
    Patch() {
    }
    /**
       @roseuid 3E669DD100A7
     */
    public static native synchronized void DetachBaseShellObject(int pQuestion, int dwpPatch, int dwpShell);
    
    /**
       @roseuid 3E669DD100B1
     */
    public static native synchronized int FindBaseShellPosition(int pQuestion, int dwpPatch, int dwpShell);
    
    /**
       @roseuid 3E669DD100BB
     */
    public static native synchronized void AddBaseShell(int pQuestion, int dwpPatch, int dwpShell);
    
    /**
       @roseuid 3E669DD100CF
     */
    public static native int NumberBaseShells(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E669DD100D9
     */
    public static native int FindBaseShell(int pQuestion, int dwpPatch, int Index);
    
    /**
       @roseuid 3E669DD100E3
     */
    public static native void DetachConnector(int pQuestion, int dwpPatch, int dwpCon);
    
    /**
       @roseuid 3E669DD100F7
     */
    public static native void AddConnector(int pQuestion, int dwpPatch, int dwpCon);
    
    /**
       @roseuid 3E669DD1010B
     */
    public static native int NumberConnectors(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E669DD10115
     */
    public static native int FindConnector(int pQuestion, int dwpPatch, int Index);
    
    /**
       @roseuid 3E669DD10129
     */
    public static native int GetDeadConnector(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E669DD10133
     */
    public static native int AddInlet(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E669DD1013D
     */
    public static native int AddOutlet(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E669DD10151
     */
    public static native int MakeNew(int pQuestion, String Name);
    
    /**
       @roseuid 3E669DD1015B
     */
    public static native void SetFileName(int pQuestion, int dwpPatch, String FileName);
    
    /**
       @roseuid 3E669DD1017A
     */
    public static native int LoadPatchFile(int pQuestion, String FileName, int dwpParent);
    
    /**
       @roseuid 3E669DD10184
     */
    public static native String GetFileName(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E669DD1018E
     */
    public static native boolean Save(int pQuestion, int dwpPatch, String FileName);
    
    /**
       @roseuid 3E669DD101A2
     */
    public static native void Destroy(int pQuestion, int dwpPatch);
    
    /**
       @roseuid 3E669DD101AC
     */
    public static native void SwapOutlets(int pQuestion, int dwpPatch, int Outlet1, int Outlet2);
    
    /**
       @roseuid 3E669DD101C0
     */
    public static native void SwapInlets(int pQuestion, int dwpPatch, int Inlet1, int Inlet2);
    
    /**
       @roseuid 3E669DD101CA
     */
    public static native int GetInlet(int pQuestion, int dwpPatch, int SocketNum);
    
    /**
       @roseuid 3E669DD101D4
     */
    public static native int GetOutlet(int pQuestion, int dwpPatch, int SocketNum);
    
    /**
       Gets the Port number of the Outlet port
       @roseuid 3E669DD101F2
     */
    public static native int GetOutletPortNumber(int pQuestion, int dwpShell);
    
    /**
       Gets the Port number of the Inlet port
       @roseuid 3E669DD10206
     */
    public static native int GetInletPortNumber(int pQuestion, int dwpShell);
    
    /**
       Returns the Number of orphan patches
       @roseuid 3E669DD10210
     */
    public static native int NumberPatches(int pQuestion);
    
    /**
       returns the Patch given an index
       @roseuid 3E669DD10224
     */
    public static native int GetPatch(int pQuestion, int patch_num);
}
