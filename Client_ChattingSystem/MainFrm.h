
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "ChildView.h"
#include "Transmission.h"

#include "iMainFrame.h"

class CMainFrame : public CFrameWnd, public iMainFrame
{
	// Constructor / Destructor
public:
	CMainFrame() noexcept;
	virtual ~CMainFrame();
protected: 
	
// 특성입니다.
public:
	iTransmission *m_transmission = nullptr;
// 작업입니다.
public:

	// Method Override
public:
	// CFrameWnd
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// iMainFrame
	virtual void Tick();
	virtual void ControlMessage(CString str);
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


