#ifndef WINDOWS_MESSAGES_H
#define WINDOWS_MESSAGES_H
//define windows messages here
class CWindowMessage
{
 public:
  CWindowMessage (UINT32 message, UINT32 lParam, UINT32 wParam)
    :_message (message), _lParam(lParam),_wParam(wParam) {}
  static UINT8 Size (){return sizeof(CWindowMessage);}
  const UINT32 _message;
  const UINT32 _lParam;
  const UINT32 _wParam;
};

// 
#ifndef WM_USER
#define WM_USER 0
#endif

#define DISPLAY_DELETED   (WM_USER + 1)
#define DISPLAY_MESSAGE   (WM_USER + 2)
#define ERROR_MESSAGE     (WM_USER + 3)
#define ERROR_MESSAGE_32  (WM_USER + 4)
#define TRIGGER_MESSAGE   (WM_USER + 5)
#define TRIGGER_DELETED   (WM_USER + 6)
#define WAVE_OPEN         (WM_USER + 7)
#define WAVE_CLOSE        (WM_USER + 8)
#define WAVE_PLAY         (WM_USER + 9)
#define WAVE_STOP         (WM_USER + 10)
#define WAVE_PAUSE        (WM_USER + 11)
#define WAVE_RESUME       (WM_USER + 12)
#define WAVE_CREATE       (WM_USER + 13)
#define WAVE_DESTROY      (WM_USER + 14)
#define WAVE_SET_DEVICE   (WM_USER + 15)
#define WAVE_RESET_DEVICE (WM_USER + 16)
#define WAVE_UPDATE_DISPLAY (WM_USER + 17)
#define NEW_FILE_OPEN      (WM_USER + 18)
#define AUDIO_CONTROL_PLAY  (WM_USER + 19)
#define AUDIO_CONTROL_STOP  (WM_USER + 20)
#define AUDIO_CONTROL_CREATE (WM_USER + 21)
#define AUDIO_CONTROL_DESTROY (WM_USER + 22)
#define AUDIO_CONTROL_DISPLAY_DELETED (WM_USER + 23)
#define AUDIO_CONTROL_DISPLAY_UPDATE (WM_USER + 24)
#define APPLICATION_OPEN_FILE (WM_USER + 25)
#endif








