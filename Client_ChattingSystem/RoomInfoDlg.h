#pragma once

#include <vector>
#include <string>
// CreateRoomDlg ��ȭ ����


class RoomInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RoomInfoDlg)

public:
	RoomInfoDlg(std::vector<std::string>, CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
	virtual ~RoomInfoDlg();

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
	std::vector<std::string> clientList;
};
