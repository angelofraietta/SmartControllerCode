##
##  $Id: Makefile,v 1.4 2003/04/15 01:11:54 angelofraietta Exp $
##
#
#  $Id: Makefile,v 1.4 2003/04/15 01:11:54 angelofraietta Exp $
#
# Templates/Makefile.leaf
# 	Template leaf node Makefile
#

EXEC=threads.exe
# C source names, if any, go here -- minus the .c
C_PIECES= tasks
C_FILES=$(C_PIECES:%=%.c)
C_O_FILES=$(C_PIECES:%=${ARCH}/%.o)

# C++ source names, if any, go here -- minus the .cc
CC_PIECES = activethreads

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
MANAGERS=all

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc

include $(RTEMS_CUSTOM)
include $(RTEMS_ROOT)/make/leaf.cfg

#
# (OPTIONAL) Add local stuff here using +=
#

#
# CFLAGS_DEBUG_V are used when the `make debug' target is built.
# To link your application with the non-optimized RTEMS routines,
# uncomment the following line:
# CFLAGS_DEBUG_V += -qrtems_debug
#

CPPFLAGS += -I ../
CPPFLAGS += -I ../hal_rtems

LD_PATHS  +=  #xxx-your-EXTRA-library-paths-go-here, if any

LD_LIBS   +=  ../$(ARCH)/sm_rtems_active.a  
LD_LIBS   +=  ../hal_rtems/$(ARCH)/sm_rtems_thread.a  
#LD_LIBS   += -lstdc++ -v


LDFLAGS   +=

#
# Add your list of files to delete here.  The config files
#  already know how to delete some stuff, so you may want
#  to just run 'make clean' first to see what gets missed.
#  'make clobber' already includes 'make clean'
#

CLEAN_ADDITIONS += #xxx-your-debris-goes-here
CLOBBER_ADDITIONS +=

all:	${ARCH} $(SRCS) $(PGMS)

${ARCH}/$(EXEC): ${OBJS} ${LINK_FILES}
	$(make-cxx-exe)

# Install the program(s), appending _g or _p as appropriate.
# for include files, just use $(INSTALL_CHANGE)
install:  all
	$(INSTALL_VARIANT) -m 555 ${PGMS} ${PROJECT_RELEASE}/bin




