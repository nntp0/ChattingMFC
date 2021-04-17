#include "pch.h"
#include "framework.h"

#include <afxsock.h>
#include "AcceptSocket.h"

CAcceptSocket::CAcceptSocket() {
	AfxMessageBox(_T("CAcceptSocket Constructor"));
}
CAcceptSocket::~CAcceptSocket() {
	AfxMessageBox(_T("CAcceptSocket Destructor"));
}