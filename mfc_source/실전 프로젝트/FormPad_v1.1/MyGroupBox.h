#pragma once

#include "ControlBase.h"
#include "PropertyGroupBox.h"


// CMyGroupBox

class CMyGroupBox : public CButton, public CControlBase
{
	DECLARE_SERIAL(CMyGroupBox)

public:
	CMyGroupBox();
	virtual ~CMyGroupBox();

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
	CPropertyGroupBox		m_Property;
	CString				&	m_strCaption;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
