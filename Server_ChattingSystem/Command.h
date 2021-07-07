#pragma once

#include "iServer.h"
#include "iCommand.h"
// CreateRoomDlg ��ȭ ����

class CommandDlg : public CDialogEx, public iCommand
{
	DECLARE_DYNAMIC(CommandDlg)

public:
	CommandDlg(CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
	virtual ~CommandDlg();

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

private:
	CString commandLine;
	CMutex mtxCommandResultList;
public:
	void MessageResponse(CString commandResult);
};
