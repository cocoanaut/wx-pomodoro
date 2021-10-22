#include "stdafx.h"
#include "tomato-tray.h"

#include "tomato.xpm"

wxBEGIN_EVENT_TABLE(TomatoTray, wxTaskBarIcon)
  EVT_MENU(PU_START_PAUSE, TomatoTray::OnMenuStartPause)
  EVT_MENU(PU_RESET,TomatoTray::OnMenuReset)
  EVT_MENU(PU_EXIT, TomatoTray::OnMenuExit)
  EVT_TIMER(TIMER_ID, TomatoTray::OnTimer)
wxEND_EVENT_TABLE()

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
    SetIcon(tomato_xpm, wxString::Format("%s %2i:%02i", (timer_.IsRunning() ? "Running" : "Stopped"), remaining / 60, remaining % 60));
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
