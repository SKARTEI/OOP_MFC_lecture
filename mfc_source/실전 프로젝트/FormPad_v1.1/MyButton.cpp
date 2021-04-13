// MyButton.cpp: 구현 파일
//

#include "pch.h"
#include "FormPad.h"
#include "MyButton.h"
#include "MainFrm.h"
#include "ControlToolBar.h"


// CMyButton

IMPLEMENT_SERIAL(CMyButton, CButton, 1)

CMyButton::CMyButton()
	: CControlBase( 9 )
	, m_strCaption( m_Property.m_strCaption )
	, m_strPath( m_Property.m_strPath )
	, m_iAction( m_Property.m_iAction )
{
	m_strCaption = _T("Button");
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CMyButton 메시지 처리기

void CMyButton::Serialize( CArchive& ar )
{
	CButton::Serialize(ar);
	if (ar.IsStoring())
		ar << m_strCaption << m_strPath << m_iAction;
	else
		ar >> m_strCaption >> m_strPath >> m_iAction;
}

BOOL CMyButton::Create( CRect &rect, CWnd *pParentWnd )
{ 
	BOOL bRtn = CButton::Create( _T("Button"),
		WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );
	return bRtn;
}

void CMyButton::PostNcDestroy()
{
	delete this;
	CButton::PostNcDestroy();
}

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ( m_bRunMode == TRUE )
	{ 
		switch ( m_iAction )
		{ 
		case 0: // Program 
			::ShellExecute( NULL, _T("open"), m_strPath, 
				NULL, NULL, SW_SHOWNORMAL ); 
			break; 
		case 1: // Mode 
			::AfxGetMainWnd()->PostMessage( WM_COMMAND, 
				MAKEWPARAM(ID_MODE_EDIT, 0), NULL ); 
			break; 
		case 2: // Minimize 
			::AfxGetMainWnd()->CloseWindow(); 
			break; 
		case 3: // Exit 
			::AfxGetMainWnd()->PostMessage( WM_COMMAND, 
				MAKEWPARAM(ID_APP_EXIT, 0), NULL ); 
			break; 
		}
	}
	else
	{
		m_bDragging = TRUE;

		::SetCursor( AfxGetApp()->LoadCursor(
			m_wndToolBar.GetImageAt(m_iIndex) ) );
		SetCapture();

		CRect rect;
		GetParent()->GetClientRect( rect );
		GetParent()->ClientToScreen( rect );
		::ClipCursor( rect );

		GetClientRect( rect );
		CRect rectHORZ( rect ), rectVERT( rect );
		rectHORZ.DeflateRect( RESIZE_POINT, 0 );
		rectVERT.DeflateRect( 0, RESIZE_POINT );
		if ( rectHORZ.PtInRect(point) == FALSE )
		{
			::SetCursor( ::LoadCursor(NULL, IDC_SIZEWE) );
			m_Resize = HORZ;
		}
		else if ( rectVERT.PtInRect(point) == FALSE )
		{
			::SetCursor( ::LoadCursor(NULL, IDC_SIZENS) );
			m_Resize = VERT;
		}
		else
		{
			m_Resize = NONE;
		}

		GetClientRect( rect );
		ClientToScreen( rect );
		m_ptHotspot = point;

		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DOWN,
			(WPARAM)&rect, NULL );
	}
	CButton::OnLButtonDown(nFlags, point);
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bRunMode == TRUE)
	{
		CButton::OnMouseMove(nFlags, point);
	}
	else if (m_bDragging == TRUE && nFlags & MK_LBUTTON)
	{
		CRect rect;
		GetClientRect( rect );

		CSize size( point.x - m_ptHotspot.x, point.y - m_ptHotspot.y );
		ClientToScreen( rect );

		switch ( m_Resize )
		{
		case NONE:
			rect.OffsetRect( size );
			break;
		case HORZ:
			rect.InflateRect( size.cx, 0 );
			break;
		case VERT:
			rect.InflateRect( 0, size.cy );
			break;
		}
		rect.NormalizeRect();

		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DRAG,
			(WPARAM)&rect, NULL );
	}
	CButton::OnMouseMove(nFlags, point);
}

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bRunMode == TRUE)
	{
		CButton::OnLButtonUp(nFlags, point);
	}
	else if ( m_bDragging == TRUE )
	{
		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DROP,
			(WPARAM)FALSE, (LPARAM)this);

		::ClipCursor( NULL );
		ReleaseCapture();
		::SetCursor( ::LoadCursor(NULL, IDC_ARROW) );

		m_bDragging = FALSE;
	}
	CButton::OnLButtonUp(nFlags, point);
}

void CMyButton::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if ( m_bRunMode == TRUE )
		return;
		
	CMenu menu;
	menu.LoadMenu( IDR_MENU_CONTROL );
	CMenu *pMenu = menu.GetSubMenu( 0 );

	::SetWindowLongPtr(GetParent()->GetSafeHwnd(),
		GWLP_USERDATA, (LONG_PTR)this);
	pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, GetParent() );
}

void CMyButton::ReflectPropery()
{
	SetWindowText( m_strCaption );
}

void CMyButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		CButton::OnLButtonDblClk(nFlags, point);
	}
}
