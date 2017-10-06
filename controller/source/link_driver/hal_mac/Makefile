	# makefile for Mac MIDI Deriver library 

.SUFFIXES : .cpp .o

LIBNAME=sm_COMM.a
LIB=$(LIBNAME)

CC_PIECES = maccommstream

CC_FILES = $(CC_PIECES:%=%.cpp)
CC_O_FILES = $(CC_PIECES:%=%.o)


DEFINES  += -D_E_STL 
CPPFLAGS += -I ../../../../estl 
CPPFLAGS += -I ./ 
CPPFLAGS += -I ../ 
CPPFLAGS += -I ../../hal_include
CPPFLAGS += -I ../../engine
CPPFLAGS += -I ../../engineinterface
CPPFLAGS += $(DEFINES)

all: $(LIB) $(CC_O_FILES) 

lib :$(LIB)

.cpp.o :
	cc $(CPPFLAGS) -c $<



$(LIB) : $(CC_O_FILES)
	ar -r -s  $@ $?


clean:
	rm *.a
	rm *.o
	rm $(TEST_EXE)