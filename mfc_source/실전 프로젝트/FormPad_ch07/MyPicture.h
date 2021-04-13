#pragma once

#include "ControlBase.h"
#include "PropertyPicture.h"


// CMyPicture

class CMyPicture : public CStatic, public CControlBase
{
	DECLARE_SERIAL(CMyPicture)

public:
	CMyPicture();
	virtual ~CMyPicture();

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
	CPropertyPicture		m_Property;
	CString				&	m_strPath;
	int					&	m_iAction;

protected:
	CBitmap				*	m_pBitmap;
	CBitmap					m_bitmapDefault;
	BITMAP					m_bmDefault;

	protected:

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
