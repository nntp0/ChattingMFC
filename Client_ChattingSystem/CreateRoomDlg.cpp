// CreateRoomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CreateRoomDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#include "MainFrm.h"


// CreateRoomDlg 대화 상자

IMPLEMENT_DYNAMIC(CreateRoomDlg, CDialogEx)

CreateRoomDlg::CreateRoomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CRROOM, pParent) {}
CreateRoomDlg::~CreateRoomDlg()
{
}
void CreateRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CreateRoomDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateRoomDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CreateRoomDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_RoomName, RoomName);

	CDialogEx::OnOK();
}
