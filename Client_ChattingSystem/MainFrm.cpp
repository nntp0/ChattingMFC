#pragma once
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include "MainFrm.h"

#include "locale.h"

#include "iTransmission.h"
#include "AMQPClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMainFrame Constructor / Destructor
// Dependency Injection About iTransmission
CMainFrame::CMainFrame() noexcept
	: m_transmission(new AMQPClient())
{
	m_transmission->SetApplication(this);
}
CMainFrame::~CMainFrame()
{
	delete m_transmission;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}

	return 0;
}
// Window Style
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_POPUP;
	if (cs.hMenu != NULL) {
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}

	cs.x = 100;
	cs.y = 100;
	cs.cy = 600;
	cs.cx = 440;

	cs.dwExStyle &= ~(WS_EX_CLIENTEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame 메시지 처리기
void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
void CMainFrame::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	AfxMessageBox(_T("Bye"));
	this->m_transmission->Close();
	CFrameWnd::OnClose();
}

// Custom Methods
void CMainFrame::Tick() {
	AfxMessageBox(_T("Tick"));
}
void CMainFrame::RecvMessage(std::string str) {
	TRACE(_T("ControlMessage"));

	std::string buf = str.substr(0, 4);
	str = str.substr(4);
	
	if (buf == "clcr") {
		std::string buf = str.substr(0, 2);
		str = str.substr(2);
		int len = stoi(buf);

		std::string uName = str.substr(0, len);
		str = str.substr(len);

		buf = str.substr(0, 2);
		str = str.substr(2);
		len = stoi(buf);

		std::string rName = str.substr(0, len);
		str = str.substr(len);

		m_wndView.UpdateUserInfo(uName, rName);

		this->m_transmission->Send("rmls");
	}
	else if (buf == "clls") {
		std::string buf = "미구현";
	}
	else if (buf == "rmcr") {
		this->m_transmission->Send("rmls");
	}
	else if (buf == "rmlv") {
		std::string buf = "미구현";
	}
	else if (buf == "rmjn") {
		std::string buf = str.substr(0, 2);
		str = str.substr(2);
		int len = stoi(buf);

		std::string uName = str.substr(0, len);
		str = str.substr(len);

		buf = str.substr(0, 2);
		str = str.substr(2);
		len = stoi(buf);

		std::string rName = str.substr(0, len);
		str = str.substr(len);

		m_wndView.UpdateUserInfo(uName, rName);
		m_wndView.JoinRoom();
	}
	else if (buf == "rmls") {

		m_wndView.ClearRoomList();
		Room room;

		std::string buf = str.substr(0, 4);
		str = str.substr(4);
		int count = stoi(buf);

		for (int i = 0; i < count; i++) {
			std::string buf = str.substr(0, 4);
			str = str.substr(4);
			UINT rID = stoi(buf);

			buf = str.substr(0, 2);
			str = str.substr(2);
			int len = stoi(buf);

			std::string rName = str.substr(0, len);
			str = str.substr(len);

			room.roomID = rID;
			room.name = CString::CStringT(CA2CT(rName.c_str()));

			m_wndView.UpdateRoomList(room);
		}
	}
	else if (buf == "norm") {
		
		std::string buf = str.substr(0, 2);
		str = str.substr(2);
		int len = stoi(buf);

		std::string uName = str.substr(0, len);
		str = str.substr(len);

		buf = str.substr(0, 2);
		str = str.substr(2);
		len = stoi(buf);

		std::string rName = str.substr(0, len);
		str = str.substr(len);

		Message recvMsg;
		recvMsg.userName = CString(CA2CT(uName.c_str()));
		recvMsg.msg = CString(CA2CT(str.c_str()));

		m_wndView.UpdateMessageList(recvMsg);
	}
	else {
		AfxMessageBox(_T("Protocol, Critical Error"));
	}
}

