// Source file: d:/develop/smartController/controller/source/engineinterface/PatchEditorInterface/Jni/PatchEditor.java

package Jni;

/*
PatchEditor Documentation: Fundamental PatchEditor Functions for Initialising Simulator

*/

public class PatchEditor {
    
    static {
      System.loadLibrary("smartcontroljava");
    }
    PatchEditor() {
    }
    /**
       Returns the Current PresentationQuestion of Shared Library
       @roseuid 3E56A4270310
     */
    public static native int GetCurrentInterface();
    
    /**
       @roseuid 3E66C25201C7
     */
    public static native boolean Initialise();
    
    /**
       @roseuid 3E66C25F02B6
     */
    public static native boolean Deinitialise();
    
    /**
       Opens A Midi Port and assigns a Number
       @roseuid 3E66C293009E
     */
    public static native boolean OpenMidiInputPort(int device_number, int index);
    
    /**
       Opens A Midi Port and assigns a Number
       @roseuid 3E66C3380204
     */
    public static native boolean OpenMidiOutputPort(int device_number, int index);
    
    /**
       @roseuid 3E66C3580051
     */
    public static native boolean CloseMidiOutputPorts();
    
    /**
       @roseuid 3E66C36801A9
     */
    public static native boolean CloseMidiInputPorts();
    
    /**
       Sets the default directory within simulator
       @roseuid 3E66C3B20322
     */
    public static native boolean SetDefaultDirectory(String path);
    
    /**
       @roseuid 3E7DA896036A
     */
    public static native String GetDefaultDirectory();
    
    /**
       Opens a File for a Sysex dump. Returns Presentation Question
       @roseuid 3E93784D000C
     */
    public static native int OpenSysexFile(String filename);
    
    /**
       Closes Sysex File
       @roseuid 3E9378A7017E
     */
    public static native boolean CloseSysexFile(int presentation);
    
    /**
       Opens a Sysex file to prpare for Transmit
       @roseuid 3E9378DD003B
     */
    public static native int PrepareTxSysexFile(String filename);
    
    /**
       Tansmits Sysex Data to a Midi Port
       @roseuid 3EAE010203C4
     */
    public static native void TxSysexData(int key, int port, int num_bytes);
    
    /**
       @roseuid 3EAE0161035D
     */
    public static native void CloseTxSysexFile(int key);
    
    /**
       Returns the Number
       @roseuid 3E93C033016B
     */
    public static native int NumMidiOut();
    
    /**
       Returns the Number
       @roseuid 3E93C05A023A
     */
    public static native int NumMidiIn();
    
    /**
       Returns the name of the device given a device index
       @roseuid 3E93C0620281
     */
    public static native String MidOutName(int index);
    
    /**
       Returns the name of the device given a device index
       @roseuid 3E93C0900024
     */
    public static native String MidInName(int index);
    
    /**
       Opens a new Presentation Inteface
       @roseuid 4088318D03D8
     */
    public static native int OpenInterface(String name, int port);
    
    /**
       Sets the IP Address for the PresentationInterface
       @roseuid 4088322C0167
     */
    public static native boolean SetInterfaceAddress(int presentation, String address);
    
    /**
       Sets the Current Interface
       @roseuid 40883DA901F4
     */
    public static native void SetCurrentInterface(int new_interface);
    
    /**
       Pushes a new Value from the Simulator onto the Input Queue. The Value is Added In a Floating Value with 1 being the Max amount
       @roseuid 415723BA0205
     */
    public static native void AddAnalogueValue(int channel, float value);
    
    /**
       Pushes a new Value from the Simulator onto the Input Queue
       @roseuid 415723F80225
     */
    public static native void AddDigitalValue(int channel, boolean value);
    
    /**
       Returns The Value of the Digital output
       @roseuid 4157241802E0
     */
    public static native boolean GetDigitalValue(int channel);
    
    /**
       Returns The Value of the Analogue output as a float, 1 being the maximum
       @roseuid 415724580244
     */
    public static native float GetAnalogueValue(int channel);
    
    /**
       @roseuid 415725020169
     */
    public static boolean IsConnected(int pinterface) {
      return true; //Patch.NumberPatches(pinterface) >= 0;
    }
}
