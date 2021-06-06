﻿
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include "DataSettings.h"
#include <string>

#ifndef __CChildView_H_INCLUDED__
#define __CChildView_H_INCLUDED__

class CMainFrame;

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
	// Constructor / Destructor
public:
	CChildView();
	virtual ~CChildView();

	// 재정의입니다.
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 구현입니다.
public:


	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();




// 특성입니다.
public:
	CMainFrame* parentFrame;

	CString m_str;
	CArray<BackSpaceInfo, BackSpaceInfo> m_strSize;
	CaretInfo m_caretInfo;

// 작업입니다.
public:
	void InputBufferClear();

	void DisplayRoomList(CPaintDC& dc);
	void DisplayClientInfoSpace(CPaintDC& dc);
	void DisplayToolsSpace(CPaintDC& dc, const CRect& rect);
	void DisplayRoomListSpace(CPaintDC& dc, const CRect &rect);
	
	void DisplayChattingRoom(CPaintDC& dc);
	void DisplayLogSpace(CPaintDC& dc, const CRect& rect);
	void DisplayTypingSpace(CPaintDC& dc, const CRect& rect);
	void DisplayRoomInfoSpace(CPaintDC& dc, const CRect& rect);

	// properties
private:

	CList<Message> messageList;
	CList<Room> RoomList;

	CString currRoom;
	CString myName;

public:
	void UpdateRoomList(Room);
	void UpdateMessageList(Message);
	void UpdateUserInfo(std::string userName, std::string roomName);

	void SendTypedMessage();
	void CreateRoom(CString);
	void ClearRoomList();

	// Page
private:
	enum class Page {
		chattingRoom,
		RoomList
	};

	int margin = 5;

	Page page = Page::chattingRoom;
	const CRect roomInfoSpaceSize = CRect(0, 0, 440, 80);
	const CRect chattingLogSpaceSize = CRect(0, 80, 440, 520);
	const CRect typingSpaceSize = CRect(0, 520, 440, 600);


	const CPoint ButtonSize = CPoint(10, 20);
	const CPoint closeButtonLoc = CPoint(415, 10);
	CRect closeButton = CRect(
		closeButtonLoc.x, 
		closeButtonLoc.y,
		closeButtonLoc.x + ButtonSize.x,
		closeButtonLoc.y + ButtonSize.y
	);
	const CPoint createButtonLoc = CPoint(395, 10);
	CRect createButton = CRect(
		createButtonLoc.x,
		createButtonLoc.y,
		createButtonLoc.x + ButtonSize.x,
		createButtonLoc.y + ButtonSize.y
	);

	const CRect clientInfoSpaceSize = CRect(0, 0, 70, 600);
	const CRect toolsSpaceSize = CRect(70, 0, 440, 80);
	const CRect roomListSpaceSize = CRect(70, 80, 440, 600);
};

#endif