#makefile for building PatcheEditor JNI
.SUFFIXES : .cpp .o .java .class

LIB=patcheditorinterface.a
#define path fror JNI
JNI_INCLUDE = -I/System/Library/Frameworks/JavaVM.framework/Headers

SOURCE_PIECES = BaseShell \
  Connector \
  Identity \
  PatchEditor \
  Patch \
  View \
  FileSend

J_SOURCES = Application1.class Frame1.class TestLoad.class

CPP_O_FILES = $(SOURCE_PIECES:%=%Interface.o)
JNI_CLASSES = $(SOURCE_PIECES:%=Jni/%.class)


COMMON_DEFINES  = -D_E_STL 
COMMON_CPPFLAGS += -I ../../../../estl 
COMMON_CPPFLAGS += -I ../ 
COMMON_CPPFLAGS += -I ../../hal_include
COMMON_CPPFLAGS += -I ../../link_driver
COMMON_CPPFLAGS += -I ../../engine
COMMON_CPPFLAGS += -I ../../../../threads/source
COMMON_CPPFLAGS += -I ../../../../mididriver

LINK_LIBS = ../../hal_mac/smart.a

all : $(CPP_O_FILES) $(JNI_CLASSES) $(LIB) $(J_SOURCES) 

java : $(JNI_CLASSES) $(J_SOURCES)

$(LIB) : $(CPP_O_FILES)
		ar -r -s  $@ $?

clean:
	-rm *.o
	-rm *.a
	-rm *.class

.cpp.o :
	cc $(JNI_INCLUDE) $(COMMON_DEFINES) $(COMMON_CPPFLAGS) -c $<

.java.class :
	javac  $<
