#pragma once


// CreateRoomDlg ��ȭ ����

class ClientInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ClientInfoDlg)

public:
	ClientInfoDlg(CString myName, CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
	virtual ~ClientInfoDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

public:
	CString myName;
};