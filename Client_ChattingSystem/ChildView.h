
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

struct CaretInfo {
public:
	CPoint offset;
	CArray<int, int> lineInfo;

public:
	CaretInfo() : offset(0, 0), lineInfo() {}

public:
	void Clear() {
		offset.x = 0;
		offset.y = 0;
		lineInfo.RemoveAll();
	}
};
struct BackSpaceInfo {
	bool isX;
	int size;

	BackSpaceInfo() : isX(false), size(0) {}
	BackSpaceInfo(bool isX, int size) : isX(isX), size(size) {}
};
// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	CString m_str;
	CArray<BackSpaceInfo, BackSpaceInfo> m_strSize;
	CaretInfo m_caretInfo;
	CButton* m_pSendButton = nullptr;

// 작업입니다.
public:
	void InputBufferClear();
	void DisplayChattingLog(CPaintDC& dc, CRect& rect);

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

	// properties
private:
	CList<CString> messageList;

public:
	void UpdateMessageList(CString msg);
	CList<CString>* GetMessageList();
};

