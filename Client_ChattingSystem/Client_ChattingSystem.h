
// Client_ChattingSystem.h: Client_ChattingSystem 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CClientChattingSystemApp:
// 이 클래스의 구현에 대해서는 Client_ChattingSystem.cpp을(를) 참조하세요.
//

class CClientChattingSystemApp : public CWinApp
{
public:
	CClientChattingSystemApp() noexcept;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	DECLARE_MESSAGE_MAP()
};
extern CClientChattingSystemApp theApp;
