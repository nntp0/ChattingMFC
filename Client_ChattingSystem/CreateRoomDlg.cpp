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
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

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


// CreateRoomDlg 메시지 처리기


void CreateRoomDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString temp;

	GetDlgItemText(IDC_EDIT1, temp);
	((CMainFrame*)AfxGetMainWnd())->m_transmission->Send("rmcr" + std::string(CT2CA(temp.operator LPCWSTR())));

	CDialogEx::OnOK();
}
