
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "ChildView.h"

#include "iApplication.h"
#include "iTransmission.h"
#include "Processor.h"

class CMainFrame : public CFrameWnd, public iApplication
{
	// Constructor / Destructor
public:
	CMainFrame() noexcept;
	virtual ~CMainFrame();
protected: 
	
	// Modules
public:
	iTransmission *m_transmission = nullptr;
	Processor processor;

	// Method Override
public:
	// CFrameWnd
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// iApplication
	virtual void Tick();
	virtual void RecvMessage(std::string str);

	// 구현입니다.
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CChildView    m_wndView;
	DECLARE_DYNAMIC(CMainFrame)

	// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
};


