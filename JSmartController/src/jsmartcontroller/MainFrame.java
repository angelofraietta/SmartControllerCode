package jsmartcontroller;

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Jni.*;
import javax.swing.filechooser.*;
import java.net.*;
import java.util.*;
import java.util.List;

/**
 * <p>Title: Smart Controller</p>
 * <p>Description: Smart Controller Patche Editor and Simulator</p>
 * <p>Copyright: Copyright (c) 2003 Angelo Fraietta</p>
 * <p>Company: Angelo Fraietta</p>
 * @author Angelo Fraietta
 * @version 1.0
 */

class DeviceProber extends Thread {

    protected DatagramSocket socket = null;
    protected int _port = 1113;
    volatile boolean _quit = false;
    final String SmartControlId = new String ("SmartController");
    MainFrame _owner;

    public DeviceProber(MainFrame owner, String name, int port) throws IOException {
        super(name);
        _owner = owner;
        _port = port;
        socket = new DatagramSocket(_port);
    }

    public DeviceProber(MainFrame owner) throws IOException {
        super("");
         _owner = owner;
        socket = new DatagramSocket(_port);
    }

    public boolean SendProbe(){
      // Send a message to the broadcast address and see who responds
      boolean ret = false;
      byte[] buf = new byte[256];
      String dString = new String("Who Are You");
      buf = dString.getBytes();

      try{
        List<NetworkInterface> interfaces = NetworkDevice.viableInterfaces();
        byte[] finalBuf = buf;
        interfaces.forEach(ni -> {

          InetAddress broadcast = NetworkDevice.getBroadcast(ni);


          if (broadcast != null) {
            try {

              DatagramPacket packet;
              packet = new DatagramPacket(finalBuf, finalBuf.length,
                      broadcast, _port);

              WriteDisplayText("Wait for Device Response on port " + _port);
              socket.send(packet);

            } catch (Exception ex) {

            }

          }

        });

        /*
        InetAddress address = InetAddress.getByName("localhost");
        String dString = new String("Who Are You");
        buf = dString.getBytes();

        DatagramPacket packet;
        packet = new DatagramPacket(buf, buf.length,
                                    address, _port);

        WriteDisplayText("Wait for Device Response on port " + _port);
        socket.send(packet);
*/
      } catch (Exception e) {
        e.printStackTrace();
      }
      return ret;
    }

    void DisplaySendLine(String chartype)
    {
      for (int i = 0; i < 40; i++)
      {
        System.out.print(chartype);
      }
      System.out.println(chartype);
    }

    void WriteDisplayText(String text)
    {
      DisplaySendLine("*");
      System.out.println (text);
      DisplaySendLine("*");
    }


    public boolean SendReboot(String reboot_address)
    {
      boolean ret = false;
      byte[] buf = new byte[256];

      try{
        InetAddress address = InetAddress.getByName(reboot_address);
        String dString = new String("Reboot");
        buf = dString.getBytes();

        DatagramPacket packet;
        packet = new DatagramPacket(buf, buf.length,
                                    address, _port);

        WriteDisplayText("Rebooting devices on " + _port);
        socket.send(packet);

      } catch (IOException e) {
        e.printStackTrace();
      }
      return ret;

    }

    public void run() {

        while (!_quit) {
            try {
                byte[] buf = new byte[256];


                // receive request
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                socket.receive(packet);

                InetAddress address = packet.getAddress();
                //System.out.println("Received Device Response from " + address.getHostAddress());
                int received_size = packet.getLength();
                byte[] response_buf = new byte [received_size];

                for (int i = 0; i < received_size; i++)
                {
                  response_buf[i] = buf[i];
                }
                String response = new String(response_buf);
                System.out.println(response);
                ProcessResponse(response, address.getHostAddress());

                // send the response to the client at "address" and "port"
                //
                //int port = packet.getPort();
                //packet = new DatagramPacket(buf, buf.length, address, port);
                //socket.send(packet);
            } catch (IOException e) {
                e.printStackTrace();
                //_quit = true;
            }
        }
        socket.close();
    }

    void ProcessResponse(String response, String address){
      boolean cancel = false;
      String device_name = new String("Error");
      int device_port = 0;
      StringTokenizer tokenizer = new StringTokenizer (response);
      int num_tokens = tokenizer.countTokens();

      //System.out.println(num_tokens);
      for (int i = 0; i < num_tokens && ! cancel; i++)
      {
        String token = tokenizer.nextToken();

        switch (i)
        {
          case 0:
            if (!token.equalsIgnoreCase(SmartControlId))
            {
              cancel = true;
            }
            break;

          case 1:
            device_name = token;
            System.out.println(device_name);
            break;

          default:
            if (i == num_tokens -1)
            {
              device_port = Integer.parseInt(token);
            }
            break;
        } //end switch
      } // end for

      if (!cancel)
      {
        System.out.println(device_name + " " + device_port);
        PresentationParam connection = new PresentationParam(device_name, address, PresentationParam.UDP_TYPE, device_port);
        _owner.DisplayUnconnectedParam(connection);
      }
    }


}

class PresentationParam implements Comparable{
  int _presentation_interface = 0;
  String _name = null;
  String _connection_type = null;
  public String _address = null;
  int _port = 0;
  static String UDP_TYPE = new String ("UDP");

  public int compareTo(Object other) {
    PresentationParam right = (PresentationParam) other;
    return _port - right._port;
  }

  public PresentationParam (int p_interface, String name){
    _presentation_interface = p_interface;
    _name = name;
  }

  public PresentationParam (String name, String address, String connection_type, int port){
    //_presentation_interface = p_interface;
    _name = name;
    _port = port;
    _connection_type = connection_type;
    _address = address;
  }

  public boolean Connect(){
    boolean ret = false;

    if (_connection_type != null && _port != 0 && _address != null)
    {
      _presentation_interface = PatchEditor.OpenInterface(_connection_type,
          _port);
      if (_presentation_interface != 0) {
        System.out.println("Successfule Open");
        PatchEditor.SetInterfaceAddress(_presentation_interface, _address);
        ret = true;
      }
    }
    return ret;
  }

  public int GetPort(){
    return _port;
  }

  public String GetAddress(){
    return _address;
  }
  public int GetPresentation(){
    return _presentation_interface;
  }

  public String GetConnectionName(){
    return _name;
  }
  public String GetDescription(){
    String ret;
    if (_port != 0)
    {
      ret = new String(GetConnectionName() + " " + GetAddress() + " " + GetPort());
    }
    else
    {
      ret = _name;
    }
    return ret;
  }
}

public class MainFrame extends JFrame {
  JPanel contentPane;
  JMenuBar jMenuBar1 = new JMenuBar();
  JMenu jMenuFile = new JMenu();
  JMenuItem jMenuFileExit = new JMenuItem();
  JMenu jMenuHelp = new JMenu();
  JMenuItem jMenuHelpAbout = new JMenuItem();
  JToolBar jToolBar = new JToolBar();
  JButton OpenButton = new JButton();
  JButton NewButton = new JButton();
  JButton jButton3 = new JButton();
  ImageIcon image1;
  ImageIcon image2;
  ImageIcon image3;
  BorderLayout borderLayout1 = new BorderLayout();
  JMenuItem jMenuNewPatch = new JMenuItem();
  JMenuItem jMenuOpen = new JMenuItem();
  JMenuItem StoreSysexMenu = new JMenuItem();
  JMenuItem SendSysexmenu = new JMenuItem();
  static String _dat_ext = new String (".dat");
  JComboBox MidiOutputCombo = new JComboBox();
  JPanel ButtonsPannel = new JPanel();
  JButton CancelButton = new JButton();
  JProgressBar SendProgress = new JProgressBar();

  long _file_size = 0;
  volatile long _bytes_sent = 0;
  volatile int _file_key = 0;
  int _device_num = 0;

  static int _progress_multiplier = 100; // this seems to be the number that works best
  SysexSender _sysex_sender;
  JMenu Device = new JMenu();
  JMenuItem mnuEraseNVRAM = new JMenuItem();
  JMenuItem mnuSaveNVRAM = new JMenuItem();
  JMenuItem mnuKillPatches = new JMenuItem();
  JPanel NetworkPanel = new JPanel();
  JButton ProbeButton = new JButton();
  DeviceProber _prober = null;
  JButton ConnectButton = new JButton();

  JPanel jPanel1 = new JPanel();

  DefaultListModel ConnectedListModel = new DefaultListModel();
  JList ConnectedList = new JList(ConnectedListModel);
  Vector ConnectedParams = new Vector();

  DefaultListModel ProbedListModel = new DefaultListModel();
  JList ProbedList = new JList(ProbedListModel);
  Vector UnconnectedParams = new Vector();

  PresentationParam _selected_interface;

  final int _simulator = PatchEditor.GetCurrentInterface();
  JLabel jLabel1 = new JLabel();
  JLabel lblCurrentPresent = new JLabel();
  JMenuItem mnuReadPatch = new JMenuItem();
  JMenuItem mnuTransferFiles = new JMenuItem();
  JMenuItem mnuSendIde = new JMenuItem();
  JMenuItem mnuReboot = new JMenuItem();

  public boolean IsSimulator(){
    return _simulator == _selected_interface.GetPresentation();
  }

  public void DisplayUnconnectedParam(PresentationParam param){
    ProbedListModel.addElement(param.GetDescription());
    UnconnectedParams.add(param);
  }

  public boolean CanConnect(PresentationParam param){
    boolean ret = true;
    for (int i = 0; i < ConnectedParams.size() && ret; i++)
    {
      PresentationParam current = (PresentationParam)ConnectedParams.elementAt(i);
      ret = current != param;
    }
    return ret;
  }
  //Construct the frame
  public MainFrame() {
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }

    PresentationParam p_interface = new PresentationParam (_simulator, new String("Simulator"));

    lblCurrentPresent.setText(p_interface.GetDescription());

    ConnectedListModel.addElement(p_interface.GetConnectionName());
    ConnectedParams.add((p_interface));
    _selected_interface = p_interface;
    // now open Midi Ports

    for (int i = 0; i < PatchEditor.NumMidiIn(); i++)
    {
      if (!PatchEditor.OpenMidiInputPort(i, i)) {
        System.out.println("Unable to open Input " + i);
      }
      else
      {
        System.out.println("Opened Input " + PatchEditor.MidInName(i));
      }
    }

    for (int i = 0; i < PatchEditor.NumMidiOut(); i++)
    {
      if (!PatchEditor.OpenMidiOutputPort(i, i)) {
        System.out.println("Unable to open Output i");
      }
      else
      {
        System.out.println("Opened Output " + PatchEditor.MidOutName(i));
        MidiOutputCombo.addItem(PatchEditor.MidOutName(i));
      }

    }
    try {
      _prober = new DeviceProber(this);
      _prober.start();
    }    catch(Exception e) {
      e.printStackTrace();
    }

  }


  public synchronized void TransmitBytes(){
    if (_file_size > _bytes_sent)
    {
      int bytes_to_send = _progress_multiplier;
      PatchEditor.TxSysexData(_file_key, _device_num, bytes_to_send);
      System.out.println("Tx Midi Sysex");
      _bytes_sent += bytes_to_send;
      SendProgress.setValue((int)(_bytes_sent / _progress_multiplier));
    }
    else
    {
      StopSysexSend();
    }

  }

  public synchronized void StopSysexSend(){
    PatchEditor.CloseTxSysexFile(_file_key);
    _file_key = 0;
    _file_size = 0;
    SendProgress.setVisible(false);
    CancelButton.setVisible(false);
    SendSysexmenu.setEnabled(true);
    mnuSaveNVRAM.setEnabled(true);
    mnuEraseNVRAM.setEnabled(true);

    _sysex_sender.Stop();
  }

  public synchronized void OpenFromFile (String filename){
    int presentation_question = _selected_interface.GetPresentation();//PatchEditor.GetCurrentInterface();
    if (presentation_question != 0) {
      int pPatch = Patch.LoadPatchFile (presentation_question, filename, 0);

      if (pPatch != 0) {
        PatchForm pPatchform = new PatchForm(presentation_question, pPatch);
        pPatchform.setBounds(this.getBounds());
        pPatchform.setVisible(true);
         pPatchform.setTitle(_selected_interface.GetDescription() + "-" + filename);
      }
      else
      {
        System.out.println("Unable to open: " + filename);
      }
    }

  }

  // Select a Patch from file and open
  public void OpenFromFile (){
    System.out.println("OpenFromFile");
    //  Set Smart Controller Patches fileter
    JFileChooser OpenDialog = new JFileChooser ();
    OpenDialog.setFileFilter(new PatchFileFilter());
    String init_dir = PatchEditor.GetDefaultDirectory();
    if (init_dir != null)
    {
      File f = new File (init_dir);
      OpenDialog.setCurrentDirectory(f);
    }
    int ret = OpenDialog.showOpenDialog(MainFrame.this);
    if (ret == JFileChooser.APPROVE_OPTION)
    {
      File file = OpenDialog.getSelectedFile();
      String filename = file.getName();
      String filepath = OpenDialog.getCurrentDirectory().getAbsolutePath() + file.separatorChar;
      String current_path = PatchEditor.GetDefaultDirectory();
      PatchEditor.SetDefaultDirectory(filepath);

      System.out.println("Path: " + filepath + filename );
      OpenFromFile (filename);
    }
    else
    {
        System.out.println("Open command cancelled by user.");
    }


  }

  //Component initialization
  private void jbInit() throws Exception  {
    image1 = new ImageIcon(jsmartcontroller.MainFrame.class.getResource("openFile.png"));
    image2 = new ImageIcon(jsmartcontroller.MainFrame.class.getResource("closeFile.png"));
    image3 = new ImageIcon(jsmartcontroller.MainFrame.class.getResource("help.png"));
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(borderLayout1);
    this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    this.setSize(new Dimension(558, 335));
    this.setTitle("Smart Controller");
    this.addWindowListener(new MainFrame_this_windowAdapter(this));
    jMenuFile.setText("File");
    jMenuFileExit.setActionCommand("Exit");
    jMenuFileExit.setText("Exit");
    jMenuFileExit.addActionListener(new MainFrame_jMenuFileExit_ActionAdapter(this));
    jMenuHelp.setText("Help");
    jMenuHelpAbout.setText("About");
    jMenuHelpAbout.addActionListener(new MainFrame_jMenuHelpAbout_ActionAdapter(this));
    OpenButton.setIcon(image1);
    OpenButton.addActionListener(new MainFrame_OpenButton_actionAdapter(this));
    OpenButton.setToolTipText("Open File");
    NewButton.setIcon(image2);
    NewButton.addActionListener(new MainFrame_NewButton_actionAdapter(this));
    NewButton.setToolTipText("Close File");
    jButton3.setIcon(image3);
    jButton3.setToolTipText("Help");
    jMenuNewPatch.setActionCommand("NewPatch");
    jMenuNewPatch.addActionListener(new MainFrame_jMenuNewPatch_ActionAdapter(this));
    jMenuNewPatch.setSelected(false);
    jMenuNewPatch.setText("New Patch");
    jMenuOpen.setSelected(false);
    jMenuOpen.setText("Open");
    jMenuOpen.addActionListener(new MainFrame_jMenuOpen_actionAdapter(this));
    StoreSysexMenu.setText("Store Sysex");
    StoreSysexMenu.addActionListener(new MainFrame_StoreSysexMenu_actionAdapter(this));
    SendSysexmenu.setText("Send Sysex");
    SendSysexmenu.addActionListener(new MainFrame_SendSysexmenu_actionAdapter(this));
    ButtonsPannel.setBorder(BorderFactory.createLoweredBevelBorder());
    ButtonsPannel.setMinimumSize(new Dimension(200, 200));
    ButtonsPannel.setPreferredSize(new Dimension(200, 200));
    ButtonsPannel.setLayout(null);
    CancelButton.setBounds(new Rectangle(0, 6, 77, 28));
    CancelButton.setText("Cancel");
    CancelButton.addActionListener(new MainFrame_CancelButton_actionAdapter(this));
    SendProgress.setBounds(new Rectangle(77, 7, 103, 25));
    Device.setText("Device");
    mnuEraseNVRAM.setText("Erase NVRAM");
    mnuEraseNVRAM.addActionListener(new MainFrame_mnuEraseNVRAM_actionAdapter(this));
    mnuSaveNVRAM.setText("Save NVRAM");
    mnuSaveNVRAM.addActionListener(new MainFrame_mnuSaveNVRAM_actionAdapter(this));
    mnuKillPatches.setText("Kill Patches");
    mnuKillPatches.addActionListener(new MainFrame_mnuKillPatches_actionAdapter(this));
    NetworkPanel.setBorder(BorderFactory.createLoweredBevelBorder());
    NetworkPanel.setBounds(new Rectangle(2, 59, 290, 221));
    NetworkPanel.setLayout(null);
    ProbeButton.setBounds(new Rectangle(4, 3, 282, 35));
    ProbeButton.setEnabled(true);
    ProbeButton.setText("Probe");
    ProbeButton.addActionListener(new MainFrame_ProbeButton_actionAdapter(this));
    ProbedList.setBorder(null);
    ProbedList.setBounds(new Rectangle(4, 73, 281, 146));
    ProbedList.addMouseListener(new MainFrame_ProbedList_mouseAdapter(this));
    ConnectButton.setBounds(new Rectangle(4, 38, 282, 35));
    ConnectButton.setEnabled(false);
    ConnectButton.setText("Connect");
    ConnectButton.addActionListener(new MainFrame_ConnectButton_actionAdapter(this));
    jPanel1.setBorder(BorderFactory.createLoweredBevelBorder());
    jPanel1.setBounds(new Rectangle(291, 60, 263, 220));
    jPanel1.setLayout(null);
    ConnectedList.setBorder(BorderFactory.createLoweredBevelBorder());
    ConnectedList.setBounds(new Rectangle(4, 37, 257, 206));
    ConnectedList.addMouseListener(new MainFrame_ConnectedList_mouseAdapter(this));
    jLabel1.setVerifyInputWhenFocusTarget(true);
    jLabel1.setText("Connected Devices");
    jLabel1.setBounds(new Rectangle(41, 11, 208, 19));
    lblCurrentPresent.setText("jLabel2");
    lblCurrentPresent.setBounds(new Rectangle(10, 15, 484, 25));
    mnuReadPatch.setEnabled(false);
    mnuReadPatch.setActionCommand("Read Patch");
    mnuReadPatch.setText("Read Patch");
    mnuReadPatch.addActionListener(new MainFrame_mnuReadPatch_actionAdapter(this));
    mnuTransferFiles.setEnabled(false);
    mnuTransferFiles.setText("Transfer Files");
    mnuTransferFiles.addActionListener(new MainFrame_mnuTransferFiles_actionAdapter(this));
    mnuSendIde.setEnabled(false);
    mnuSendIde.setText("Update IDE File");
    mnuSendIde.addActionListener(new MainFrame_mnuSendIde_actionAdapter(this));
    mnuReboot.setText("Reboot");
    mnuReboot.addActionListener(new MainFrame_mnuReboot_actionAdapter(this));
    jToolBar.add(OpenButton);
    jToolBar.add(NewButton);
    jToolBar.add(jButton3);
    jMenuFile.add(jMenuNewPatch);
    jMenuFile.add(mnuReadPatch);
    jMenuFile.add(jMenuOpen);
    jMenuFile.addSeparator();
    jMenuFile.add(StoreSysexMenu);
    jMenuFile.add(mnuTransferFiles);
    jMenuFile.addSeparator();
    jMenuFile.add(jMenuFileExit);
    jMenuHelp.add(jMenuHelpAbout);
    jMenuBar1.add(jMenuFile);
    jMenuBar1.add(jMenuHelp);
    jMenuBar1.add(Device);
    this.setJMenuBar(jMenuBar1);
    contentPane.add(jToolBar, BorderLayout.NORTH);
    contentPane.add(MidiOutputCombo,  BorderLayout.SOUTH);
    contentPane.add(ButtonsPannel,  BorderLayout.CENTER);
    ButtonsPannel.add(CancelButton, null);
    ButtonsPannel.add(SendProgress, null);
    ButtonsPannel.add(NetworkPanel, null);
    Device.add(mnuSaveNVRAM);
    Device.add(mnuKillPatches);
    Device.add(SendSysexmenu);
    Device.add(mnuReboot);
    Device.addSeparator();
    Device.add(mnuEraseNVRAM);
    Device.addSeparator();
    Device.add(mnuSendIde);
    NetworkPanel.add(ProbeButton, null);
    NetworkPanel.add(ConnectButton, null);
    NetworkPanel.add(ProbedList, null);
    ButtonsPannel.add(jPanel1, null);
    jPanel1.add(ConnectedList, null);
    jPanel1.add(jLabel1, null);
    ButtonsPannel.add(lblCurrentPresent, null);

    CancelButton.setVisible(false);
    SendProgress.setVisible(false);
    _sysex_sender = new SysexSender (this, 50);
  }

  private void ReadPatchFromDevice(){
    int presentation_question = _selected_interface.GetPresentation();
    int num_patches = Patch.NumberPatches(presentation_question);

    if (num_patches > 0)
    {
      int pPatch = Patch.GetPatch(presentation_question, 0);

      if (pPatch != 0)
      {
        View.AddView(presentation_question, pPatch);
        PatchForm pPatchform = new PatchForm(presentation_question, pPatch);
        pPatchform.setBounds(this.getBounds());
        pPatchform.setVisible(true);
        pPatchform.setTitle(_selected_interface.GetDescription() +  "-" + Patch.GetFileName(presentation_question, pPatch));
        pPatchform.RequestKill();
      }
    }
    else if (!PatchEditor.IsConnected(presentation_question))
    {
      System.out.println("Unable to connect to device");
    }

  }
  private void CreateNewPatch(){
    int presentation_question = _selected_interface.GetPresentation(); //PatchEditor.GetCurrentInterface();
    if (presentation_question != 0) {
      int pPatch = Patch.MakeNew(presentation_question, "NewPatch");
      if (pPatch != 0) {
        View.AddView(presentation_question, pPatch);
        PatchForm pPatchform = new PatchForm(presentation_question, pPatch);
        pPatchform.setBounds(this.getBounds());
        pPatchform.setVisible(true);
        pPatchform.setTitle(_selected_interface.GetDescription());
        pPatchform.Save();
      }
    }

  }

  public boolean StoreSysex(){
    SysexFileCreator creator = new SysexFileCreator();

    creator.pack();
    creator.setTitle(_selected_interface.GetDescription());
    creator.show();

    return true;
  }

  public void TransferFiles(){
    SysexFileCreator creator = new SysexFileCreator(_selected_interface.GetPresentation());

    creator.pack();
    creator.setTitle(_selected_interface.GetDescription());
    creator.show();

  }
  //File | Exit action performed
  public void jMenuFileExit_actionPerformed(ActionEvent e) {
    System.exit(0);
  }
  //Help | About action performed
  public void jMenuHelpAbout_actionPerformed(ActionEvent e) {
    MainFrame_AboutBox dlg = new MainFrame_AboutBox(this);
    Dimension dlgSize = dlg.getPreferredSize();
    Dimension frmSize = getSize();
    Point loc = getLocation();
    dlg.setLocation((frmSize.width - dlgSize.width) / 2 + loc.x, (frmSize.height - dlgSize.height) / 2 + loc.y);
    dlg.setModal(true);
    dlg.pack();
    dlg.show();
  }
  //Overridden so we can exit when window is closed
  protected void processWindowEvent(WindowEvent e) {
    super.processWindowEvent(e);
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      jMenuFileExit_actionPerformed(null);
    }
  }

  void jMenuNewPatch_actionPerformed(ActionEvent e) {
    CreateNewPatch();
  }

  void OpenButton_actionPerformed(ActionEvent e) {
    OpenFromFile();
  }

  void this_windowClosing(WindowEvent e) {
  }

  void jMenuOpen_actionPerformed(ActionEvent e) {
    OpenFromFile();
  }

  void NewButton_actionPerformed(ActionEvent e) {
    CreateNewPatch();
  }

  void StoreSysexMenu_actionPerformed(ActionEvent e) {
    StoreSysex();
  }

  void SendSysexmenu_actionPerformed(ActionEvent e) {
    // Get the Name of the file to save
    JFileChooser SaveDialog = new JFileChooser();
    SaveDialog.setFileFilter(new DataFileFilter());
    String init_dir = PatchEditor.GetDefaultDirectory();

    if (init_dir != null)
    {
      File f = new File (init_dir);
      SaveDialog.setCurrentDirectory(f);
    }


    int ret = SaveDialog.showOpenDialog(this);
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

      SendSysexFile (sysex_file);
    }
    else
    {
        System.out.println("Open command cancelled by user.");
    }

  }

  void CancelButton_actionPerformed(ActionEvent e) {
    StopSysexSend();
  }

  void SendSysexFile (String sysex_file){
    System.out.println("Sysex Filename: " +  sysex_file);
    File file = new File (sysex_file);
    _file_size = file.length();
    _device_num = MidiOutputCombo.getSelectedIndex();
    _file_key = PatchEditor.PrepareTxSysexFile(sysex_file);
    _bytes_sent = 0;
    _sysex_sender.Start();
    // we need to start timer here


    SendProgress.setMaximum( (int) (_file_size / _progress_multiplier));
    SendProgress.setValue(0);
    SendSysexmenu.setEnabled(false);
    mnuSaveNVRAM.setEnabled(false);
    mnuEraseNVRAM.setEnabled(false);
    SendProgress.setVisible(true);
    CancelButton.setVisible(true);

  }

  void mnuEraseNVRAM_actionPerformed(ActionEvent e) {
    if (IsSimulator())
    {
      String sysex_file = new String ("erasenvram.dat");
      int p_interface = PatchEditor.OpenSysexFile(sysex_file);
      FileSend.EraseNVRAM(p_interface);
      PatchEditor.CloseSysexFile(p_interface);

      SendSysexFile (sysex_file);
    }
    else
    {
      FileSend.EraseNVRAM(_selected_interface.GetPresentation());
    }

  }

  void mnuSaveNVRAM_actionPerformed(ActionEvent e) {

    if (IsSimulator())
    {
      String sysex_file = new String("savenvram.dat");
      int p_interface = PatchEditor.OpenSysexFile(sysex_file);
      FileSend.SaveNVRAM(p_interface);
      PatchEditor.CloseSysexFile(p_interface);

      SendSysexFile(sysex_file);
    }
    else
    {
      FileSend.SaveNVRAM(_selected_interface.GetPresentation());
    }

  }

  void mnuKillPatches_actionPerformed(ActionEvent e) {
    if (IsSimulator())
    {
      String sysex_file = new String ("savenvram.dat");
      int p_interface = PatchEditor.OpenSysexFile(sysex_file);
      Patch.Destroy(p_interface, 0);
      PatchEditor.CloseSysexFile(p_interface);
      SendSysexFile (sysex_file);
    }
    else
    {
      Patch.Destroy(_selected_interface.GetPresentation(), 0);
    }
  }

  void ProbeButton_actionPerformed(ActionEvent e) {
    ProbedListModel.clear();
    UnconnectedParams.clear();
//    ProbedList.removeAll();
    _prober.SendProbe();
  }

  void ConnectButton_actionPerformed(ActionEvent e) {
    int index = ProbedList.getSelectedIndex();
    if (index >= 0)
    {
      PresentationParam param = (PresentationParam)UnconnectedParams.elementAt(index);
      if (param.Connect())
      {
        ConnectedListModel.addElement(param.GetConnectionName());
        ConnectedParams.add((param));
        ConnectButton.setEnabled(false);
      }
    }
  }

  void ConnectedList_mouseClicked(MouseEvent e) {
    int index = ConnectedList.getSelectedIndex();
    PresentationParam p_interface = (PresentationParam)ConnectedParams.elementAt(index);
    PatchEditor.SetCurrentInterface(p_interface.GetPresentation());
    _selected_interface = p_interface;
    lblCurrentPresent.setText(_selected_interface.GetDescription());

    mnuReadPatch.setEnabled(index > 0); // allow read of anything but simulator
    mnuTransferFiles.setEnabled(index > 0);
    mnuSendIde.setEnabled(index > 0);
  }

  void ProbedList_mouseClicked(MouseEvent e) {
    int index = ProbedList.getSelectedIndex();
    if (index >= 0)
    {
      PresentationParam param = (PresentationParam)UnconnectedParams.elementAt(index);
      System.out.println(param.GetDescription());
      ConnectButton.setEnabled(CanConnect(param));

    }

  }

  void mnuReadPatch_actionPerformed(ActionEvent e) {
    ReadPatchFromDevice();
  }

  void mnuTransferFiles_actionPerformed(ActionEvent e) {
    TransferFiles();
  }


  void mnuSendIde_actionPerformed(ActionEvent e) {
    JFileChooser OpenDialog = new JFileChooser ();
     int ret = OpenDialog.showOpenDialog(MainFrame.this);
     if (ret == JFileChooser.APPROVE_OPTION)
     {
       File file = OpenDialog.getSelectedFile();
       String filename = file.getName();
       String filepath = OpenDialog.getCurrentDirectory().getAbsolutePath() + file.separatorChar;
       System.out.println("Path: " + filepath + filename );

       Patch.Destroy(_selected_interface.GetPresentation(), 0);
       FileSend.SendFile(_selected_interface.GetPresentation(), filename, filepath + filename);
       FileSend.SaveToIde(_selected_interface.GetPresentation(), filename, filepath + filename);

     }

  }

  void mnuReboot_actionPerformed(ActionEvent e) {
    _prober.SendReboot(_selected_interface._address);
  }


}

class MainFrame_jMenuFileExit_ActionAdapter implements ActionListener {
  MainFrame adaptee;

  MainFrame_jMenuFileExit_ActionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuFileExit_actionPerformed(e);
  }
}

class MainFrame_jMenuHelpAbout_ActionAdapter implements ActionListener {
  MainFrame adaptee;

  MainFrame_jMenuHelpAbout_ActionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuHelpAbout_actionPerformed(e);
  }
}

class MainFrame_jMenuNewPatch_ActionAdapter implements ActionListener {
  MainFrame adaptee;

  MainFrame_jMenuNewPatch_ActionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuNewPatch_actionPerformed(e);
  }
}

class MainFrame_OpenButton_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_OpenButton_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.OpenButton_actionPerformed(e);
  }
}

class MainFrame_this_windowAdapter extends java.awt.event.WindowAdapter {
  MainFrame adaptee;

  MainFrame_this_windowAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void windowClosing(WindowEvent e) {
    adaptee.this_windowClosing(e);
  }
}

class MainFrame_jMenuOpen_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jMenuOpen_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuOpen_actionPerformed(e);
  }
}

class MainFrame_NewButton_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_NewButton_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.NewButton_actionPerformed(e);
  }
}

class MainFrame_StoreSysexMenu_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_StoreSysexMenu_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.StoreSysexMenu_actionPerformed(e);
  }
}

class MainFrame_SendSysexmenu_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_SendSysexmenu_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.SendSysexmenu_actionPerformed(e);
  }
}

class SysexSender implements ActionListener {
    javax.swing.Timer timer;
    MainFrame _parent;

    /**
       @roseuid 3EB1ED750021
     */
    SysexSender(MainFrame parent, int time) {
    timer = new javax.swing.Timer(time, this);
    _parent = parent;
    }

    /**
       @roseuid 3EB1ED750024
     */
    public void actionPerformed(ActionEvent e) {
      //Advance the animation frame.
        _parent.TransmitBytes();
    }

    /**
       @roseuid 3EB1ED750026
     */
    public synchronized void Start() {
    if (!timer.isRunning())
    {
      timer.start();
    }
    }

    /**
       @roseuid 3EB1ED750027
     */
    public synchronized void Stop() {
    if (timer.isRunning())
    {
      timer.stop();
    }

    }
}

class MainFrame_CancelButton_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_CancelButton_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.CancelButton_actionPerformed(e);
  }
}

class MainFrame_mnuEraseNVRAM_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_mnuEraseNVRAM_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuEraseNVRAM_actionPerformed(e);
  }
}

class MainFrame_mnuSaveNVRAM_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_mnuSaveNVRAM_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuSaveNVRAM_actionPerformed(e);
  }
}

class MainFrame_mnuKillPatches_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_mnuKillPatches_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuKillPatches_actionPerformed(e);
  }
}

class MainFrame_ProbeButton_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_ProbeButton_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.ProbeButton_actionPerformed(e);
  }
}

class MainFrame_ConnectButton_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_ConnectButton_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.ConnectButton_actionPerformed(e);
  }
}

class MainFrame_ConnectedList_mouseAdapter extends java.awt.event.MouseAdapter {
  MainFrame adaptee;

  MainFrame_ConnectedList_mouseAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
    adaptee.ConnectedList_mouseClicked(e);
  }
}

class MainFrame_ProbedList_mouseAdapter extends java.awt.event.MouseAdapter {
  MainFrame adaptee;

  MainFrame_ProbedList_mouseAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
    adaptee.ProbedList_mouseClicked(e);
  }
}

class MainFrame_mnuReadPatch_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_mnuReadPatch_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuReadPatch_actionPerformed(e);
  }
}

class MainFrame_mnuTransferFiles_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_mnuTransferFiles_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuTransferFiles_actionPerformed(e);
  }
}

class MainFrame_mnuSendIde_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_mnuSendIde_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuSendIde_actionPerformed(e);
  }
}

class MainFrame_mnuReboot_actionAdapter implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_mnuReboot_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.mnuReboot_actionPerformed(e);
  }
}
