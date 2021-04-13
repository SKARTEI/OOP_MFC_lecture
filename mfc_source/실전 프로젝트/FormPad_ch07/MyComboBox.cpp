// MyComboBox.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyComboBox.h"

#include "ControlToolBar.h"
#include "MyIPAddress.h"


// CMyComboBox

IMPLEMENT_SERIAL(CMyComboBox, CObject, 1)

CMyComboBox::CMyComboBox()
	: CControlBase(8),
	m_strName( m_Property.m_strName ),
	m_pIPAddress(NULL)
{
	m_strName = _T("ComboBox");
}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CMyComboBox 메시지 처리기입니다.

void CMyComboBox::Serialize (CArchive& ar)
{
}

BOOL CMyComboBox::Create(CRect &rect, CWnd *pParentWnd)
{
	BOOL bRtn = CComboBox::Create(
		WS_CHILD|WS_VISIBLE|CBS_SIMPLE|WS_VSCROLL,
		rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );
	return bRtn;
}

void CMyComboBox::PostNcDestroy() 
{
	delete this;
	CComboBox::PostNcDestroy();
}

void CMyComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{ 
		CComboBox::OnLButtonDown(nFlags, point);
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
	CComboBox::OnLButtonDown(nFlags, point);
}

void CMyComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		CComboBox::OnMouseMove(nFlags, point);
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
	CComboBox::OnMouseMove(nFlags, point);
}

void CMyComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CComboBox::OnLButtonUp(nFlags, point);
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
	CComboBox::OnLButtonUp(nFlags, point);
}

void CMyComboBox::OnContextMenu(CWnd* pWnd, CPoint point) 
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

void CMyComboBox::ReflectPropery()
{
//	SetWindowText(m_strCaption);
}

BOOL CMyComboBox::PreTranslateMessage(MSG* pMsg) 
{
	if ( pMsg->message == WM_KEYDOWN )
	{
		if ( m_bRunMode == FALSE )
			return CWnd::PreTranslateMessage(pMsg);

		int nVirtKey = (int) pMsg->wParam;
		if ( nVirtKey == VK_RETURN )
		{
			CString str;
			GetWindowText(str);
			InsertString(0, str);
			SetEditSel(0, -1);
			SetCurSel(0);
			Clear();
			SendData(str);
		}
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

void CMyComboBox::SendData( CString& str ) 
{
	if ( m_pIPAddress )
		m_pIPAddress->SendData( str );
}
