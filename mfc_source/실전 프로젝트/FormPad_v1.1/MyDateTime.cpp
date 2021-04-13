// MyDateTime.cpp :  구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyDateTime.h"

#include "ControlToolBar.h"


// CMyDateTime

IMPLEMENT_SERIAL(CMyDateTime, CObject, 1)

CMyDateTime::CMyDateTime()
	: CControlBase(6)
	, m_bAlarm( m_Property.m_bAlarm )
	, m_tAlarm( m_Property.m_tAlarm )
{
	m_bAlarm = FALSE;
	m_tAlarm = CTime::GetCurrentTime();
}

CMyDateTime::~CMyDateTime()
{
}


BEGIN_MESSAGE_MAP(CMyDateTime, CDateTimeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMyDateTime 메시지 처리기입니다.

void CMyDateTime::Serialize (CArchive& ar)
{
	CDateTimeCtrl::Serialize(ar);
	if (ar.IsStoring())
		ar << m_bAlarm << m_tAlarm;
	else
		ar >> m_bAlarm >> m_tAlarm;
}

BOOL CMyDateTime::Create(CRect &rect, CWnd *pParentWnd)
{
	BOOL bRtn = CDateTimeCtrl::Create(
		WS_CHILD|WS_VISIBLE|DTS_RIGHTALIGN|DTS_TIMEFORMAT,
		rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );
	return bRtn;
}

void CMyDateTime::PostNcDestroy() 
{
	delete this;
	CDateTimeCtrl::PostNcDestroy();
}

void CMyDateTime::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{ 
		CDateTimeCtrl::OnLButtonDown(nFlags, point);
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
	CDateTimeCtrl::OnLButtonDown(nFlags, point);
}

void CMyDateTime::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		CDateTimeCtrl::OnMouseMove(nFlags, point);
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
	CDateTimeCtrl::OnMouseMove(nFlags, point);
}

void CMyDateTime::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CDateTimeCtrl::OnLButtonUp(nFlags, point);
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
	CDateTimeCtrl::OnLButtonUp(nFlags, point);
}

void CMyDateTime::OnContextMenu(CWnd* pWnd, CPoint point) 
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

void CMyDateTime::ReflectPropery()
{
}

void CMyDateTime::Action()
{
	OnTimer( 0 );	// reset
	SetTimer( 0, 1000, NULL );

	if ( m_bAlarm )
	{
		CTime timeNow = CTime::GetCurrentTime();
		CTimeSpan timeSpan = m_tAlarm - timeNow;
		SetTimer( 1, (UINT)timeSpan.GetTotalSeconds()*1000, NULL );
	}
}

void CMyDateTime::Stop()
{
	KillTimer( 0 );
	if ( m_bAlarm )
		KillTimer( 1 );
}

void CMyDateTime::OnTimer(UINT_PTR nIDEvent) 
{
	switch (nIDEvent)
	{
	case 0:	// clock
		SetTime( COleDateTime::GetCurrentTime() );
		break;

	case 1:	// alarm
		KillTimer( 1 );
		::Beep( 1000, 10000 ); 
		m_bAlarm = FALSE;
		break;
	}
	
	CDateTimeCtrl::OnTimer( nIDEvent );
}
