// Source file: C:/develop/JSmartController/src/jsmartcontroller/SysexFileCreator.java

package jsmartcontroller;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;

import Jni.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import java.io.*;
import java.util.*;

class SysexFileCreator_SendFileMenu_actionAdapter implements ActionListener {
    SysexFileCreator adaptee;

    /**
       @roseuid 3E94B14800A1
     */
    SysexFileCreator_SendFileMenu_actionAdapter(SysexFileCreator adaptee) {
    }

    /**
       @roseuid 3E94B14800A3
     */
    public void actionPerformed(ActionEvent e) {
    }
}
public class SysexFileCreator extends JFrame {
    private int _pinterface;
    String _filename;
    BorderLayout borderLayout1 = new BorderLayout ();
    static String _init_dir = null;
    JPanel jPanel2 = new JPanel ();
    JPanel jPanel3 = new JPanel ();
    JButton CreateSysexBtn = new JButton ();
    JLabel jLabel1 = new JLabel ();
    JTextField SelectedPatch = new JTextField ();
    JLabel jLabel2 = new JLabel ();
    static final String _dat_ext = new String (".dat");
    static final String _proj_ext = new String (".prj");
    static final String _patch_designator = new String ("Patch");
    static final String _file_designator = new String ("File");
    static final String _kill_command = new String ("KillPatches");
    Vector target_filename_list = new Vector();
    JEditorPane FileList = new JEditorPane();
    String _patch_filename = null;
    String _project_filename = null;

  JMenuBar jMenuBar1 = new JMenuBar();
  JMenu jMenu1 = new JMenu();
  JMenuItem SaveMenuSelect = new JMenuItem();
  JButton AddFilesButton = new JButton ();
  JButton SetPatchButton = new JButton ();
  JCheckBox KillPatchesCheck = new JCheckBox ();
  JMenuItem OpenProjectMenu = new JMenuItem();

    /**
       @roseuid 3E94B148003D
     */
    SysexFileCreator() {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    _pinterface = 0;
    }

    SysexFileCreator(int p_interface) {
    try {
      jbInit();
    }

    catch(Exception e) {
      e.printStackTrace();
    }
    CreateSysexBtn.setText("Transfer Files");
    _pinterface = p_interface;
    }


    /**
       @roseuid 3E94B148004F
     */
    private void jbInit() throws Exception {
    this.getContentPane().setLayout(borderLayout1);
    this.setSize(new Dimension(454, 335));
    jPanel3.setMinimumSize(new Dimension(40, 40));
    jPanel3.setPreferredSize(new Dimension(40, 40));
    CreateSysexBtn.setText("Create Data File");
    CreateSysexBtn.addActionListener(new SysexFileCreator_CreateSysexBtn_actionAdapter(this));
    jPanel2.setBorder(BorderFactory.createRaisedBevelBorder());
    jPanel2.setDebugGraphicsOptions(0);
    jPanel2.setPreferredSize(new Dimension(500, 200));
    jPanel2.setRequestFocusEnabled(true);
    jPanel2.setLayout(null);
    jLabel1.setForeground(Color.black);
    jLabel1.setText("Selected Patch:");
    jLabel1.setBounds(new Rectangle(18, 36, 132, 21));
    SelectedPatch.setForeground(Color.black);
    SelectedPatch.setMinimumSize(new Dimension(100, 21));
    SelectedPatch.setPreferredSize(new Dimension(100, 21));
    SelectedPatch.setToolTipText("");
    SelectedPatch.setText("");
    SelectedPatch.setBounds(new Rectangle(16, 62, 134, 21));
    jLabel2.setText("Files To Send");
    jLabel2.setBounds(new Rectangle(184, 32, 86, 19));
    FileList.setBorder(BorderFactory.createLoweredBevelBorder());
    FileList.setBounds(new Rectangle(180, 55, 217, 122));
    jMenu1.setText("File");
    SaveMenuSelect.setText("Save");
    SaveMenuSelect.addActionListener(new SysexFileCreator_SaveMenuSelect_actionAdapter(this));
    AddFilesButton.setBounds(new Rectangle(183, 3, 129, 25));
    AddFilesButton.setMaximumSize(new Dimension(2000, 2000));
    AddFilesButton.setToolTipText("Select the files to send");
    AddFilesButton.setVerifyInputWhenFocusTarget(true);
    AddFilesButton.setMargin(new Insets(2, 14, 2, 14));
    AddFilesButton.setText("Add Files");
    AddFilesButton.addActionListener(new SysexFileCreator_AddFilesButton_actionAdapter(this));
    SetPatchButton.setBounds(new Rectangle(1, 2, 143, 23));
    SetPatchButton.setMaximumSize(new Dimension(4000, 4000));
    SetPatchButton.setToolTipText("Sets which Patch is loaded");
    SetPatchButton.setText("Set Patch");
    SetPatchButton.addActionListener(new SysexFileCreator_SetPatchButton_actionAdapter(this));
    KillPatchesCheck.setMaximumSize(new Dimension(2000, 2000));
    KillPatchesCheck.setToolTipText("Kill the existing loaded patches");
    KillPatchesCheck.setText("Kill existing Patches");
    KillPatchesCheck.setBounds(new Rectangle(14, 96, 170, 23));
    OpenProjectMenu.setText("Open");
    OpenProjectMenu.addActionListener(new SysexFileCreator_OpenProjectMenu_actionAdapter(this));
    this.getContentPane().add(jPanel3, BorderLayout.SOUTH);
    jPanel3.add(CreateSysexBtn, null);
    this.getContentPane().add(jPanel2, BorderLayout.CENTER);
    jPanel2.add(AddFilesButton, null);
    jPanel2.add(SetPatchButton, null);
    jPanel2.add(jLabel1, null);
    jPanel2.add(SelectedPatch, null);
    jPanel2.add(jLabel2, null);
    jPanel2.add(FileList, null);
    jPanel2.add(KillPatchesCheck, null);
    this.setJMenuBar(jMenuBar1);
    jMenuBar1.add(jMenu1);
    jMenu1.add(SaveMenuSelect);
    jMenu1.add(OpenProjectMenu);
    }



    /**
       Send message if KillPatches checkbox is checked
       @roseuid 3E94B1EF00D0
     */
    private void KillPatches() {
      if (this.KillPatchesCheck.isSelected())
        {
          Patch.Destroy(_pinterface, 0);
          System.out.println ("Kill Patches");
        }
    }

    /**
       Sends all Files in FileList
       @roseuid 3E94B2090362
     */
    private void SendFiles() {
      File f = new File (_init_dir);


      for (int i = 0; i < target_filename_list.size(); i++)
      {
        String filename  = (String) target_filename_list.get(i);
        String full_path = _init_dir +  f.separatorChar + filename;
        FileSend.SendFile(_pinterface, filename, full_path);
        System.out.println ("Sending File " + full_path);
      }


    }

    /**
       Sens message if filename is available
       @roseuid 3E94B2690053
     */
    private void ExecutePatch() {
      if (_patch_filename != null)
      {
        Patch.LoadPatchFile(_pinterface, _patch_filename, 0);
        System.out.println ("Execute Patch " + _patch_filename);
      }

    }


    /**
       Sens message if filename is available
       @roseuid 3E94D7FE0314
     */
    private void SelectFiles() {
      JFileChooser OpenDialog = new JFileChooser ();
      //OpenDialog.setFileFilter(new PatchFileFilter());
      OpenDialog.setMultiSelectionEnabled(true);
      if (_init_dir != null)
      {
        File f = new File (_init_dir);
        OpenDialog.setCurrentDirectory(f);
      }

      int ret = OpenDialog.showOpenDialog(this);
      if (ret == JFileChooser.APPROVE_OPTION)
      {
        File [] file = OpenDialog.getSelectedFiles();
        int num_files = file.length;
        _init_dir = OpenDialog.getCurrentDirectory().getAbsolutePath();
        for (int i = 0; i < num_files; i++)
        {
          String filename = file[i].getName();
          AddFile (filename);
        }
      }
      else
      {
          System.out.println("Open command cancelled by user.");
      }

    }

    /**
       Sens message if filename is available
       @roseuid 3E94D80601C2
     */
    private void SelectPatch() {
      JFileChooser OpenDialog = new JFileChooser ();
      OpenDialog.setFileFilter(new PatchFileFilter());
      OpenDialog.setMultiSelectionEnabled(false);
      if (_init_dir != null)
      {
        File f = new File (_init_dir);
        OpenDialog.setCurrentDirectory(f);
      }
      int ret = OpenDialog.showOpenDialog(this);
      if (ret == JFileChooser.APPROVE_OPTION)
      {
        File file = OpenDialog.getSelectedFile();
        _init_dir = OpenDialog.getCurrentDirectory().getAbsolutePath();

        _patch_filename = file.getName();
        SelectedPatch.setText(_patch_filename);
      }
      else
      {
          System.out.println("Open command cancelled by user.");
      }

    }

    private void OpenProject() {
      JFileChooser OpenDialog = new JFileChooser ();
      OpenDialog.setFileFilter(new ProjectFileFilter());
      OpenDialog.setMultiSelectionEnabled(false);
      if (_init_dir != null)
      {
        File f = new File (_init_dir);
        OpenDialog.setCurrentDirectory(f);
      }
      int ret = OpenDialog.showOpenDialog(this);
      if (ret == JFileChooser.APPROVE_OPTION)
      {
        File file = OpenDialog.getSelectedFile();
        _init_dir = OpenDialog.getCurrentDirectory().getAbsolutePath();

        _init_dir = OpenDialog.getCurrentDirectory().getAbsolutePath();
        _project_filename = OpenDialog.getCurrentDirectory().getAbsolutePath() + file.separatorChar + file.getName();
        LoadProject();
      }
      else
      {
          System.out.println("Open command cancelled by user.");
      }

    }

    void LoadProject(){
      // first initialise the page
      _patch_filename = null;
      SelectedPatch.setText("");

      target_filename_list.clear();
      FileList.setText("");
      this.KillPatchesCheck.setSelected(false);

      // now read from the file
      try
      {
        FileReader infile = new FileReader (_project_filename);
        int next_char = infile.read();
        String buf = new String();
        while (next_char != -1)
        {
          buf = buf + (char)next_char;
          next_char = infile.read();
        }
        infile.close();
        ProcessProject (buf);
      }
      catch (Exception e) {
        e.printStackTrace();
      }


    }

    private void ProcessProject (String file_data){
      StringTokenizer tokenizer = new StringTokenizer (file_data);
      int num_tokens = tokenizer.countTokens();
      while (tokenizer.hasMoreTokens())
      {
        String token = tokenizer.nextToken();
        if (token.equalsIgnoreCase(_patch_designator))
        {
          if (tokenizer.hasMoreTokens())
          {
            _patch_filename = tokenizer.nextToken();
            SelectedPatch.setText(_patch_filename);
          }
        }
        else if (token.equalsIgnoreCase(_file_designator))
        {
          if (tokenizer.hasMoreTokens())
          {
            _filename = tokenizer.nextToken();
            AddFile(_filename);
          }
        }
        else if (token.equalsIgnoreCase(_kill_command))
        {
          this.KillPatchesCheck.setSelected(true);
        }

      }

    }
    private void SaveProject(){
      if (_project_filename == null)
      {
        JFileChooser SaveDialog = new JFileChooser ();
        SaveDialog.setFileFilter(new ProjectFileFilter());

        SaveDialog.setMultiSelectionEnabled(false);
        if (_init_dir != null)
        {
          File f = new File (_init_dir);
          SaveDialog.setCurrentDirectory(f);
        }

        int ret = SaveDialog.showSaveDialog(this);
        if (ret == JFileChooser.APPROVE_OPTION)
        {
          File file = SaveDialog.getSelectedFile();
          _init_dir = SaveDialog.getCurrentDirectory().getAbsolutePath();
          _project_filename = SaveDialog.getCurrentDirectory().getAbsolutePath() + file.separatorChar + file.getName();

          if (!_project_filename.endsWith(_proj_ext))
          {
            _project_filename += _proj_ext;
          }

        }
        else
        {
          System.out.println("Open command cancelled by user.");
        }
      }

      if (_project_filename != null)
      {
        try
          {
            FileWriter outfile = new FileWriter(_project_filename);
            outfile.write(_patch_designator + " " +_patch_filename +  "\r\n");
            for (int i = 0; i < target_filename_list.size(); i++)
            {
              outfile.write (_file_designator + " " +(String) target_filename_list.get(i) +  "\r\n");
            }

          if (this.KillPatchesCheck.isSelected())
          {
             outfile.write (_kill_command +  "\r\n");

          }
            outfile.close();
          }
          catch (Exception e) {
            e.printStackTrace();
          }

      }
    }

    private void PerformTransfer(){
      KillPatches();
      SendFiles();
      ExecutePatch();
    }
    /**
       Creates The SYSex file
       @roseuid 3E94D87D0046
     */
    private void CreateSysex() {
      // Get the Name of the file to save
      JFileChooser SaveDialog = new JFileChooser();
      SaveDialog.setFileFilter(new DataFileFilter());
      String init_dir = PatchEditor.GetDefaultDirectory();

      if (init_dir != null)
      {
        File f = new File (init_dir);
        SaveDialog.setCurrentDirectory(f);
      }


      int ret = SaveDialog.showSaveDialog(this);
      if (ret == JFileChooser.APPROVE_OPTION)
      {
        File file = SaveDialog.getSelectedFile();
        String filename = file.getName();

        String filepath = SaveDialog.getCurrentDirectory().getAbsolutePath() + file.separatorChar;
        String current_path = PatchEditor.GetDefaultDirectory();
        PatchEditor.SetDefaultDirectory(filepath);

        if (!filename.endsWith(_dat_ext))
        {
          filename += _dat_ext;
        }

        String sysex_file = filepath + filename;
        System.out.println("Sysex Filename: " +  sysex_file);


        _pinterface = PatchEditor.OpenSysexFile(sysex_file);

        if (_pinterface != 0)
        {
          System.out.println("Opened: " +  sysex_file);

          // now execute all The commands
          PerformTransfer();

          PatchEditor.CloseSysexFile(_pinterface);
          this.dispose();
          System.out.println("Wrote: " +  sysex_file);
          _pinterface = 0;
        }
      }
      else
      {
          System.out.println("Open command cancelled by user.");
      }

    }

    /**
       @roseuid 3E94DB0E02AE
     */
    void AddFilesButton_actionPerformed(ActionEvent e) {
      SelectFiles();
    }

    /**
       @roseuid 3E94DE38033F
     */
    public boolean AddFile(String target_filename) {
      target_filename_list.add(target_filename);
      target_filename = target_filename + "\r\n";
      FileList.setText(FileList.getText() + target_filename);
      return true;

    }

  void SetPatchButton_actionPerformed(ActionEvent e) {
    SelectPatch ();
  }

  void CreateSysexBtn_actionPerformed(ActionEvent e) {
    if (_pinterface == 0)
    {
      CreateSysex();
    }
    else
    {
      PerformTransfer();
      this.dispose();
    }


  }

  void jMenu1_actionPerformed(ActionEvent e) {
  }

  void SaveMenuSelect_actionPerformed(ActionEvent e) {
    SaveProject();
  }

  void OpenProjectMenu_actionPerformed(ActionEvent e) {
    OpenProject();
  }
}
/*
SysexFileCreator.AddFile(String){
    }

*/

class SysexFileCreator_CreateSysexBtn_actionAdapter implements java.awt.event.ActionListener {
  SysexFileCreator adaptee;

  SysexFileCreator_CreateSysexBtn_actionAdapter(SysexFileCreator adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.CreateSysexBtn_actionPerformed(e);
  }
}

class SysexFileCreator_SaveMenuSelect_actionAdapter implements java.awt.event.ActionListener {
  SysexFileCreator adaptee;

  SysexFileCreator_SaveMenuSelect_actionAdapter(SysexFileCreator adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.SaveMenuSelect_actionPerformed(e);
  }
}

class SysexFileCreator_AddFilesButton_actionAdapter implements java.awt.event.ActionListener {
  SysexFileCreator adaptee;

  SysexFileCreator_AddFilesButton_actionAdapter(SysexFileCreator adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.AddFilesButton_actionPerformed(e);
  }
}

class SysexFileCreator_SetPatchButton_actionAdapter implements java.awt.event.ActionListener {
  SysexFileCreator adaptee;

  SysexFileCreator_SetPatchButton_actionAdapter(SysexFileCreator adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.SetPatchButton_actionPerformed(e);
  }
}

class SysexFileCreator_OpenProjectMenu_actionAdapter implements java.awt.event.ActionListener {
  SysexFileCreator adaptee;

  SysexFileCreator_OpenProjectMenu_actionAdapter(SysexFileCreator adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.OpenProjectMenu_actionPerformed(e);
  }
}
