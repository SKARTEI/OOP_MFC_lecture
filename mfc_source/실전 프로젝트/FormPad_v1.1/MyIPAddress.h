#pragma once

#include "ControlBase.h"
#include "MyComboBox.h"
#include "PropertyIPAddress.h"

#define SOCKET_PORT					8000
#define	WM_APP_ADJUST_SERIALIZE		WM_APP + 0

// CMyIPAddress

class CMyIPAddress : public CIPAddressCtrl, public CControlBase
{
	DECLARE_SERIAL(CMyIPAddress)

public:
	CMyIPAddress();
	virtual ~CMyIPAddress();

public:
	CMyComboBox	*GetCurrentCombo()		{ return m_pCombo; }
	void SendData( CString& str )		{ m_Socket.SendMessage(str); }
	void ReceiveData( CString& str )	{ if (m_pCombo) m_pCombo->ReceiveData(str); }

public:
	BOOL Create( CRect &rect, CWnd *pParentWnd );

protected:
	void Serialize( CArchive& ar );

protected:
	CPropertyBase *GetProperyPage()	{ return &m_Property; }
	void ReflectPropery();
	void Action();
	void Stop();

protected:
	void ActAsServer();
	void ActAsClient();

protected:
	CPropertyIPAddress		m_Property;
	CMyComboBox		*	&	m_pCombo;
	int					&	m_iAction;

// inner-class call
public:
	void OnSocketAccept();
	void OnSocketReceive(const CString &m_strMsg);
	void OnSocketClose();

	//------------------
	// CKNChatSocket
	//------------------
	class CKNChatSocket : public CSocket
	{
	public:
		CKNChatSocket(CMyIPAddress *pSink, int uiPort=SOCKET_PORT+1);
		virtual ~CKNChatSocket();

		// Attributes
	public:
		void Initialize();
		void Release();

		// Operations
	public:
		void Serialize(CArchive& ar);
		void SendMessage(const CString &strMsg);

		// Overrides
	public:
		virtual void OnReceive(int nErrorCode);
		virtual void OnClose(int nErrorCode);

	protected:
		CMyIPAddress	*	m_pSink;
		UINT				m_uiPort;
		CString				m_strReceiveMsg;
		CString				m_strSendMsg;
		CSocketFile		*	m_pSocketFile;
		CArchive		*	m_pArchiveIn;
		CArchive		*	m_pArchiveOut;
	};
	CKNChatSocket		m_Socket;	// Data Socket

	//------------------
	// CKNChatSocket
	//------------------
	class CListenSocket : public CSocket
	{
	public:
		CListenSocket(CMyIPAddress *pSink);
		virtual ~CListenSocket();

		// Overrides
	public:
		virtual void OnAccept(int nErrorCode);
		virtual void OnClose(int nErrorCode);

	protected:
		CMyIPAddress	*	m_pSink;
	};
	CListenSocket		m_Listen;	// Listen Socket

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg LRESULT OnAdjustSerialze(WPARAM wParam, LPARAM lParam);
};
