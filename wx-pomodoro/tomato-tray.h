#pragma once

#include "stdafx.h"

enum
{
  TIMER_ID = 10001,
  PU_START_PAUSE = 10002,
  PU_RESET = 10003,
  PU_EXIT
};

class TomatoTray : public wxTaskBarIcon
{
public:
#if defined(__WXOSX__) && wxOSX_USE_COCOA
  TomatoTray(wxTaskBarIconType iconType = wxTBI_DEFAULT_TYPE, wxApp *app) : wxTaskBarIcon(iconType)
#else
  TomatoTray(wxApp *app) : timer_(this, TIMER_ID)
#endif
  {
    app_ = app;
    Reset();
  }
  virtual wxMenu *CreatePopupMenu();
  void OnMenuStartPause(wxCommandEvent&);
  void OnMenuReset(wxCommandEvent&);
  void OnMenuExit(wxCommandEvent&);
  void TomatoTray::OnTimer(wxTimerEvent& event);
private:
  static const int timer_seconds_ = 1500; // 25 minutes
  wxApp* app_;
  wxTimer timer_;
  int elapsed_seconds_;
  void Reset();
  void Update();
  wxDECLARE_EVENT_TABLE();
};
