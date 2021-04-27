// ChildView.h: CChildView 클래스의 인터페이스
//

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
#include "Transmission.h"
#endif

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	
// 작업입니다.
public:

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

private:
	Transmission transmission;
};

