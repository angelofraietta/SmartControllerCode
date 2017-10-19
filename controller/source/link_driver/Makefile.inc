#
#  $
#
# Makefile for engineinterface library
#       
#

LIBNAME=sm_link_driver.a        # xxx- your library names goes here
TESTNAME=UDPTest

# C and C++ source names, if any, go here -- minus the .c or .cc
C_PIECES=
CC_PIECES= linkprotocol \
	linklayer \
	crc32 \
	udpport \
	networklayer


COMMON_DEFINES  = -D_E_STL 
COMMON_CPPFLAGS = -I ../../../estl 
COMMON_CPPFLAGS += -I ./ 
COMMON_CPPFLAGS += -I ../hal_include
COMMON_CPPFLAGS += -I ../engine
COMMON_CPPFLAGS += -I ../engineinterface



























