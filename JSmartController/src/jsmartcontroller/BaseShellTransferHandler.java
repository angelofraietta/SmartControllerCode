package jsmartcontroller;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import java.awt.dnd.*;
import java.io.*;

/**
 * <p>Title: Smart Controller</p>
 * <p>Description: Smart Controller Patch Editor and Simulator</p>
 * <p>Copyright: Copyright (c) 2003 Angelo Fraietta</p>
 * <p>Company: Angelo Fraietta</p>
 * @author Angelo Fraietta
 * @version 1.0
 */

public class BaseShellTransferHandler extends TransferHandler {
  String mimeType = DataFlavor.javaJVMLocalObjectMimeType +
      ";class=jsmartcontroller.BaseShellHook";
  DataFlavor dataFlavor;

  BaseShellHook _pHook = null;
  ViewForm _target;

  public BaseShellTransferHandler() {
    System.out.println("BaseShellTransferHandler");
    try {
        dataFlavor = new DataFlavor(mimeType);
    } catch (ClassNotFoundException e) {
   e.printStackTrace(); }

  }

  public BaseShellHook GetHook(){
    return _pHook;
  }

  public void SetTarget(ViewForm target){
    _target = target;
  }

  public void SetHook(BaseShellHook pHook) {
    _pHook = pHook;
  }

  public boolean importData(JComponent c, Transferable t) {
    System.out.println("ImportData" );
    ViewObject view_object = new ViewObject ();
    view_object.setHook(_pHook);

    view_object.left = 10;
    view_object.top = 10;
    _target.AddObject(view_object);
    _target.update();

    return true;
  }
  public boolean canImport(JComponent c, DataFlavor[] flavors) {
    boolean ret = false;
    try{
      JToolBar j = (JToolBar) c;
      System.out.println("cannot Import " + c.toString());
    }
    catch (Exception e){
    System.out.println("can Import " );
    ret = _target.GetBaseShellBox(_pHook) == null;

    }

    return ret;
  }

}