// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"
#include "MainFrm.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CreateRoomDlg.h"

// CChildView Constructor / Destructor

CChildView::CChildView()
{
}
CChildView::~CChildView()
{
}
void CChildView::UpdateRoomList(std::vector<Room> roomList) {
	this->dataModule.UpdateRoomList(roomList);

	if (this->page == Page::RoomList) Invalidate();
}
void CChildView::UpdateMessageList(Message msg) {
	this->dataModule.AddMessage(msg);

	if (this->page == Page::chattingRoom) Invalidate();
}
void CChildView::UpdateUserInfo(std::string userName, std::string roomName) {
	dataModule.SetUserInfo(userName, roomName);

	if (this->page == Page::chattingRoom) Invalidate();
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

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

	parentFrame = ((CMainFrame*)GetParentFrame());
	return 0;
}
void CChildView::OnDestroy()
{
	::DestroyCaret();

	CWnd::OnDestroy();
}

//------------------------------------------------------------------------------
//							Display Section
//------------------------------------------------------------------------------
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
	DisplayRoomListSpace(dc, roomListSpaceSize);
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
void CChildView::DisplayRoomListSpace(CPaintDC& dc, const CRect& rect) {
	CRect RoomSpace(rect);
	RoomSpace.bottom = RoomSpace.top + DisplayRoomSize;


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

	auto roomNameList = this->dataModule.GetRoomList();
	int index = 0;
	for (auto iter = roomNameList.begin(); iter != roomNameList.end(); iter++) {

		
		if (index++ == pointedRoom) dc.FillSolidRect(CRect(RoomSpace.left, RoomSpace.top,
			RoomSpace.right, RoomSpace.bottom), RGB(242, 242, 242));

		dc.Rectangle(CRect(RoomSpace.left + 10, RoomSpace.top + 10,
			RoomSpace.left + 60, RoomSpace.top + 60));

		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(iter->GetString(), iter->GetLength(), &(CRect(RoomSpace.left + 70, RoomSpace.top + 15,
			RoomSpace.right, RoomSpace.top + 35)), DT_LEFT);

		RoomSpace.top += DisplayRoomSize;
		RoomSpace.bottom += DisplayRoomSize;
	}

	dc.SelectObject(def_font);
	font.DeleteObject();
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

	

	dc.DrawText(this->dataModule.currRoom, this->dataModule.currRoom.GetLength(), CRect(80, 20, 200, 40), DT_LEFT);
	dc.DrawText(CString("x"), 1, &closeButton, DT_LEFT);
	dc.SelectObject(def_font);
	font.DeleteObject();
}
void CChildView::DisplayLogSpace(CPaintDC& dc, const CRect& rect) {
	CRect CommentSpace(rect);
	CommentSpace.top = CommentSpace.bottom - DisplayLogSize;

	dc.FillSolidRect(rect, RGB(155, 187, 212));
	
	CFont font;
	VERIFY(font.CreateFont(
		15,                       // nHeight
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


	auto messageList = this->dataModule.GetMessageList();
	for( auto iter = messageList.rbegin(); iter != messageList.rend(); iter++) {

		CString user = iter->userName;
		CString msg = iter->msg;

		CSize fontSize = dc.GetTextExtent(msg);
		SetBkMode(dc, TRANSPARENT);

		if (user == this->dataModule.myName) {
			dc.Rectangle(CRect(CommentSpace.right - 55, CommentSpace.top + 5,
				CommentSpace.right - 5, CommentSpace.bottom - 5));

			CBrush brush;
			brush.CreateSolidBrush(RGB(247, 230, 0));
			CBrush* oldBrush = dc.SelectObject(&brush);

			dc.RoundRect(CRect(CommentSpace.right - 70 - fontSize.cx - margin, CommentSpace.top + 25 - margin,
				CommentSpace.right - 70 + margin, CommentSpace.bottom - 10 + margin), CPoint(17, 17));

			brush.DeleteObject();
			dc.SelectObject(oldBrush);

			dc.DrawText(user.GetString(), user.GetLength(), &CRect(CommentSpace.left, CommentSpace.top,
				CommentSpace.right - 60, CommentSpace.bottom - 20), DT_RIGHT);
			dc.DrawText(msg.GetString(), msg.GetLength(), &CRect(CommentSpace.left, CommentSpace.top + 30,
				CommentSpace.right - 70, CommentSpace.bottom - 10), DT_RIGHT);
		}
		else if (user == "_system") {
			// delta = top / bottom 에서 떨어진 거리
			int delta = (DisplayLogSize - fontSize.cy) / 2;

			dc.FillSolidRect(CRect(CommentSpace.left + 10, CommentSpace.top + delta - margin,
				CommentSpace.right - 10, CommentSpace.bottom - delta + margin), RGB(169, 189, 206));
			dc.DrawText(msg.GetString(), msg.GetLength(), &CRect(CommentSpace.left + 10, CommentSpace.top + delta,
				CommentSpace.right - 10, CommentSpace.bottom - delta), DT_CENTER);
		}
		else {
			dc.Rectangle(CRect(CommentSpace.left + 5, CommentSpace.top + 5,
				CommentSpace.left + 55, CommentSpace.bottom - 5));
			dc.RoundRect(CRect(CommentSpace.left + 70 - margin, CommentSpace.top + 25 - margin,
				CommentSpace.left + 70 + fontSize.cx + margin, CommentSpace.bottom - 10 + margin), CPoint(17, 17));

			dc.DrawText(user.GetString(), user.GetLength(), &CRect(CommentSpace.left + 60, CommentSpace.top,
				CommentSpace.right, CommentSpace.bottom - 20), DT_LEFT);
			dc.DrawText(msg.GetString(), msg.GetLength(), &CRect(CommentSpace.left + 70, CommentSpace.top + 30,
				CommentSpace.right, CommentSpace.bottom - 10), DT_LEFT);
		}

		CommentSpace.top -= DisplayLogSize;
		CommentSpace.bottom -= DisplayLogSize;
		
		if (CommentSpace.top < chattingLogSpaceSize.top) break;
	}
	dc.SelectObject(def_font);
	font.DeleteObject();
}
void CChildView::DisplayTypingSpace(CPaintDC& dc, const CRect& rect) {

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

	

	CPoint poi(margin + typingSpaceSize.left + m_caretInfo.offset.x,
		margin + typingSpaceSize.top + m_caretInfo.offset.y);
	SetCaretPos(poi);

	CBrush brush;
	if (!isFocused) {
		brush.CreateSolidBrush(RGB(240, 240, 240));
		dc.SetTextColor(RGB(200, 200, 200));
	}
	else {
		brush.CreateSolidBrush(RGB(247, 230, 0));
		if (!isSendable) {
			dc.SetTextColor(RGB(189, 176, 58));
		}
	}
	CBrush* oldBrush = dc.SelectObject(&brush);

	dc.RoundRect(sendButton, CPoint(2, 2));

	brush.DeleteObject();
	dc.SelectObject(oldBrush);
	
	dc.DrawText(_T("전송"), 2, &sendButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	dc.SetTextColor(RGB(0, 0, 0));

	dc.SelectObject(def_font);
	font.DeleteObject();

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void CChildView::INShowCaret() {
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
	else {
		AfxMessageBox(_T("NoWay"));
	}
}
void CChildView::INHideCaret() {
	HideCaret();
}

void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	isFocused = true;
	INShowCaret();
}
void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	isFocused = false;
	INHideCaret();
}

// Internal
void CChildView::INClearBuffer() {
	this->m_str.Empty();
	this->m_strSize.RemoveAll();
	this->m_caretInfo.Clear();

	isSendable = false;
}




//------------------------------------------------------------------------------
//						주요 Display Event 생성 지점
//------------------------------------------------------------------------------
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
		_T("맑은고딕")));			// lpszFacename

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
			ReqSendChatting();
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

			if (m_str.GetLength() == 0) isSendable = false;
		}
	}
	else {
		m_str += (TCHAR)nChar;
		m_caretInfo.offset.x += fontSize.cx;
		m_strSize.Add(BackSpaceInfo(true, fontSize.cx));

		isSendable = true;
	}

	dc.SelectObject(def_font);
	font.DeleteObject();
	Invalidate();
}
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (this->page == Page::chattingRoom) {

		if (roomInfoSpaceSize.PtInRect(point)) {
			CRect closeButtonArea = CRect(closeButton.left - margin, closeButton.top - margin,
				closeButton.right + margin, closeButton.bottom + margin);
			
			if (closeButtonArea.PtInRect(point)) {
				ReqLeaveRoom();
			}
			else {
				isDrag = true;
				GetCursorPos(&dragSPos);
			}
		}
		else if (typingSpaceSize.PtInRect(point)) {
			CRect sendButtonArea = CRect(sendButton.left - margin, sendButton.top - margin,
				sendButton.right + margin, sendButton.bottom + margin);

			if (sendButtonArea.PtInRect(point)) {
				ReqSendChatting();
			}
		}
	}
	else if (this->page == Page::RoomList) {
		
		if (toolsSpaceSize.PtInRect(point)) {
			CRect createButtonArea = CRect(createButton.left - margin, createButton.top - margin,
				createButton.right + margin, createButton.bottom + margin);
			CRect closeButtonArea = CRect(closeButton.left - margin, closeButton.top - margin,
				closeButton.right + margin, closeButton.bottom + margin);

			if (createButtonArea.PtInRect(point)) {
				CreateRoomDlg dlg;
				if (IDOK == dlg.DoModal()) {
					CString roomName = dlg.RoomName;
					ReqCreateRoom(roomName);
				}
			}
			else if (closeButtonArea.PtInRect(point)) {
				((CMainFrame*)AfxGetMainWnd())->OnClose();
			}
		}
		else if (roomListSpaceSize.PtInRect(point)) {
			int yOffset = point.y - roomListSpaceSize.top;
			int roomNum = yOffset / DisplayRoomSize;

			int roomID = this->dataModule.GetRoomID(roomNum);
			
			if (roomID != -2) {
				ReqJoinRoom(roomID);
			}
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isDrag) {
		CPoint now;
		GetCursorPos(&now);
		CPoint dif = now - dragSPos;
		CRect frameloc;
		parentFrame->GetWindowRect(&frameloc);
		frameloc.top += dif.y;
		frameloc.bottom += dif.y;
		frameloc.right += dif.x;
		frameloc.left += dif.x;
		parentFrame->MoveWindow(&frameloc, 1);
		dragSPos = now;
	}

	// Data Modifying
	else {
		if (this->page == Page::chattingRoom) {}
		else if (this->page == Page::RoomList) {
			if (roomListSpaceSize.PtInRect(point)) {
				int yOffset = point.y - roomListSpaceSize.top;
				int roomNum = yOffset / DisplayRoomSize;

				if (roomNum < this->dataModule.GetRoomListSize()) {
					if (pointedRoom != roomNum) {
						pointedRoom = roomNum;
						Invalidate();
					}
				}
				else {
					if (pointedRoom != -1) {
						pointedRoom = -1;
						Invalidate();
					}
				}
			}
			else {
				if (pointedRoom != -1) {
					pointedRoom = -1;
					Invalidate();
				}
			}
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isDrag) isDrag = false;

	CWnd::OnLButtonUp(nFlags, point);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



// Request
//	Send a Message:	'norm' + body
//	Create Room:	'rmcr' + roomName
//	Leave Room:		'rmlv
//	Join Room:		'rmjn' + roomID
void CChildView::ReqSendChatting() {
	if (this->m_str.GetLength() == 0) return;

	std::string msg("norm");
	msg += std::string(CT2CA(m_str.operator LPCWSTR()));

	parentFrame->processor.RegisterEvent("cs" + msg);

	this->INClearBuffer();
	Invalidate();
}
void CChildView::ReqCreateRoom(CString roomName) {
	std::string msg("rmcr");
	msg += std::string(CT2CA(roomName.operator LPCWSTR()));

	parentFrame->processor.RegisterEvent("cs" + msg);
}
void CChildView::ReqLeaveRoom() {
	this->page = Page::RoomList;
	this->INClearBuffer();
	this->dataModule.INClearRoomList();
	this->dataModule.INClearMessageList();
	this->INHideCaret();

	std::string msg("rmlv");
	parentFrame->processor.RegisterEvent("cs" + msg);
	Invalidate();
}
void CChildView::ReqJoinRoom(int roomID) {
	char buf[5];
	sprintf_s(buf, 5, "%d", roomID);

	std::string msg("rmjn");
	msg += buf;

	parentFrame->processor.RegisterEvent("cs" + msg);
}

// Response
void CChildView::ResJoinRoom() {
	this->page = Page::chattingRoom;
	//AfxMessageBox(_T("Hello")); <= 유/무에 따라 Caret 보이는지 안보이는지가 결정된다. 이상한 버그
	INShowCaret();
	Invalidate();
}