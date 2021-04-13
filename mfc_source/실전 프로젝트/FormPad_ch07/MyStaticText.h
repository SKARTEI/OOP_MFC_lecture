#pragma once

#include "ControlBase.h"
#include "PropertyStaticText.h"


// CMyStaticText

class CMyStaticText : public CStatic, public CControlBase
{
	DECLARE_SERIAL(CMyStaticText)

public:
	CMyStaticText();
	virtual ~CMyStaticText();

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
	CPropertyStaticText		m_Property;
	BOOL				&	m_bWebLink;
	CString				&	m_strCaption;

protected:
	CFont					m_fontStandard;
	CFont					m_fontUnderline;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};
