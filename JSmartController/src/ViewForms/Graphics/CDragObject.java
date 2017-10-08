// Source file: c:/develop/PatchEditor/ViewForms/Graphics/CDragObject.java

/*
Angelo Fraietta

*/

package ViewForms.Graphics;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
   Object used as a reference for dragging. This has been made an abstract class so its processDrag and endDrag is overridden by the subclass, which in turn will operate on the actual object that is being dragged
 */
public abstract class CDragObject {
    
    /**
       Process the Mouse Drag
       @roseuid 3B69E80602BF
     */
    public abstract void processDrag(MouseEvent evt, int x, int y);
    
    /**
       @roseuid 3B69E97B0384
     */
    public abstract void endDrag(MouseEvent evt, int x, int y);
}
