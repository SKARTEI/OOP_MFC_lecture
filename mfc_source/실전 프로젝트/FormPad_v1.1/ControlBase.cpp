#include "pch.h"
#include "MainFrm.h"
#include "ControlToolBar.h"
#include "ControlBase.h"


CControlBase::CControlBase( int iIndex )
	: m_bRunMode( ((CMainFrame *)AfxGetMainWnd())->GetMode() )
	, m_wndToolBar( ((CMainFrame *)AfxGetMainWnd())->GetToolBar() )
	, m_iIndex( iIndex )
	, m_bDragging( FALSE )
	, m_Resize( NONE )
{
}

CControlBase::~CControlBase()
{
}
