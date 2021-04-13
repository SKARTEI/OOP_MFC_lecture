#pragma once

#include "ControlBase.h"

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
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
