// ChildView.h: CChildView 클래스의 인터페이스
//

// CChildView 창

#include "iDisplayModule.h"

class CChildView : public CWnd, public iDisplayModule
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
	
	// Method Override
public:
	virtual void DisplayLog(CString msg);
};

