#pragma once

#define WM_APP_CONTROL_DOWN	WM_APP + 0
#define WM_APP_CONTROL_DRAG	WM_APP + 1
#define WM_APP_CONTROL_DROP	WM_APP + 2

class CControlBase;

// CControlToolBar

class CControlToolBar : public CToolBar
{
	DECLARE_DYNAMIC(CControlToolBar)

public:
	CControlToolBar();
	virtual ~CControlToolBar();

public:
	UINT GetImageAt( int iIndex )	{ return m_CursorArray[iIndex]; }

public:
	CControlBase *GetControlBase( CObject *pObj );

protected:
	DECLARE_MESSAGE_MAP()

protected:
	int		m_iIndex;
	BOOL	m_bDragging;
	UINT	m_CursorArray[10];

protected:
	CSize				m_SizeArray[10];
	CRuntimeClass	*	m_ClassArray[10];

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


