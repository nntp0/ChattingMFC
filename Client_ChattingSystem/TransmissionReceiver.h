#pragma once

class TransmissionReceiver : CWinThread {
	DECLARE_DYNCREATE(TransmissionReceiver)
	
protected:
	TransmissionReceiver();
	virtual ~TransmissionReceiver();

public:
	virtual BOOL InitInstance();
};