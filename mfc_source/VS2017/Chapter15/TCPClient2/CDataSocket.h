#pragma once

class CTCPClient2Dlg;

// CDataSocket 명령 대상

class CDataSocket : public CSocket
{
public:
	CDataSocket(CTCPClient2Dlg* pDlg);
	virtual ~CDataSocket();
	CTCPClient2Dlg* m_pDlg;
};


