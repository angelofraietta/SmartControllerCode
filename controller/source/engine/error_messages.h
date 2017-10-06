
#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

enum error_message_type
{
  eDivideByZero,
  eInternalError,
	eInvalidIndex,
  eCounterError,
  eDelayError,
  eNumberStoreError,
  eOutletThreadLocked,
  ePatchAncestorError,
  eUnableToOpenPatch,
  eInvalidPatchFile,
  ePatchRestoreError,
  ePatchRestoreConnection,
  eInvalidTempo,
  eUnableToOpenSequence,
  eInvalidStatus,
  eInvalidChannel,
  eInvalidDataValue,
  eInvalidDevice,
  eSendMidiError,
  eInvalidSwitchContacts,
  eInvalidTableSize,
  eTableExceeded,
  eTableStoreError,
  eInvalidTableIndex,
  eUnableToOpenTable,
  eTimerError
};

#endif
