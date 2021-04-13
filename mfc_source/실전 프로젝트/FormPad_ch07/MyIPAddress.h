#pragma once

#include "ControlBase.h"
#include "MyComboBox.h"
#include "PropertyIPAddress.h"


// CMyIPAddress

class CMyIPAddress : public CIPAddressCtrl, public CControlBase
{
	DECLARE_SERIAL(CMyIPAddress)

public:
	CMyIPAddress();
	virtual ~CMyIPAddress();

public:
	CMyComboBox	*GetCurrentCombo()		{ return m_pCombo; }
	void SendData( CString& str )		{ m_strMsg = str; }
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
	static UINT MyThread(LPVOID pParam);

protected:
	CPropertyIPAddress		m_Property;
	CMyComboBox		*	&	m_pCombo;
	int					&	m_iAction;
protected:
	CSocket				*	m_pSock;
	CSocket 			*	m_pSockData;
	CWinThread			*	m_pThread;
	CString					m_strMsg;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
