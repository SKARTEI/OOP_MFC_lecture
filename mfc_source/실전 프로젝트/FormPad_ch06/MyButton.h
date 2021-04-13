#pragma once

#include "ControlBase.h"
#include "PropertyButton.h"

#define RESIZE_POINT 5

// CMyButton

class CMyButton : public CButton, public CControlBase
{
	DECLARE_SERIAL(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();

public:
	BOOL Create( CRect &rect, CWnd *pParentWnd );

protected:
	void Serialize( CArchive& ar );

protected:
	CPropertyBase *GetProperyPage()	{ return &m_Property; }
	void ReflectPropery();
	void Action()	{}
	void Stop()		{}

protected:
	CPropertyButton	m_Property;
	CString	&		m_strCaption;
	CString	&		m_strPath;
	int		&		m_iAction;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
