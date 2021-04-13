// MyGroupBox.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyGroupBox.h"

#include "ControlToolBar.h"


// CMyGroupBox

IMPLEMENT_SERIAL(CMyGroupBox, CObject, 1)

CMyGroupBox::CMyGroupBox()
	: CControlBase( 2 )
	, m_strCaption( m_Property.m_strCaption )
{
	m_strCaption = _T("Static");
}

CMyGroupBox::~CMyGroupBox()
{
}


BEGIN_MESSAGE_MAP(CMyGroupBox, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CMyGroupBox 메시지 처리기입니다.

void CMyGroupBox::Serialize (CArchive& ar)
{
	CButton::Serialize(ar);
	if (ar.IsStoring())
		ar << m_strCaption;
	else
		ar >> m_strCaption;
}

BOOL CMyGroupBox::Create(CRect &rect, CWnd *pParentWnd)
{
	BOOL bRtn = CButton::Create( m_strCaption,
		WS_CHILD|WS_VISIBLE|BS_OWNERDRAW|BS_NOTIFY,
		rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );
	return bRtn;
}

void CMyGroupBox::PostNcDestroy() 
{
	delete this;
	CButton::PostNcDestroy();
}

void CMyGroupBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{ 
		CButton::OnLButtonDown(nFlags, point);
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

void CMyGroupBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
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

void CMyGroupBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CButton::OnLButtonUp(nFlags, point);
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
	CButton::OnLButtonUp(nFlags, point);
}

void CMyGroupBox::OnContextMenu(CWnd* pWnd, CPoint point) 
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

void CMyGroupBox::ReflectPropery()
{
	SetWindowText( m_strCaption );
}

void CMyGroupBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	CRect rectClient = lpDrawItemStruct->rcItem;

	pDC->SetBkMode( TRANSPARENT );
	pDC->SelectStockObject( NULL_BRUSH );

	CRect rect( rectClient );
	int cxChar, cyChar;
	{
		CFont *pFont = GetParent()->GetFont();
		CFont *pOldFont = pDC->SelectObject( pFont );

		TEXTMETRIC tm;
		pDC->GetTextMetrics( &tm );
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight;

		pDC->SelectObject( pOldFont );

		rect.top += cyChar >> 1;
	}
	pDC->DrawEdge( rect, BDR_RAISEDINNER|BDR_SUNKENOUTER, BF_RECT );

	pDC->SetBkMode( OPAQUE );
	pDC->TextOut( cxChar, 0, _T(" ") + m_strCaption + _T(" ") );
}
