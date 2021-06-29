#pragma once


// CreateRoomDlg 대화 상자

class ClientInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ClientInfoDlg)

public:
	ClientInfoDlg(CString myName, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ClientInfoDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

public:
	CString myName;
};
