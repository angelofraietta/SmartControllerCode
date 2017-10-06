#
#  $Id: Makefile,v 1.20 2003/04/28 05:27:53 angelofraietta Exp $
#
# Templates/Makefile.leaf
# 	Template leaf node Makefile
#

EXEC=smart.exe
# C source names, if any, go here -- minus the .c
C_PIECES=diags fsmount bsp-cs8900 cs8900 init
C_FILES=$(C_PIECES:%=%.c)
C_O_FILES=$(C_PIECES:%=${ARCH}/%.o)

# C++ source names, if any, go here -- minus the .cc
CC_PIECES=rtems_init \
  midioutput \
  scheduler \
	rtems_simulator \
	commtasks	

CC_FILES=$(CC_PIECES:%=%.cpp)
CC_O_FILES=$(CC_PIECES:%=${ARCH}/%.o)

H_FILES= 

# Assembly source names, if any, go here -- minus the .S
S_PIECES=
S_FILES=$(S_PIECES:%=%.S)
S_O_FILES=$(S_FILES:%.S=${ARCH}/%.o)

SRCS=$(C_FILES) $(CC_FILES) $(H_FILES) $(S_FILES)
OBJS=$(C_O_FILES) $(CC_O_FILES) $(S_O_FILES)

PGMS=${ARCH}/$(EXEC) #${ARCH}/xxx-another-one

# List of RTEMS managers to be included in the application goes here.
# Use:
#     MANAGERS=all
# to include all RTEMS managers in the application.
MANAGERS=io event message rate_monotonic semaphore timer

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc

include $(RTEMS_CUSTOM)
include $(RTEMS_ROOT)/make/leaf.cfg

#
# (OPTIONAL) Add local stuff here using +=
#

DEFINES  += -D_E_STL 
CPPFLAGS += -I ../../../estl 
CPPFLAGS += -I ../engine
CPPFLAGS += -I ../engineinterface
CPPFLAGS += -I ../hal_include
CPPFLAGS += -I ../link_driver
CPPFLAGS += -I ../../../threads/source
CPPFLAGS += -I ../../../mididriver
CPPFLAGS += -I ../../../mididriver/hal_rtems

XCPPFLAGS +=
CFLAGS   +=

#
# CFLAGS_DEBUG_V are used when the `make debug' target is built.
# To link your application with the non-optimized RTEMS routines,
# uncomment the following line:
# CFLAGS_DEBUG_V += -qrtems_debug
#

LD_PATHS  +=  #xxx-your-EXTRA-library-paths-go-here, if any

LD_LIBS   +=  ../engine/$(ARCH)/sm_engine.a  
LD_LIBS   +=  ../engineinterface/$(ARCH)/sm_engineinterface.a  
LD_LIBS   +=  ../engine/$(ARCH)/sm_engine.a  
LD_LIBS   +=  ../link_driver/$(ARCH)/sm_link_driver.a  
LD_LIBS   +=  ../link_driver/hal_rtems/$(ARCH)/sm_comm.a  
LD_LIBS   +=  ../../../threads/source/$(ARCH)/sm_rtems_active.a  
LD_LIBS   +=  ../../../threads/source/hal_rtems/$(ARCH)/sm_rtems_thread.a  
LD_LIBS   +=  ../../../mididriver/hal_rtems/$(ARCH)/rtems_midi.a
LD_LIBS   +=  ../../../libOSC/$(ARCH)/libosc.a
# Add the following code when attempting to strip down in size
#LDFLAGS   += -Wl,'-gc-sections'

#
# Add your list of files to delete here.  The config files
#  already know how to delete some stuff, so you may want
#  to just run 'make clean' first to see what gets missed.
#  'make clobber' already includes 'make clean'
#

CLEAN_ADDITIONS += 
CLOBBER_ADDITIONS +=

all:	${ARCH} $(SRCS) $(PGMS)

${ARCH}/$(EXEC): ${OBJS} ${LINK_FILES}
	$(make-cxx-exe)

# Install the program(s), appending _g or _p as appropriate.
# for include files, just use $(INSTALL_CHANGE)
install:  all
	$(INSTALL_VARIANT) -m 555 ${PGMS} ${PROJECT_RELEASE}/bin

