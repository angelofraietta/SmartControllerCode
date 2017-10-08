// Source file: C:/develop/JSmartController/src/jsmartcontroller/ViewObject.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;


public class ViewObject extends View {
    /**
       BaseShell Hook For the object
     */
    public BaseShellHook _pHook;

    /**
       @roseuid 3E890D700036
     */
    public void setHook(BaseShellHook pHook) {
      _pHook = pHook;
      this.dwpShell = _pHook._pObject;
    }

    /**
       @roseuid 3E92165D038D
     */
    ViewObject() {
    }

    /**
       Sets The bounds of Object
       @roseuid 3E92166A027D
     */
    public void SetBounds(Rectangle new_position) {
      this.top = new_position.y;
      this.width = new_position.width;
      this.left = new_position.x;
      this.height = new_position.height;
    }

    /**
       Stores View
       @roseuid 3E921F650139
     */
    public boolean StoreView(int pQuestion, int dwpPatch, int viewNum) {
      return View.AddViewObject(pQuestion, dwpPatch, viewNum, dwpShell, top, left, height, width, tag);
    }
}
