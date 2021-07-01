// CreateRoomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "RoomInfoDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#include "MainFrm.h"


// CreateRoomDlg 대화 상자

IMPLEMENT_DYNAMIC(RoomInfoDlg, CDialogEx)

RoomInfoDlg::RoomInfoDlg(std::vector<std::string> clientList, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RoomInfo, pParent) {
	this->clientList.assign(clientList.begin(), clientList.end());
}
RoomInfoDlg::~RoomInfoDlg()
{
}
BOOL RoomInfoDlg::OnInitDialog() {
	CListBox* clientListBox = (CListBox*)GetDlgItem(IDC_RoomInfo);
	
	for (auto iter = clientList.begin(); iter != clientList.end(); iter++) {
		clientListBox->AddString(CString(iter->c_str()));
	}

	return TRUE;
}
void RoomInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(RoomInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RoomInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void RoomInfoDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
