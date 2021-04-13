#pragma once

#include "ControlBase.h"
#include "PropertyAnimate.h"


// CMyAnimate

class CMyAnimate : public CAnimateCtrl, public CControlBase
{
	DECLARE_SERIAL(CMyAnimate)
	friend class CFormPadView;

public:
	CMyAnimate();
	virtual ~CMyAnimate();

public:
	BOOL Create( CRect &rect, CWnd *pParentWnd );

protected:
	void Serialize( CArchive& ar );

protected:
	CPropertyBase *GetProperyPage()	{ return &m_Property; }
	void ReflectPropery();
	void Action()	{ Play(-1, -1, -1); }
	void Stop()		{ CAnimateCtrl::Stop(); }

protected:
	CPropertyAnimate	m_Property;
	CString	&			m_strPath;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
