// MyMonthCal.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyMonthCal.h"

#include "ControlToolBar.h"


// CMyMonthCal

IMPLEMENT_SERIAL(CMyMonthCal, CObject, 1)

CMyMonthCal::CMyMonthCal()
	: CControlBase( 5 )
	, m_bNoToday( m_Property.m_bNoToday )
{
	m_bNoToday = TRUE;
}

CMyMonthCal::~CMyMonthCal()
{
}


BEGIN_MESSAGE_MAP(CMyMonthCal, CMonthCalCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CMyMonthCal 메시지 처리기입니다.

void CMyMonthCal::Serialize (CArchive& ar)
{
}

BOOL CMyMonthCal::Create(CRect &rect, CWnd *pParentWnd)
{
	BOOL bRtn = CMonthCalCtrl::Create(
		WS_CHILD|WS_VISIBLE|MCS_NOTODAY,
		rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );
	return bRtn;
}

void CMyMonthCal::PostNcDestroy() 
{
	delete this;
	CMonthCalCtrl::PostNcDestroy();
}

void CMyMonthCal::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{ 
		CMonthCalCtrl::OnLButtonDown(nFlags, point);
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
	CMonthCalCtrl::OnLButtonDown(nFlags, point);
}

void CMyMonthCal::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		CMonthCalCtrl::OnMouseMove(nFlags, point);
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
	CMonthCalCtrl::OnMouseMove(nFlags, point);
}

void CMyMonthCal::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CMonthCalCtrl::OnLButtonUp(nFlags, point);
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
	CMonthCalCtrl::OnLButtonUp(nFlags, point);
}

void CMyMonthCal::OnContextMenu(CWnd* pWnd, CPoint point) 
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

void CMyMonthCal::ReflectPropery()
{
	if ( m_bNoToday == FALSE )
		ModifyStyle( MCS_NOTODAY, 0 );
	else
		ModifyStyle( 0, MCS_NOTODAY );
}
