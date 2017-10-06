#
#  $
#
# Makefile for engineinterface library
#       
#

LIBNAME=sm_engineinterface.a        # xxx- your library names goes here
SIMLIBNAME = sm_question.a
C_PIECES=

CC_PIECES= smutility \
 eventmessagequeue \
 baseshellquestion \
 connectorquestion \
 patchquestion \
 identityquestion \
 sessionquestion \
 presentationquestion \
 eventquestion \
 baseshellanswer \
 connectoranswer \
 patchanswer \
 identityanswer \
 sessionanswer \
 presentationanswer \
 eventanswer \
 fileanswer \
 answertask \
 sysexfilequestion \
 viewanswer \
 fileblock \
 nvramstore

CC_SIM_PIECES = baseshellquestion \
 connectorquestion \
 eventquestion \
 filequestion \
 identityquestion \
 patchquestion \
 presentationquestion \
 questiontask\
 sessionquestion \
 smutility \
 sysexfilequestion \
 viewquestion 


COMMON_DEFINES  = -D_E_STL 
COMMON_CPPFLAGS += -I ../../../estl 
COMMON_CPPFLAGS += -I ./ 
COMMON_CPPFLAGS += -I ../hal_include
COMMON_CPPFLAGS += -I ../link_driver
COMMON_CPPFLAGS += -I ../engine
COMMON_CPPFLAGS += -I ../../../threads/source
COMMON_CPPFLAGS += -I ../../../mididriver



























