
// ChattingClient.h : main header file for the ChattingClient application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CChattingClientApp:
// See ChattingClient.cpp for the implementation of this class
//

class CChattingClientApp : public CWinApp
{
public:
	CChattingClientApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChattingClientApp theApp;
