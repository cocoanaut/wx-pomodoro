
#include "stdafx.h"
#include "tomato-tray.h"

#include "tomato.xpm"

class TomatoApp : public wxApp 
{
public:
    TomatoTray *tray_;
    virtual bool OnInit(); 
}; 

wxIMPLEMENT_APP(TomatoApp);

bool TomatoApp::OnInit()
{
  // TODO: should I be checking this first?
  // const bool isTray = wxTaskBarIcon::IsAvailable();
  
  tray_ = new TomatoTray(this);
  wxIcon icon(tomato_xpm);
  tray_->SetIcon(icon, "Right click and choose Start to begin.");

  // TomatoFrame *frame = new TomatoFrame();
  // frame->Show(true);

  return true;
}
