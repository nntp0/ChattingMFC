// CreateRoomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Command.h"
#include "afxdialogex.h"
#include "resource.h"

#include "MainFrm.h"


// CreateRoomDlg 대화 상자

IMPLEMENT_DYNAMIC(CommandDlg, CDialogEx)

CommandDlg::CommandDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Command, pParent) {

}
CommandDlg::~CommandDlg()
{
}
BOOL CommandDlg::OnInitDialog() {
	return TRUE;
}
void CommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CommandDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CommandDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CommandDlg::OnBnClickedOk()
{
	AfxMessageBox(_T("HelloWorld"));
}