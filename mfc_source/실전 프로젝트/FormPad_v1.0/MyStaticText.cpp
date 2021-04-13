// MyStaticText.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyStaticText.h"

#include "ControlToolBar.h"


// CMyStaticText

IMPLEMENT_SERIAL(CMyStaticText, CObject, 1)

CMyStaticText::CMyStaticText()
	: CControlBase( 1 )
	, m_bWebLink( m_Property.m_bWebLink )
	, m_strCaption( m_Property.m_strCaption )
{
	m_strCaption = _T("Static");
}

CMyStaticText::~CMyStaticText()
{
}


BEGIN_MESSAGE_MAP(CMyStaticText, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


// CMyStaticText 메시지 처리기입니다.

void CMyStaticText::Serialize (CArchive& ar)
{
}

BOOL CMyStaticText::Create(CRect &rect, CWnd *pParentWnd)
{
	BOOL bRtn = CStatic::Create( m_strCaption,
		WS_CHILD|WS_VISIBLE|SS_LEFT|SS_NOTIFY,
		rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );

    LOGFONT lf;
    pParentWnd->GetFont()->GetLogFont( &lf );
	m_fontStandard.CreateFontIndirect( &lf );
    lf.lfUnderline = (BYTE)TRUE;
    m_fontUnderline.CreateFontIndirect( &lf );

	return bRtn;
}

void CMyStaticText::PostNcDestroy() 
{
	delete this;
	CStatic::PostNcDestroy();
}

void CMyStaticText::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		if ( m_bWebLink )
			::ShellExecute(NULL, _T("open"), m_strCaption, NULL, NULL, SW_SHOWNORMAL);
		CStatic::OnLButtonDown(nFlags, point);
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
	CStatic::OnLButtonDown(nFlags, point);
}

void CMyStaticText::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		CStatic::OnMouseMove(nFlags, point);
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
	CStatic::OnMouseMove(nFlags, point);
}

void CMyStaticText::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CStatic::OnLButtonUp(nFlags, point);
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
	CStatic::OnLButtonUp(nFlags, point);
}

void CMyStaticText::OnContextMenu(CWnd* pWnd, CPoint point) 
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

void CMyStaticText::ReflectPropery()
{
	SetWindowText( m_strCaption );
	SetFont( m_bWebLink ? &m_fontUnderline : &m_fontStandard );
	
	CRect rect;
	GetClientRect( rect );
	ClientToScreen( rect );
	GetParent()->ScreenToClient( rect );
	rect.InflateRect( 3, 3 );
	GetParent()->InvalidateRect( rect );
}

HBRUSH CMyStaticText::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if ( m_bWebLink )
		pDC->SetTextColor( RGB(0, 0, 255) );
	else
		pDC->SetTextColor( RGB(0, 0, 0) );

	pDC->SetBkMode( TRANSPARENT );
	return (HBRUSH)GetStockObject( NULL_BRUSH );
}
