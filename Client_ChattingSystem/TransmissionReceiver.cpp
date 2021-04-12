#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "TransmissionReceiver.h"

IMPLEMENT_DYNCREATE(TransmissionReceiver, CWinThread)
TransmissionReceiver::TransmissionReceiver() {
	AfxMessageBox(_T("Transmission Receiver 생성!"));
}
TransmissionReceiver::~TransmissionReceiver() {
	AfxMessageBox(_T("Transmission Receiver 파괴!"));
}
BOOL TransmissionReceiver::InitInstance() {
	AfxMessageBox(_T("InitInstance() 호출!"));

	return TRUE;
}