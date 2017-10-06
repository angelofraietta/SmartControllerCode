#
#  $
#
# Makefile for Pointer STL Library
#       
#

LIBNAME=libosc.a        # xxx- your library names goes here

# C and C++ source names, if any, go here -- minus the .c or .cc
C_PIECES=OSC-client OSC-timetag htmsocket

CC_PIECES= 


H_FILES=

COMMON_DEFINES = -D_E_STL 
COMMON_DEFINES += -D_DO_STREAM

COMMON_CPPFLAGS = -I ../../../estl 

COMMON_CPPFLAGS += -I ./ 
COMMON_CPPFLAGS += -I ../hal_include
COMMON_CPPFLAGS += -I ../engineinterface
COMMON_CPPFLAGS += -I ../link_driver
COMMON_CPPFLAGS += -I ../../../threads/source
COMMON_CPPFLAGS += -I ../../../mididriver























