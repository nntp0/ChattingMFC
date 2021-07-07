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
	: CDialogEx(IDD_Command, pParent) 
{
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
	GetDlgItemText(IDC_Command, commandLine);

	if (commandLine == "") return;

	SetDlgItemText(IDC_Command, _T(""));
	mtxCommandResultList.Lock();
	((CListBox*)GetDlgItem(IDC_CommandResult))->AddString(commandLine);
	mtxCommandResultList.Unlock();
	((CMainFrame*)GetParent())->ProcCommand(std::string(CT2CA(commandLine.operator LPCWSTR())));
}
void CommandDlg::MessageResponse(CString commandResult) {
	mtxCommandResultList.Lock();
	((CListBox*)GetDlgItem(IDC_CommandResult))->AddString(commandResult);
	mtxCommandResultList.Unlock();
}