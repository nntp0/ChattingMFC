// ChattingServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"

#include <afxsock.h>

#include "ChattingServer.h"

// Resource List
#include "ListenSocket.h"
#include "AcceptSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            _tprintf(_T("Hello World!\n"));

            AfxSocketInit();

            CListenSocket listenSock;

            // If Creation succeeds, not null
            if (listenSock.Create(8089)) {
                // If Listen succeeds, not null
                if (!listenSock.Listen()) {
                    _tprintf(_T("%d"), GetLastError());
                    AfxMessageBox(_T("ListenSock Listen Fail"));
                }
            }
            else {
                _tprintf(_T("%d"), GetLastError());
                AfxMessageBox(_T("ListenSock Create Fail"));
            }

            Sleep(5000);

            CAcceptSocket acceptSocket;

            listenSock.Close();
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
