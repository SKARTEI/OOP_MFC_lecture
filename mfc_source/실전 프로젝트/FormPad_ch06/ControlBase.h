#pragma once

#include "PropertyBase.h"

class CControlToolBar;

class CControlBase
{
public:
	CControlBase( int iIndex );
	virtual ~CControlBase();

public:
	virtual BOOL Create( CRect &rect, CWnd *pParentWnd ) = 0;
	virtual CPropertyBase *GetProperyPage() = 0;
	virtual void ReflectPropery() = 0;
	virtual void Action() = 0;
	virtual void Stop() = 0;

protected:
	int					m_iIndex;
	BOOL				m_bDragging;
	CPoint				m_ptHotspot;
	enum { NONE, HORZ, VERT, }	m_Resize;

protected:
	BOOL			&	m_bRunMode;
	CControlToolBar	&	m_wndToolBar;

};
