// Source file: C:/develop/JSmartController/src/jsmartcontroller/DataFileFilter.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.io.File;

import javax.swing.filechooser.FileFilter;


public class DataFileFilter extends FileFilter {

    DataFileFilter() {
    }
    /**
       @roseuid 3E937EBD01ED
     */
    public boolean accept(File f) {
      return f.getName().toLowerCase().endsWith(".dat") || f.isDirectory();
    }

    /**
       Returns the Description of The File Type
       @roseuid 3E937EBD021F
     */
    public String getDescription() {
      return "Sysex data";
    }
}
