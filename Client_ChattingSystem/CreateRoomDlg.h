﻿#pragma once


// CreateRoomDlg 대화 상자

class CreateRoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateRoomDlg)

public:
	CreateRoomDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CreateRoomDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
