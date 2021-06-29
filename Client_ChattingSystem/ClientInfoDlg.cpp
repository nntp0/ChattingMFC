// CreateRoomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ClientInfoDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#include "MainFrm.h"


// CreateRoomDlg 대화 상자

IMPLEMENT_DYNAMIC(ClientInfoDlg, CDialogEx)

ClientInfoDlg::ClientInfoDlg(CString myName, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ClientInfo, pParent), myName(myName) {
	
}
ClientInfoDlg::~ClientInfoDlg()
{
}
BOOL ClientInfoDlg::OnInitDialog() {
	SetDlgItemText(IDC_ClientID, myName);
	return TRUE;
}
void ClientInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ClientInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ClientInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void ClientInfoDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
