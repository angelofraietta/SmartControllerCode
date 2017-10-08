import Jni.*;

class MidiExe {

		public static void main(String[] args) {
				System.out.println ("MidiExe");
				String source_file = new String (args [0]);
				String dat_file = new String (args [1]);

				System.out.println (source_file);
				System.out.println (dat_file);

				int pinterface = PatchEditor.OpenSysexFile(dat_file);

				Patch.Destroy(pinterface, 0);
        FileSend.SendFile(pinterface, source_file, source_file);
        FileSend.SaveToIde(pinterface, source_file, source_file);
				PatchEditor.CloseSysexFile(pinterface);
		}
}
