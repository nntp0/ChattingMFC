
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include "Data.h"
#include <vector>

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


#ifndef __CChildView_H_INCLUDED__
#define __CChildView_H_INCLUDED__

class CMainFrame;


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

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

// 특성입니다.
public:
	CMainFrame* parentFrame = nullptr;
	DataModule dataModule;

// Helper Method
public:
	void INClearBuffer();

	void INShowCaret();
	void INHideCaret();

	void ReqLeaveRoom();
	void ReqSendChatting();
	void ReqJoinRoom(int);
	void ReqCreateRoom(CString);

	void ResJoinRoom();

// Internal
private:
	enum class Page {
		chattingRoom,
		RoomList
	};
	Page page = Page::chattingRoom;

	int pointedRoom = -1;

	CString m_str;
	CArray<BackSpaceInfo, BackSpaceInfo> m_strSize;
	CaretInfo m_caretInfo;

// Display Section
private:

	bool isFocused = false;
	bool isSendable = false;
	bool isDrag = false;
	CPoint dragSPos;

	int margin = 5;
	const int DisplayRoomSize = 70;
	const int DisplayLogSize = 60;

	
	const CRect roomInfoSpaceSize = CRect(0, 0, 440, 80);
	const CRect chattingLogSpaceSize = CRect(0, 80, 440, 520);
	const CRect typingSpaceSize = CRect(0, 520, 440, 600);

	const CRect clientInfoSpaceSize = CRect(0, 0, 70, 600);
	const CRect toolsSpaceSize = CRect(70, 0, 440, 80);
	const CRect roomListSpaceSize = CRect(70, 80, 440, 600);

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
	const CPoint sendButtonLoc = CPoint(typingSpaceSize.right - 60, typingSpaceSize.top + 10);
	CRect sendButton = CRect(
		sendButtonLoc.x,
		sendButtonLoc.y,
		sendButtonLoc.x + 50,
		sendButtonLoc.y + 30
	);

public:
	void DisplayRoomList(CDC& dc);
	void DisplayClientInfoSpace(CDC& dc);
	void DisplayToolsSpace(CDC& dc, const CRect& rect);
	void DisplayRoomListSpace(CDC& dc, const CRect& rect);

	void DisplayChattingRoom(CDC& dc);
	void DisplayLogSpace(CDC& dc, const CRect& rect);
	void DisplayTypingSpace(CDC& dc, const CRect& rect);
	void DisplayRoomInfoSpace(CDC& dc, const CRect& rect);

public:
	void UpdateRoomList(std::vector<Room>);
	void UpdateMessageList(Message);
	void UpdateUserInfo(std::string userName, std::string roomName);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
#endif