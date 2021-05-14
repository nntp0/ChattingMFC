
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "ChattingClient.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{

	//m_caretPos = new CPoint(0, 0);
	//m_typingArea = new CRect();

	//GetClientRect(m_typingArea);
	//m_typingArea->top = m_typingArea->bottom - 200;
	TRACE(_T("Hello World"));
}

CChildView::~CChildView()
{
	AfxMessageBox(_T("CChildView Destructor"));
	//delete m_caretPos;
	//delete m_typingArea;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
//	ON_WM_CLOSE()
ON_WM_DESTROY()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//dc.DrawText(m_str.GetData(), m_str.GetSize(), m_typingArea, DT_LEFT);

	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	CreateSolidCaret(5, 20);
	SetCaretPos(CPoint(20, 20));
	ShowCaret();
}


void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	HideCaret();
	::DestroyCaret();
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == _T('\b')) {
		if (m_str.GetSize() > 0) {
			m_str.RemoveAt(m_str.GetSize() - 1);
		}
	}
	else {
		m_str.Add(nChar);
	}
	
	Invalidate();
}


//void CChildView::OnClose()
//{
//	TRACE(_T("View OnClose"));
//
//	CWnd::OnClose();
//}


void CChildView::OnDestroy()
{
	AfxMessageBox(_T("View OnDestroy"));
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}
