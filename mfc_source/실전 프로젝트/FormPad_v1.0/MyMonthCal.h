#pragma once

#include "ControlBase.h"
#include "PropertyMonthCal.h"


// CMyMonthCal

class CMyMonthCal : public CMonthCalCtrl, public CControlBase
{
	DECLARE_SERIAL(CMyMonthCal)

public:
	CMyMonthCal();
	virtual ~CMyMonthCal();

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
	CPropertyMonthCal		m_Property;
	BOOL				&	m_bNoToday;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
