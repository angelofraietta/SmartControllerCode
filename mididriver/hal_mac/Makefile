	# makefile for Mac MIDI Deriver library 

.SUFFIXES : .cpp .o

LIBNAME=sm_MIDI.a
TESTNAME=test.exe
DEMONAME=echo.exe
LIB=$(LIBNAME)
TEST_EXE=$(TESTNAME)

CC_PIECES = macmidiinputdriver macmidioutputdriver

CC_FILES = $(CC_PIECES:%=%.cpp)
CC_O_FILES = $(CC_PIECES:%=%.o)

LINK_FLAGS = $(LIB)
LINK_FLAGS += ../../threads/source/hal_mac/sm_thread.a

DEFINES  += -D_E_STL 
CPP_FLAGS += -I ../../estl 
CPP_FLAGS += -I ../ 
CPP_FLAGS += -I ../../threads/source
CPP_FLAGS += $(DEFINES)
FRAMEWORKS += -framework CoreMidi -framework CoreServices

all: $(LIB) $(CC_O_FILES) $(TEST_EXE)

lib :$(LIB)

.cpp.o :
	cc $(CPP_FLAGS) -c $<



$(LIB) : $(CC_O_FILES)
	ar -r -s  $@ $?

$(TEST_EXE) : $(LIB) testmid.o
	g++  testmid.o -o $(TEST_EXE) $(LINK_FLAGS) $(FRAMEWORKS) 

$(DEMONAME) : echo.o
	g++ echo.o -o $(DEMONAME) $(FRAMEWORKS) 

demo : $(DEMONAME) 

clean:
	rm *.a
	rm *.o
	rm $(TEST_EXE)
