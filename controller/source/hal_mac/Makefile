#
#  $Id: Makefile,v 1.10 2003/03/14 00:26:43 angelofraietta Exp $
#
# Templates/Makefile.leaf
# 	Template leaf node Makefile
#


JAVLIB=libsmartcontroljava.jnilib
TEST_EXE=smart.exe


# C++ source names, if any, go here -- minus the .cc
CC_PIECES=  scheduler \
 ../hal_include/simulator	

CC_JPIECES =  ../engineinterface/PatchEditorInterface/PatchEditorInterface \
  ../engineinterface/PatchEditorInterface/BaseShellInterface \
  ../engineinterface/PatchEditorInterface/FileSendInterface \
  ../engineinterface/PatchEditorInterface/ConnectorInterface \
  ../engineinterface/PatchEditorInterface/IdentityInterface \
  ../engineinterface/PatchEditorInterface/PatchInterface \
  ../engineinterface/PatchEditorInterface/ViewInterface \
 
CC_SIM_PIECES=testsim

CC_FILES = $(CC_PIECES:%=%.cpp)
CC_O_FILES = $(CC_PIECES:%=%.o)
CJ_O_FILES = $(CC_JPIECES:%=%.o)
CC_SIM_O_FILES = $(CC_SIM_PIECES:%=%.o)	

DEFINES  += -D_E_STL 
CPPFLAGS += -I ../../../estl 
CPPFLAGS += -I ../engine
CPPFLAGS += -I ../engineinterface
CPPFLAGS += -I ../hal_include
CPPFLAGS += -I ../link_driver
CPPFLAGS += -I ../../../threads/source
CPPFLAGS += -I ../../../mididriver
CPPFLAGS += -I ../../../mididriver/hal_rtems

CPPFLAGS += $(DEFINES)
CPPFLAGS += -I/System/Library/Frameworks/JavaVM.framework/Headers

FRAMEWORKS += -framework CoreMidi -framework CoreServices -framework AudioToolbox
J_FRAMEWORKS = -framework JavaVM

LD_LIBS   +=  ../engine/sm_engine.a  
LD_LIBS   +=  ../engineinterface/sm_engineinterface.a  
LD_LIBS   +=  ../link_driver/sm_link_driver.a  
LD_LIBS   +=  ../link_driver/hal_mac/sm_comm.a  
LD_LIBS   +=  ../../../threads/source/hal_mac/sm_thread.a  
LD_LIBS   +=  ../../../mididriver/hal_mac/sm_MIDI.a
LD_LIBS   +=  ../../../libOSC/libosc.a
LD_LIBS   +=  ../engineinterface/sm_question.a  
#LD_LIBS   += -lstdc++ -v

J_LIBS   =  ../engineinterface/PatchEditorInterface/patcheditorinterface.a


all: $(CC_O_FILES) $(CJ_O_FILES) $(CC_SIM_O_FILES) $(JAVLIB) $(TEST_EXE)

sim: $(TEST_EXE)
	
clean:
	-rm *.o
	-rm *.jnilib


install:
	cp $(JAVLIB) ../../../JSmartcontroller
	#cp $(JAVLIB) /Users/angelofraietta/Desktop/MacSmartcontrollerFolder/


.cpp.o :
	cc $(CPPFLAGS) -c $<


$(JAVLIB) : $(CJ_O_FILES) $(CC_O_FILES) $(LD_LIBS)
	echo MAKEJAVA
	g++ -dynamiclib -o $(JAVLIB) $(CJ_O_FILES)  $(J_LIBS) $(CC_O_FILES) $(LD_LIBS) $(FRAMEWORKS) $(J_FRAMEWORKS)

$(TEST_EXE) : $(CC_SIM_O_FILES) $(CC_O_FILES) $(LD_LIBS) 
	echo MakeSim
	g++  -o $(TEST_EXE) $(CC_SIM_O_FILES) $(CC_O_FILES) $(LD_LIBS) $(FRAMEWORKS)




