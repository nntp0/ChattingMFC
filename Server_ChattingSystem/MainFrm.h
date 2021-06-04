
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "ChildView.h"

#include "iServer.h"

#include "Processor.h"

#include <memory>

class CMainFrame : public CFrameWnd, public iServer
{
	// Constructor / Destructor
public:
	CMainFrame() noexcept;
	virtual ~CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 구현입니다.
public:	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CChildView    m_wndView;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();


// iServer
	
	// methods
public:
	std::shared_ptr<Processor> FindIdleProcessor();

	// method override
public:
	// iServer.h
	virtual void Tick();
	virtual void Connect(UID);
	virtual void Disconnect(UID);
	virtual void RecvMessage(std::string msg);

	virtual void Run();

	// properties
private:
	std::shared_ptr<iTransmissionServer> transmission;

	iDisplayModule* displayModule = nullptr;
	std::shared_ptr<iDataModule> dataModule;

	std::shared_ptr<Processor> processor;
};


