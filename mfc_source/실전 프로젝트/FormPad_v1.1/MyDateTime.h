#pragma once

#include "ControlBase.h"
#include "PropertyDateTime.h"


// CMyDateTime

class CMyDateTime : public CDateTimeCtrl, public CControlBase
{
	DECLARE_SERIAL(CMyDateTime)

public:
	CMyDateTime();
	virtual ~CMyDateTime();

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
	CPropertyDateTime		m_Property;
	BOOL				&	m_bAlarm;
	CTime				&	m_tAlarm;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
