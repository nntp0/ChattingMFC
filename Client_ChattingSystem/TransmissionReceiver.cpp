#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "TransmissionReceiver.h"

IMPLEMENT_DYNCREATE(TransmissionReceiver, CWinThread)
TransmissionReceiver::TransmissionReceiver() {
	AfxMessageBox(_T("Transmission Receiver ����!"));
}
TransmissionReceiver::~TransmissionReceiver() {
	AfxMessageBox(_T("Transmission Receiver �ı�!"));
}
BOOL TransmissionReceiver::InitInstance() {
	AfxMessageBox(_T("InitInstance() ȣ��!"));

	return TRUE;
}