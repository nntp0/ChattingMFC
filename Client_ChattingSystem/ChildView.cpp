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

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);


	// 여기 수정하세요
	/*this->messageList.AddTail(CString("Hello World!"));
	this->messageList.AddTail(CString("Bye World!"));*/

	return TRUE;
}

void CChildView::OnPaint() 
{
	CRect rect;
	GetClientRect(&rect);

	CPaintDC dc(this);

	// Chatting 에 대한 영역과 Typing 영역을 그립니다.

	DisplayChattingLog(dc, rect);
	DisplayUserTyping(dc, rect);
}

void CChildView::DisplayUserTyping(CPaintDC& dc, CRect& rect) {
	rect.top = rect.bottom - 200;
	dc.DrawText(m_str.GetString(), m_str.GetLength(), &rect, DT_LEFT);

	CPoint poi(rect.left + m_caretInfo.offset.x, rect.top + m_caretInfo.offset.y);
	SetCaretPos(poi);
}
void CChildView::DisplayChattingLog(CPaintDC& dc, CRect& rect) {
	auto pos = this->messageList.GetHeadPosition();
	while (pos != NULL) {
		CString temp = this->messageList.GetNext(pos);

		rect.top = rect.top + 20;

		dc.DrawText(temp.GetString(), temp.GetLength(), &rect, DT_LEFT);
	}
}

//void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	delete ((CMainFrame*)AfxGetMainWnd())->m_transmission;
//}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC dc(this);
	CSize fontSize = dc.GetTextExtent((LPCTSTR)&nChar, 1);

	/*if (nChar == VK_RETURN) {

		m_caretInfo.offset.y += fontSize.cy;
		m_strSize.Add(BackSpaceInfo(false, fontSize.cy));

		m_caretInfo.lineInfo.Add(m_caretInfo.offset.x);
		m_caretInfo.offset.x = 0;

		m_str += (TCHAR)nChar;
	}*/
	if (nChar == VK_RETURN) {
		//((CMainFrame*)GetParentFrame())->m_transmission->Send(this->m_str);

		this->InputBufferClear();
		Invalidate();
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

	Invalidate();
}

void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	CreateSolidCaret(5, 20);
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