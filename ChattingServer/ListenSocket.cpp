#include "pch.h"
#include "framework.h"

#include <afxsock.h>
#include "ListenSocket.h"

CListenSocket::CListenSocket() {
	AfxMessageBox(_T("CListenSocket Constructor"));
}

CListenSocket::~CListenSocket() {
	AfxMessageBox(_T("CListenSocket Destructor"));
}

void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class



	CAsyncSocket::OnAccept(nErrorCode);
}
