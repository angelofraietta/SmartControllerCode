	# makefile for Mac thread library 

.SUFFIXES : .cpp .o

LIBNAME=sm_thread.a
TESTNAME=test.exe
LIB=$(LIBNAME)
TEST_EXE=$(TESTNAME)

CC_PIECES = macthread macevent macmutex
#threadslib
CC_FILES = $(CC_PIECES:%=%.cpp)
CC_O_FILES = $(CC_PIECES:%=%.o)
CC_O_FILES += activeobject.o

LINK_FLAGS = $(LIB)
CPP_FLAGS += -I../

all: $(LIB) $(CC_O_FILES) $(TEST_EXE)

lib :$(LIB)
activeobject.o : ../activeobject.cpp
	cc $(CPP_FLAGS) -Ihal_mac -c ../activeobject.cpp

.cpp.o :
	cc $(CPP_FLAGS) -c $<



$(LIB) : $(CC_O_FILES)
	ar -r -s  $@ $?

$(TEST_EXE) : $(LIB) activethreads.o
	g++  activethreads.o -o $(TEST_EXE) $(LINK_FLAGS)

clean:
	-rm *.a
	-rm *.o
	-rm $(TEST_EXE)