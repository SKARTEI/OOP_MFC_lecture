// MyAnimate.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyAnimate.h"

#include "ControlToolBar.h"


// CMyAnimate

IMPLEMENT_SERIAL(CMyAnimate, CObject, 1)

CMyAnimate::CMyAnimate()
	: CControlBase( 4 )
	, m_strPath( m_Property.m_strPath )
{
}

CMyAnimate::~CMyAnimate()
{
}


BEGIN_MESSAGE_MAP(CMyAnimate, CAnimateCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CMyAnimate 메시지 처리기입니다.

void CMyAnimate::Serialize (CArchive& ar)
{
}

BOOL CMyAnimate::Create(CRect &rect, CWnd *pParentWnd)
{ 
	BOOL bRtn = CAnimateCtrl::Create(
		WS_CHILD|WS_VISIBLE|WS_BORDER,
		rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );
	return bRtn;
}

void CMyAnimate::PostNcDestroy() 
{
	delete this;	
	CAnimateCtrl::PostNcDestroy();
}

void CMyAnimate::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CAnimateCtrl::OnLButtonDown(nFlags, point);
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

		//////////////
		ScreenToClient(&point);
		//////////////
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

		//////////////
		ClientToScreen(&point);
		//////////////
		m_ptHotspot = point;

		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DOWN,
			(WPARAM)&rect, NULL );
	}
	CAnimateCtrl::OnLButtonDown(nFlags, point);
}

void CMyAnimate::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CAnimateCtrl::OnMouseMove(nFlags, point);
	}
	else if (m_bDragging == TRUE && nFlags & MK_LBUTTON)
	{
		CRect rect;
		GetClientRect( rect );

		//////////////
		ClientToScreen(&point);
		//////////////
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
	CAnimateCtrl::OnMouseMove(nFlags, point);
}

void CMyAnimate::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CAnimateCtrl::OnLButtonUp(nFlags, point);
	}
	else if ( m_bDragging == TRUE )
	{
		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DROP,
			(WPARAM)FALSE, (LPARAM)this );

		::ClipCursor( NULL );
		ReleaseCapture();
		::SetCursor( ::LoadCursor(NULL, IDC_ARROW) );

		m_bDragging = FALSE;
	}
	CAnimateCtrl::OnLButtonUp(nFlags, point);
}

void CMyAnimate::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if ( m_bRunMode == TRUE )
		return;
		
	CMenu menu;
	menu.LoadMenu( IDR_MENU_CONTROL );
	CMenu *pMenu = menu.GetSubMenu( 0 );

	::SetWindowLongPtr( GetParent()->GetSafeHwnd(),
		GWLP_USERDATA, (LONG_PTR)this );
	pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, GetParent() );
}

void CMyAnimate::ReflectPropery()
{
	if ( m_strPath.IsEmpty() == TRUE )
	{
		ModifyStyle( ACS_TRANSPARENT, WS_BORDER );
		Close();
		SetWindowPos( NULL, NULL, NULL, NULL, NULL,
			SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_SHOWWINDOW|SWP_FRAMECHANGED );
		Invalidate();
	}
	else
	{
		ModifyStyle( WS_BORDER, ACS_TRANSPARENT );
		Open( m_strPath );
	}
}
