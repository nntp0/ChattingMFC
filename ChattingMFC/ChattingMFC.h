
// ChattingMFC.h : main header file for the ChattingMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CChattingMFCApp:
// See ChattingMFC.cpp for the implementation of this class
//

class CChattingMFCApp : public CWinApp
{
public:
	CChattingMFCApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChattingMFCApp theApp;
