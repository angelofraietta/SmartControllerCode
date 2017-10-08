// Source file: C:/develop/JSmartController/src/jsmartcontroller/BaseShellInlet.java

package jsmartcontroller;

/* commence import */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import ViewForms.Graphics.*;
/* finsih import*/



public class BaseShellInlet extends CTopFollower {
    public BaseShellHook _pHook;
    private String _name = null;

    /**
       @roseuid 3E83D5CE0178
     */
    public BaseShellInlet(CObjectBox parent, int index, BaseShellHook pHook) {
      super (parent, index);
      _pHook = pHook;
    }

    /**
       Process the Mouse Drag
       @roseuid 3E876C64031B
     */
    protected void processMouseEntered(int x, int y) {
       super.processMouseEntered (x, y);
       GetPatchForm().DisplayText (GetName());
    }

    /**
       Process the Mouse Drag
       @roseuid 3E876C640325
     */
    protected void processMouseExited(int x, int y) {
      super.processMouseExited(x, y);
      GetPatchForm().DisplayText ("");
    }

    /**
       Returns the _name variable. If _name has not been set yet, the value ios obtained from the engine.
       @roseuid 3E876E6F039F
     */
    public String GetName() {
      if (_name == null)
      {
        _name = BaseShell.GetInletName(_pHook._presentation, _pHook._pObject, super._index);
      }
    return _name;
    }

    /**
       @roseuid 3E877F9C0013
     */
    protected void performConnection() {
      if (_mouseOverBottom != null)
      {
        if (_mouseOverBottom.CanConnect(this))
        {
          BaseShellInlet inlet = this;
          BaseShellOutlet outlet = (BaseShellOutlet)_mouseOverBottom;

          // See if We can Create a connector within engine
          int presentation = this._pHook._presentation;
          int inlet_base = inlet._pHook._pObject;
          int inlet_index = inlet._index;
          int outlet_base = outlet._pHook._pObject;
          int outlet_index = outlet._index;

          int pConnector = Connector.Create(presentation);

          if (pConnector != 0)
          {
            Connector.SetInletBase(presentation, pConnector, inlet_base);
            Connector.SetInletNum(presentation, pConnector, inlet_index);

            Connector.SetOutletBase(presentation, pConnector, outlet_base);
            Connector.SetOutletNum(presentation, pConnector, outlet_index);

            if (Connector.MakeConnection(presentation, pConnector))
            {
              final ViewForm line_parent = (ViewForm) _parent._parent;
              int pPatch = Identity.GetParent(presentation, inlet_base);
              Identity.SetParent (presentation, pConnector, pPatch);
              Patch.AddConnector(presentation, pPatch, pConnector);
              PatchForm pPatchForm = line_parent._patch_form;

              final ConnectorHook pConHook = pPatchForm.AddConnector(pConnector, pPatch);
              // make a new segment using the top and this
              //new ConnectorLine (inlet, outlet, line_parent, pConHook, null);
              System.out.println("Try Invoke Later");
              try {
                // make a new segment using the top and this
                javax.swing.SwingUtilities.invokeLater(new Runnable() {

                  public void run() {
                    line_parent.AddConnection(pConHook);
                  }
                });
              }
              catch(Exception e) {
                e.printStackTrace();
              }

              //line_parent.AddConnection(pConHook);
            }
          }
        }
      }

    }

    /**
       @roseuid 3EB1F14800B5
     */
    public PatchForm GetPatchForm() {
      return ((BaseShellBox)_parent).GetPatchForm();
    }
}
