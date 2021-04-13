#pragma once

#include "ControlBase.h"
#include "PropertyComboBox.h"
class CMyIPAddress;

// CMyComboBox

class CMyComboBox : public CComboBox, public CControlBase
{
	DECLARE_SERIAL(CMyComboBox)

public:
	CMyComboBox();
	virtual ~CMyComboBox();

public:
	CString GetName()	{ return m_strName; }
	void SetObject( CMyIPAddress *pIPAddress )	{ m_pIPAddress = pIPAddress; }

public:
	void SendData( CString &str );
	void ReceiveData( CString& str )	{ InsertString( 0, str ); }

public:
	BOOL Create( CRect &rect, CWnd *pParentWnd );

protected:
	void Serialize( CArchive& ar );

protected:
	CPropertyBase *GetProperyPage()	{ return &m_Property; }
	void ReflectPropery();
	void Action()	{}
	void Stop()		{ ResetContent(); }

protected:
	CPropertyComboBox		m_Property;
	CString				&	m_strName;
	CMyIPAddress		*	m_pIPAddress;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
