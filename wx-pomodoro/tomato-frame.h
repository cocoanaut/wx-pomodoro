#pragma once

#include "stdafx.h"

class TomatoFrame : public wxFrame
{
public:

    TomatoFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};
