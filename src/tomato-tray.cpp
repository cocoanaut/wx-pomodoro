#include "stdafx.h"
#include "tomato-tray.h"

#include "tomato.xpm"

#if defined(__WXOSX__) && wxOSX_USE_COCOA
TomatoTray::TomatoTray(wxTaskBarIconType iconType, wxApp *app) : wxTaskBarIcon(iconType)
#else
TomatoTray::TomatoTray(wxApp *app) : timer_(this, TIMER_ID)
#endif
{
  app_ = app;
  Reset();

  // Bind events using the modern Connect/Bind method
  Bind(wxEVT_MENU, &TomatoTray::OnMenuStartPause, this, PU_START_PAUSE);
  Bind(wxEVT_MENU, &TomatoTray::OnMenuReset, this, PU_RESET);
  Bind(wxEVT_MENU, &TomatoTray::OnMenuExit, this, PU_EXIT);
  Bind(wxEVT_TIMER, &TomatoTray::OnTimer, this, TIMER_ID);
}

wxMenu *TomatoTray::CreatePopupMenu()
{
  wxMenu *menu = new wxMenu;
  menu->Append(PU_START_PAUSE, wxT("&Start / Pause"));
  menu->AppendSeparator();
  menu->Append(PU_RESET, wxT("&Reset"));
  /* OSX has built-in quit menu for the dock menu, but not for the status item */
#ifdef __WXOSX__ 
  if ( OSXIsStatusItem() )
#endif
  {
    menu->AppendSeparator();
    menu->Append(PU_EXIT, wxT("E&xit"));
  }
  return menu;
}

void TomatoTray::Reset()
{
  timer_.Stop();
  elapsed_seconds_ = 0;
}

void TomatoTray::Update()
{

  if(!timer_.IsRunning() && elapsed_seconds_ == 0) {
    SetIcon(tomato_xpm, "Right click and choose Start to begin.");
    return;
  }

  int remaining = (timer_seconds_ - elapsed_seconds_);
  if(remaining <= 0) {
    Reset();
    wxMessageBox(wxT("Timer Complete"),wxT("Tomato Timer"));
    SetIcon(tomato_xpm, "Timer Complete.");
  } else {
    int remainingMinutes = remaining / 60;
    int remainingSeconds = remaining % 60;
    wxString label = wxString::Format("%s %2i:%02i", (timer_.IsRunning() ? wxT("Running") : wxT("Stopped")), remainingMinutes, remainingSeconds);
    SetIcon(tomato_xpm, label);
  }
}

void TomatoTray::OnTimer(wxTimerEvent& event)
{
  elapsed_seconds_++;
  Update();
}

void TomatoTray::OnMenuStartPause(wxCommandEvent& )
{
  if(timer_.IsRunning())
    timer_.Stop();
  else
    timer_.Start(1000); // 1 second interval
  Update();
}

void TomatoTray::OnMenuReset(wxCommandEvent& )
{
  Reset();
  Update();
}

void TomatoTray::OnMenuExit(wxCommandEvent& )
{
  app_->GetTopWindow()->Close(true);
}
