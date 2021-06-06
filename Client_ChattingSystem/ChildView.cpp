// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MainFrm.h"

// CChildView Constructor / Destructor

CChildView::CChildView()
{
}
CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}
int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	return 0;
}
void CChildView::OnDestroy()
{
	::DestroyCaret();

	CWnd::OnDestroy();
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	
	if (this->page == Page::chattingRoom) DisplayChattingRoom(dc);
	else if (this->page == Page::RoomList) DisplayRoomList(dc);
}

// RoomList View
void CChildView::DisplayRoomList(CPaintDC &dc) {
	DisplayClientInfoSpace(dc);
	DisplayToolsSpace(dc, toolsSpaceSize);
	DisplayRoomListSpace(dc);
}
void CChildView::DisplayClientInfoSpace(CPaintDC& dc) {
	dc.FillSolidRect(clientInfoSpaceSize, RGB(236, 236, 237));
}
void CChildView::DisplayToolsSpace(CPaintDC& dc, const CRect& rect) {
	dc.FillSolidRect(toolsSpaceSize, RGB(100, 236, 237));

// x Button
	CFont font;
	VERIFY(font.CreateFont(
		20,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_NORMAL,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Ariel")));            // lpszFacename

	CFont* def_font = dc.SelectObject(&font);

	dc.DrawText(CString("+"), 1, &createButton, DT_LEFT);
	dc.DrawText(CString("x"), 1, &closeButton, DT_LEFT);
	dc.SelectObject(def_font);
	font.DeleteObject();
}
void CChildView::DisplayRoomListSpace(CPaintDC& dc) {
	//dc.FillSolidRect(roomListSpaceSize, RGB(255, 255, 255));
}

// ChattingRoom View
void CChildView::DisplayChattingRoom(CPaintDC& dc) {
	DisplayRoomInfoSpace(dc, roomInfoSpaceSize);
	DisplayLogSpace(dc, chattingLogSpaceSize);
	DisplayTypingSpace(dc, typingSpaceSize);
}
void CChildView::DisplayRoomInfoSpace(CPaintDC& dc, const CRect& rect) {
	dc.FillSolidRect(rect, RGB(169, 189, 206));

// Client Image
	CPen pen;
	pen.CreatePen(PS_NULL, 3, RGB(255, 255, 255));
	CPen* oldPen = dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldBrush = dc.SelectObject(&brush);

	dc.Ellipse(15, 15, 65, 65);

	pen.DeleteObject();
	brush.DeleteObject();
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);

// X Button
	CFont font;
	VERIFY(font.CreateFont(
		20,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_NORMAL,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Ariel")));            // lpszFacename

	CFont* def_font = dc.SelectObject(&font);

	

	dc.DrawText(currRoom, currRoom.GetLength(), CRect(80, 20, 200, 40), DT_LEFT);
	dc.DrawText(CString("x"), 1, &closeButton, DT_LEFT);
	dc.SelectObject(def_font);
	font.DeleteObject();


}
void CChildView::DisplayLogSpace(CPaintDC& dc, const CRect& rect) {

	int spaceSize = 20;
	int spaceTime = 0;
	CRect lineSpace(0, 0, 0, 0);

	dc.FillSolidRect(rect, RGB(155, 187, 212));
	auto pos = this->messageList.GetHeadPosition();
	while (pos != NULL) {
		Message temp = this->messageList.GetNext(pos);

		CString user = temp.userName;
		CString msg = temp.msg;

		spaceTime++;
		lineSpace.top = spaceSize * spaceTime;

		dc.DrawText(msg.GetString(), msg.GetLength(), &(rect - lineSpace), DT_LEFT);
	}
}
void CChildView::DisplayTypingSpace(CPaintDC& dc, const CRect& rect) {

	int margin = 5;
	CRect marginSpace(margin, margin, 0, 0);

	CFont font;
	VERIFY(font.CreateFont(
		20,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_NORMAL,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("맑은고딕")));            // lpszFacename
	CFont* def_font = dc.SelectObject(&font);

	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_str.GetString(), m_str.GetLength(), &(rect - marginSpace), DT_LEFT);

	dc.SelectObject(def_font);
	font.DeleteObject();

	CPoint poi(margin + typingSpaceSize.left + m_caretInfo.offset.x,
		margin + typingSpaceSize.top + m_caretInfo.offset.y);
	SetCaretPos(poi);
}



void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC dc(this);

	CFont font;
	VERIFY(font.CreateFont(
		20,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_NORMAL,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("맑은고딕")));            // lpszFacename

	CFont* def_font = dc.SelectObject(&font);

	
	CSize fontSize = dc.GetTextExtent((LPCTSTR)&nChar, 1);

	if (nChar == VK_RETURN) {
		if (GetKeyState(VK_SHIFT) & 0x80) {
			m_caretInfo.offset.y += fontSize.cy;
			m_strSize.Add(BackSpaceInfo(false, fontSize.cy));

			m_caretInfo.lineInfo.Add(m_caretInfo.offset.x);
			m_caretInfo.offset.x = 0;

			m_str += (TCHAR)nChar;
		}
		else {
			((CMainFrame*)GetParentFrame())->m_transmission->Send(std::string(CT2CA(m_str.operator LPCWSTR())));
			this->InputBufferClear();
			Invalidate();
		}
		
	}
	else if (nChar == _T('\b')) {

		if (m_str.GetLength() > 0) {
			BackSpaceInfo temp = m_strSize.GetAt(m_strSize.GetSize() - 1);

			if (temp.isX) {
				m_caretInfo.offset.x -= temp.size;
			}
			else {
				m_caretInfo.offset.y -= temp.size;
				m_caretInfo.offset.x = m_caretInfo.lineInfo.GetAt(m_caretInfo.lineInfo.GetSize() - 1);
				m_caretInfo.lineInfo.RemoveAt(m_caretInfo.lineInfo.GetSize() - 1);
			}

			m_strSize.RemoveAt(m_strSize.GetSize() - 1);
			m_str.Delete(m_str.GetLength() - 1);
		}
	}
	else {
		m_str += (TCHAR)nChar;
		m_caretInfo.offset.x += fontSize.cx;
		m_strSize.Add(BackSpaceInfo(true, fontSize.cx));
	}

	dc.SelectObject(def_font);
	font.DeleteObject();
	Invalidate();
}

void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	if (page == Page::chattingRoom)
	{		
		CreateSolidCaret(4, 20);
		CPoint poi(margin + typingSpaceSize.left + m_caretInfo.offset.x,
			margin + typingSpaceSize.top + m_caretInfo.offset.y);
		SetCaretPos(poi);
		ShowCaret();
	}
	else if (page == Page::RoomList) {

	}
}
void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	HideCaret();
}

void CChildView::InputBufferClear() {
	this->m_str.Empty();
	this->m_strSize.RemoveAll();
	this->m_caretInfo.Clear();
}

void CChildView::UpdateRoomList(Room msg) {
	this->RoomNameList.AddTail(msg);
	if (this->page == Page::RoomList) Invalidate();
}
void CChildView::UpdateMessageList(Message msg) {
	this->messageList.AddTail(msg);
	if (this->page == Page::chattingRoom) Invalidate();
}
void CChildView::UpdateUserInfo(std::string userName, std::string roomName) {
	this->myName = CString(CA2CT(userName.c_str()));
	this->currRoom = CString(CA2CT(roomName.c_str()));
	if (this->page == Page::chattingRoom) Invalidate();
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (this->page == Page::chattingRoom) {

		CRect closeButtonArea = CRect(closeButton.left - margin, closeButton.top - margin,
			closeButton.right + margin, closeButton.bottom + margin);

		if (closeButtonArea.PtInRect(point)) {
			this->page = Page::RoomList;
			HideCaret();
			Invalidate();
		}
	}
	else if (this->page == Page::RoomList) {
		CRect createButtonArea = CRect(createButton.left - margin, createButton.top - margin,
			createButton.right + margin, createButton.bottom + margin);
		CRect closeButtonArea = CRect(closeButton.left - margin, closeButton.top - margin,
			closeButton.right + margin, closeButton.bottom + margin);

		if (createButtonArea.PtInRect(point)) {
			AfxMessageBox(_T("Create"));
		}

		if (closeButtonArea.PtInRect(point)) {
			((CMainFrame*)AfxGetMainWnd())->OnClose();
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}
