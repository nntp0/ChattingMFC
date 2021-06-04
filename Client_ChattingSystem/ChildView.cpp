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
//	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_DESTROY()
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

void CChildView::OnPaint() 
{
	CRect rect;
	CPaintDC dc(this);
	
	if (this->page == Page::chattingRoom) DisplayChattingRoom(dc, rect);
	else if (this->page == Page::RoomList) DisplayRoomList(dc, rect);
}

void CChildView::DisplayChattingRoom(CPaintDC& dc, CRect& rect) {
	DisplayUserTyping(dc, rect);
	DisplayChattingSpace(dc, rect);
	DisplayChattingLog(dc, rect);
}

void CChildView::DisplayRoomList(CPaintDC &dc, CRect& rect) {

}

void CChildView::DisplayUserTyping(CPaintDC& dc, CRect& rect) {
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

	rect.top = 520;
	rect.left = 5;
	rect.bottom = 600;
	rect.right = 440;
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_str.GetString(), m_str.GetLength(), &rect, DT_LEFT);

	CPoint poi(rect.left + m_caretInfo.offset.x, rect.top + m_caretInfo.offset.y);
	SetCaretPos(poi);

	dc.SelectObject(def_font);
	font.DeleteObject();
}
void CChildView::DisplayChattingLog(CPaintDC& dc, CRect& rect) {
	auto pos = this->messageList.GetHeadPosition();
	while (pos != NULL) {
		CString temp = this->messageList.GetNext(pos);

		rect.top = rect.top + 20;

		dc.DrawText(temp.GetString(), temp.GetLength(), &rect, DT_LEFT);
	}
}
void CChildView::DisplayChattingSpace(CPaintDC& dc, CRect& rect) {
	rect.top = 0;
	rect.left = 0;
	rect.bottom = 80;
	rect.right = 440;
	dc.FillSolidRect(rect, RGB(169, 189, 206));
	
	CPen pen;
	pen.CreatePen(PS_NULL, 3, RGB(255, 255, 255));
	CPen* oldPen = dc.SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldBrush = dc.SelectObject(&brush);

	dc.Ellipse(15, 15, 65, 65);

	pen.DeleteObject();
	brush.DeleteObject();
	dc.SelectObject(oldPen);     // 시스템 펜 객체를 돌려줌
	dc.SelectObject(oldBrush);    // 시스템 브러시 객체를 돌려줌



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
	rect.top = 10;
	rect.left = 415;
	dc.DrawText(CString("x"), 1, &rect, DT_LEFT);
	dc.SelectObject(def_font);
	font.DeleteObject();

	rect.top = 80;
	rect.left = 0;
	rect.bottom = 520;
	rect.right = 440;
	dc.FillSolidRect(rect, RGB(155, 187, 212));
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
	CreateSolidCaret(5, 20);
	CPoint poi(5 + m_caretInfo.offset.x, 520 + m_caretInfo.offset.y);
	SetCaretPos(poi);
	ShowCaret();
}
void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	HideCaret();
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

void CChildView::InputBufferClear() {
	this->m_str.Empty();
	this->m_strSize.RemoveAll();
	this->m_caretInfo.Clear();
}

void CChildView::UpdateMessageList(CString msg) {
	TRACE(_T("CChildView UpdateMessageList"));
	TRACE(msg);

	this->messageList.AddTail(msg);

	Invalidate();
}
CList<CString>* CChildView::GetMessageList() {
	return NULL;
}