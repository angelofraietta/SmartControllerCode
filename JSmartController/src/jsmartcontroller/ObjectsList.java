// Source file: C:/develop/JSmartController/src/jsmartcontroller/ObjectsList.java

package jsmartcontroller;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.DefaultListModel;
import java.util.*;

public class ObjectsList extends JFrame {
    /**
       The List of Object Types that can be created
     */
    JList ObjectList = new JList ();
    BorderLayout borderLayout1 = new BorderLayout ();
    JPanel BottomPanel = new JPanel ();
    JButton CreateButton = new JButton ();
    SortedListModel  ListModel = new SortedListModel ();
    int _presentation;
    int _patch;
    PatchForm _creator;
    Point _position = null;
    Point _create_position = null;
    JButton CloseButton = new JButton();

    /**
       @roseuid 3E7A82A80327
     */
    public ObjectsList() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    }

    public ObjectsList(int presentation, int patch, PatchForm creator, Point position){
      _presentation = presentation;
      _patch = patch;
      _creator = creator;
      if (position == null)
        {
          position = new Point(10, 10);
        }

      _position = new Point (position);
      _create_position = new Point (position);
      try {
        jbInit();
      }
      catch(Exception e) {
        e.printStackTrace();
      }
      loadObjects();
    }
    /**
       @roseuid 3E7A82A80331
     */

    public void SetPatch (int pPatch){
       _patch = pPatch;
    }

    private void jbInit() throws Exception {
    this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    this.setTitle("Objects");
    this.addWindowListener(new ObjectsList_this_windowAdapter(this));
    this.getContentPane().setLayout(borderLayout1);
    ObjectList.setDebugGraphicsOptions(0);
    ObjectList.setMaximumSize(new Dimension(0, 0));
    BottomPanel.setMinimumSize(new Dimension(30, 30));
    BottomPanel.setPreferredSize(new Dimension(60, 60));
    BottomPanel.setToolTipText("");
    CreateButton.setToolTipText("");
    CreateButton.setText("Create");
    CreateButton.addActionListener(new ObjectsList_CreateButton_actionAdapter(this));
    CloseButton.setText("Close");
    CloseButton.addActionListener(new ObjectsList_CloseButton_actionAdapter(this));
    this.getContentPane().add(ObjectList, BorderLayout.CENTER);
    this.getContentPane().add(BottomPanel, BorderLayout.SOUTH);
    BottomPanel.add(CreateButton, null);
    BottomPanel.add(CloseButton, null);
    }

    /**
       Loads all the different Object types
       @roseuid 3E7A82E00291
     */

    public void loadObjects() {
      ObjectList.setModel(ListModel);
      int num_objects = BaseShell.GetNumObjectTypes(_presentation);
      System.out.println (num_objects);

      for (int i = 0; i < num_objects; i++)
      {
        String ObjectName = BaseShell.GetObjectType(_presentation, i);
        ListModel.add(ObjectName);
      }

    }

    private void CreateNewObject (int index){
      String objectType = ObjectList.getSelectedValue().toString();
      System.out.println("Creating " + objectType);
      int pShell = 0;

      if (objectType.compareTo(new String("PatchFromFile")) != 0)
      {
        pShell = BaseShell.Create(_presentation, objectType, _patch);
        // if it is a patch, we will give it a view
        if (objectType.compareTo(new String("Patch")) == 0)
        {
          System.out.println("Add View");
           View.AddView(_presentation, pShell);
        }
      }
      else
      {
        //We need to create a Patch File
        System.out.println("We need to create a Patch File defined by object type");
        JFileChooser OpenDialog = new JFileChooser ();
        OpenDialog.setFileFilter(new PatchFileFilter());
        String init_dir = PatchEditor.GetDefaultDirectory();
        if (init_dir != null)
        {
          File f = new File (init_dir);
          OpenDialog.setCurrentDirectory(f);
        }
        int ret = OpenDialog.showOpenDialog(ObjectsList.this);
        if (ret == JFileChooser.APPROVE_OPTION)
        {
          File file = OpenDialog.getSelectedFile();
          String filename = file.getName();
          String filepath = OpenDialog.getCurrentDirectory().getAbsolutePath() + file.separatorChar;
          String current_path = PatchEditor.GetDefaultDirectory();
          PatchEditor.SetDefaultDirectory(filepath);

          System.out.println("Path: " + filepath + filename );
          pShell = Patch.LoadPatchFile(_presentation, filename, _patch);
        }

      }

      if (pShell != 0)
      {
        Patch.AddBaseShell(_presentation, _patch, pShell);
        _creator.AddObject(pShell, _patch, _position);
        // now add 10 to the position so we can see another if we press create again
        _position.setLocation(_position.getX() + 10, _position.getY() +10);
      }
    }

  void CreateButton_actionPerformed(ActionEvent e) {
    int index = ObjectList.getSelectedIndex();
    if (index >= 0)
    {
      CreateNewObject (index);
    }
  }

  void CloseButton_actionPerformed(ActionEvent e) {
    this.dispose();
  }

  void this_windowDeactivated(WindowEvent e) {
    _position.setLocation(_create_position.getLocation());
  }


}

class ObjectsList_CreateButton_actionAdapter implements java.awt.event.ActionListener {
  ObjectsList adaptee;

  ObjectsList_CreateButton_actionAdapter(ObjectsList adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.CreateButton_actionPerformed(e);
  }
}


class ObjectsList_CloseButton_actionAdapter implements java.awt.event.ActionListener {
  ObjectsList adaptee;

  ObjectsList_CloseButton_actionAdapter(ObjectsList adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.CloseButton_actionPerformed(e);
  }
}

class ObjectsList_this_windowAdapter extends java.awt.event.WindowAdapter {
  ObjectsList adaptee;

  ObjectsList_this_windowAdapter(ObjectsList adaptee) {
    this.adaptee = adaptee;
  }
  public void windowDeactivated(WindowEvent e) {
    adaptee.this_windowDeactivated(e);
  }
}

class SortedListModel extends AbstractListModel {

  // Define a SortedSet
  SortedSet model;

  public SortedListModel() {
    // Create a TreeSet
    // Store it in SortedSet variable
    model = new TreeSet();
  }

  // ListModel methods
  public int getSize() {
    // Return the model size
    return model.size();
  }

  public Object getElementAt(int index) {
    // Return the appropriate element
    return model.toArray()[index];
  }

  // Other methods
  public void add(Object element) {
    if (model.add(element)) {
      fireContentsChanged(this, 0, getSize());
    }
  }

  public void addAll(Object elements[]) {
    Collection c = Arrays.asList(elements);
    model.addAll(c);
    fireContentsChanged(this, 0, getSize());
  }

  public void clear() {
    model.clear();
    fireContentsChanged(this, 0, getSize());
  }

  public boolean contains(Object element) {
    return model.contains(element);
  }

  public Object firstElement() {
    // Return the appropriate element
    return model.first();
  }

  public Iterator iterator() {
    return model.iterator();
  }

  public Object lastElement() {
    // Return the appropriate element
    return model.last();
  }

  public boolean removeElement(Object element) {
    boolean removed = model.remove(element);
    if (removed) {
      fireContentsChanged(this, 0, getSize());
    }
    return removed;
  }
}
