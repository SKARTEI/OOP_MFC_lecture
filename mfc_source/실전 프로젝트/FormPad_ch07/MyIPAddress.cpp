// MyIPAddress.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyIPAddress.h"

#include "ControlToolBar.h"
#include "MyIPAddress.h"


// CMyIPAddress

IMPLEMENT_SERIAL(CMyIPAddress, CObject, 1)

CMyIPAddress::CMyIPAddress()
	: CControlBase( 7 )
	, m_iAction( m_Property.m_iAction )
	, m_pCombo( m_Property.m_pCombo )
	, m_pSock( NULL )
	, m_pThread( NULL )
	, m_pSockData( NULL )
{
}

CMyIPAddress::~CMyIPAddress()
{
}


BEGIN_MESSAGE_MAP(CMyIPAddress, CIPAddressCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CMyIPAddress 메시지 처리기입니다.

void CMyIPAddress::Serialize( CArchive& ar )
{
}

BOOL CMyIPAddress::Create(CRect &rect, CWnd *pParentWnd)
{
	BOOL bRtn = CIPAddressCtrl::Create(
		WS_CHILD|WS_VISIBLE,
		rect, pParentWnd, 101 );
	SetFont( pParentWnd->GetFont() );
	return bRtn;
}

void CMyIPAddress::PostNcDestroy() 
{
	delete this;
	CIPAddressCtrl::PostNcDestroy();
}

void CMyIPAddress::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{ 
		CIPAddressCtrl::OnLButtonDown(nFlags, point);
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
	CIPAddressCtrl::OnLButtonDown(nFlags, point);
}

void CMyIPAddress::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		CIPAddressCtrl::OnMouseMove(nFlags, point);
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
	CIPAddressCtrl::OnMouseMove(nFlags, point);
}

void CMyIPAddress::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CIPAddressCtrl::OnLButtonUp(nFlags, point);
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
	CIPAddressCtrl::OnLButtonUp(nFlags, point);
}

void CMyIPAddress::OnContextMenu(CWnd* pWnd, CPoint point) 
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

void CMyIPAddress::ReflectPropery()
{
	if ( m_iAction == 0 )
		SetWindowText( _T("127.0.0.1") );

	if ( m_pCombo )
		m_pCombo->SetObject( this );
}

void CMyIPAddress::Action()
{
	m_pThread = ::AfxBeginThread( MyThread, this );
	m_pThread->m_bAutoDelete = FALSE;
#ifdef _DEBUG
	m_pThread->SetThreadPriority( THREAD_PRIORITY_IDLE );
#endif
}

void CMyIPAddress::Stop()
{
	if ( m_pSock )
		m_pSock->CancelBlockingCall();
	if ( m_pSockData )
		m_pSockData->CancelBlockingCall();

	if ( m_pThread != NULL )
	{
		if ( m_pThread->m_hThread != NULL )
			::WaitForSingleObject( m_pThread->m_hThread, INFINITE );
		delete m_pThread;
		m_pThread = NULL;
	}
}

UINT CMyIPAddress::MyThread( LPVOID pParam )
{
	CMyIPAddress *pIPAddress = (CMyIPAddress *)pParam;

	if ( pIPAddress->m_iAction == 0 )	// Server
	{
		pIPAddress->ActAsServer();
		pIPAddress->m_pSock = NULL;
		pIPAddress->m_pSockData = NULL;
	}
	else if ( pIPAddress->m_iAction == 1 )	// Client
	{
		pIPAddress->ActAsClient();
	}
	return 1007;
}

void CMyIPAddress::ActAsServer()
{
	CSocket sock;
	if ( !sock.Create(8000) )
		return;

	m_pSock = &sock;
	if ( !sock.Listen() )
		return;

	char buf[256];
	while ( m_bRunMode == TRUE )
	{
		CSocket newsock;
		m_pSockData = &newsock;
		if ( !sock.Accept(newsock) )
			return;

		CString strMsg, strAddress;
		UINT uiPort;
		newsock.GetPeerName( strAddress, uiPort );
		strMsg.Format( _T(">>Enter %s:%d"), strAddress, uiPort );
		ReceiveData( strMsg );

		while ( m_bRunMode == TRUE )
		{
			int iRetVal = newsock.Receive( buf, 256 );
			if ( iRetVal == SOCKET_ERROR )
				break;
			else if ( iRetVal == 0 )
				break;
			else if ( iRetVal > 0 )
			{
				buf[iRetVal] = '\0';
				strMsg.Format( _T(">%s"), buf );
				ReceiveData( strMsg );
			}
		}
	}
}

void CMyIPAddress::ActAsClient()
{
	CSocket sock;
	if ( !sock.Create() )
		return;

	CString strAddress;
	GetWindowText( strAddress );
	if ( !sock.Connect(strAddress, 8000) )
		return;

	CString strMsg;
	UINT uiPort;
	sock.GetPeerName( strAddress, uiPort );
	strMsg.Format( _T("<<Connect %s:%d"), strAddress, uiPort );
	ReceiveData( strMsg );

	int i=0;
	TCHAR buf[256];
	while ( m_bRunMode == TRUE )
	{
		if ( m_strMsg.IsEmpty() )
			continue;

		wsprintf( buf, _T("%s"), m_strMsg );
		if ( sock.Send(buf, m_strMsg.GetLength()+1) == SOCKET_ERROR )
			return;

		m_strMsg.Empty();
		Sleep( 100 );
	}
}
