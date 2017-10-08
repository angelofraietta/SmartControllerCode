// Source file: C:/develop/JSmartController/src/jsmartcontroller/ProjectFileFilter.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.io.File;

import javax.swing.filechooser.FileFilter;


public class ProjectFileFilter extends FileFilter {

    /**
       @roseuid 3EDAD4B903A6
     */
    public boolean accept(File f) {
      return f.getName().toLowerCase().endsWith(".prj") || f.isDirectory();
    }

    /**
       Returns the Description of The File Type
       @roseuid 3EDAD4B903BA
     */
    public String getDescription() {
      return "Smart Controller Project";
    }

    /**
       @roseuid 3EDAD4B903C4
     */
    ProjectFileFilter() {
    }
}
