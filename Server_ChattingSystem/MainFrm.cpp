// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Server_ChattingSystem.h"

#include "MainFrm.h"

#include "AMQPServer.h"
#include "DataModule.h"

#include "EventSettings.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

//------------------------------------------------------------------------------------------------------------------------------
//											기본 제공
//------------------------------------------------------------------------------------------------------------------------------
CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}
CMainFrame::~CMainFrame()
{
}
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}
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

// Window Message Procedures

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}
BOOL CMainFrame::OnCmdMsg(int nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
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
	
	this->processor.Stop();
	this->displayModule->Stop();

	CFrameWnd::OnClose();
}
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------


/*
* Behaviors
*	MainFrame controls FrontEnd / BackEnd Works
*	FrontEnds, there is a view, who will show a log, such as a client has connected with ID.
*	BackEnds, As a core module, MainFrame manages transmission & logger
* Reponsibilities
*	CoreModule Holder
*	CoreModule: Manage Modules, each module sends event to core module, then core module deal with that events
*/
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

	this->transmission = std::shared_ptr<AMQPServer>(new AMQPServer);
	this->Run();

	return 0;
}


#include "Processor.h"

Processor* CMainFrame::FindIdleProcessor() {
	return &processor;
}

void CMainFrame::Tick() { AfxMessageBox(_T("Hello. I am Server")); }
void CMainFrame::Connect(UID id) {
	auto idleProcessor = FindIdleProcessor();	
	idleProcessor->RegisterEvent("conn" + id);
}
void CMainFrame::Disconnect(UID id) {
	auto idleProcessor = FindIdleProcessor();
	idleProcessor->RegisterEvent("disc" + id);
}
void CMainFrame::RecvMessage(std::string msg) {
	auto idleProcessor = FindIdleProcessor();
	idleProcessor->RegisterEvent("norm" + msg);
}

void CMainFrame::Run() {
	this->transmission->SetServer(this);

	this->dataModule = std::shared_ptr<DataModule>(new DataModule);
	this->displayModule = std::shared_ptr<Logger>(new Logger);
	this->displayModule->Start();

	this->processor.SetModules(this->transmission, this->displayModule, this->dataModule);
	this->processor.Start();

	this->command = std::shared_ptr<CommandDlg>(new CommandDlg);
	this->command->Create(IDD_Command);
	this->command->ShowWindow(SW_SHOW);
}