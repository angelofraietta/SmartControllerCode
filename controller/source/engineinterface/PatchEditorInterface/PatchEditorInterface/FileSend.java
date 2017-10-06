// Source file: c:/develop/smartController/controller/source/engineinterface/PatchEditorInterface/PatchEditorInterface/FileSend.java

package PatchEditorInterface;

/**
   JNI Interface for Sending data through FileQuestion
 */
public class FileSend {
    
    FileSend() {
    }
    /**
       @roseuid 3E9384790342
     */
    public static native boolean SendFile(int pQuestion, String target_filename, String source_filename);
    
    /**
       @roseuid 3E9384790356
     */
    public static native int CloseFile(int pQuestion, int key);
    
    /**
       Stores the Data to NVRAM
       @roseuid 3E9384790360
     */
    public static native int SaveNVRAM(int pQuestion);
    
    /**
       Clears NVRAM
       @roseuid 3E938479036A
     */
    public static native int EraseNVRAM(int pQuestion);
    
    /**
       Sends command to Write a file to Disk sending the filename and the crc of the file
       @roseuid 3EAE0FD2015A
     */
    public static native boolean SaveToIde(int pQuestion, String target_filename, String source_filename);
}
