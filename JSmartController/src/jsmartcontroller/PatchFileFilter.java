// Source file: C:/develop/JSmartController/src/jsmartcontroller/PatchFileFilter.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.io.File;
import javax.swing.filechooser.FileFilter;


/**
   Allaws Files to be Displayed in A filechooser
 */
public class PatchFileFilter extends FileFilter {

    /**
       @roseuid 3E8CE71B0166
     */
    public boolean accept(File f) {
      return f.getName().toLowerCase().endsWith(".smp") || f.isDirectory();
    }

    /**
       Returns the Description of The File Type
       @roseuid 3E8CE727033A
     */
    public String getDescription() {
      return "Smart Controller Patch";
    }
}
/*
PatchFileFilter.PatchFileFilter(){
    }

*/
