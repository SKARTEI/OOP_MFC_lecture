#pragma once

class CTCPServer2Doc;

// CDataSocket 명령 대상

class CDataSocket : public CSocket
{
public:
	CDataSocket(CTCPServer2Doc* pDoc);
	virtual ~CDataSocket();
	CTCPServer2Doc* m_pDoc;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


