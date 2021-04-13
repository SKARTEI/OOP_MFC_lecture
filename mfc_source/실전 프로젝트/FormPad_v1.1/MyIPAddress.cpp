// MyIPAddress.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyIPAddress.h"

#include "ControlToolBar.h"
#include "MyIPAddress.h"
#include "FormPadDoc.h"


// CMyIPAddress

IMPLEMENT_SERIAL(CMyIPAddress, CObject, 1)

CMyIPAddress::CMyIPAddress()
	: CControlBase( 7 )
	, m_iAction( m_Property.m_iAction )
	, m_pCombo( m_Property.m_pCombo )
	, m_Socket( this )
	, m_Listen( this )
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
	ON_MESSAGE(WM_APP_ADJUST_SERIALIZE, &CMyIPAddress::OnAdjustSerialze)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKNChatSocket inner class
CMyIPAddress::CKNChatSocket::CKNChatSocket(CMyIPAddress *pSink, int uiPort)
	: m_pSink(pSink), m_uiPort(uiPort),
	m_pSocketFile(NULL), m_pArchiveIn(NULL), m_pArchiveOut(NULL)
{
}

CMyIPAddress::CKNChatSocket::~CKNChatSocket()
{
	Release();
}

void CMyIPAddress::CKNChatSocket::Initialize()
{
	m_pSocketFile = new CSocketFile(this);
	if (m_pSocketFile)
	{
		m_pArchiveIn = new CArchive(m_pSocketFile, CArchive::load);
		m_pArchiveOut = new CArchive(m_pSocketFile, CArchive::store);
	}
}

void CMyIPAddress::CKNChatSocket::Release()
{
	if (m_pArchiveIn)
	{
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
	}

	if (m_pArchiveOut)
	{
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
	}

	if (m_pSocketFile)
	{
		delete m_pSocketFile;
		m_pSocketFile = NULL;
	}
}

void CMyIPAddress::CKNChatSocket::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strSendMsg;
	}
	else
	{
		ar >> m_strReceiveMsg;
	}
}

void CMyIPAddress::CKNChatSocket::SendMessage(const CString &strMsg)
{
	m_strSendMsg = strMsg;
	if (m_pArchiveOut)
	{
		Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}

void CMyIPAddress::CKNChatSocket::OnReceive(int nErrorCode)
{
	if (m_pArchiveIn)
		Serialize(*m_pArchiveIn);
	CSocket::OnReceive(nErrorCode);
	m_pSink->OnSocketReceive(m_strReceiveMsg);
}

void CMyIPAddress::CKNChatSocket::OnClose(int nErrorCode)
{
	Release();
	CSocket::OnClose(nErrorCode);
	m_pSink->OnSocketClose();
}

/////////////////////////////////////////////////////////////////////////////
// CListenSocket inner class
CMyIPAddress::CListenSocket::CListenSocket(CMyIPAddress *pSink)
	: m_pSink(pSink)
{
}

CMyIPAddress::CListenSocket::~CListenSocket()
{
}

void CMyIPAddress::CListenSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	m_pSink->OnSocketAccept();
}

void CMyIPAddress::CListenSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	m_pSink->OnSocketClose();
}


// CMyIPAddress 메시지 처리기입니다.

void CMyIPAddress::Serialize( CArchive& ar )
{
	CIPAddressCtrl::Serialize(ar);
	if (ar.IsStoring())
	{
		CString strAddress;
		GetWindowText(strAddress);
		ar << strAddress;

		CFrameWnd *pFrame = (CFrameWnd *)AfxGetMainWnd();
		CFormPadDoc *pDoc = (CFormPadDoc *)pFrame->GetActiveDocument();
		int iIndex = pDoc->FindIndexFromObject(m_pCombo);
		ar << iIndex << m_iAction;
	}
	else
	{
		CString strAddress;
		ar >> strAddress;
		SetWindowText(strAddress);

		int iIndex;
		ar >> iIndex;

		// Adjust m_pCombo after control list get prepared!
		PostMessage(WM_APP_ADJUST_SERIALIZE, iIndex);

		ar >> m_iAction;
	}
}

LRESULT CMyIPAddress::OnAdjustSerialze(WPARAM wParam, LPARAM lParam)
{
	int iIndex = (int)wParam;
	if (iIndex < 0)
		m_pCombo = NULL;
	else
	{
		CFrameWnd *pFrame = (CFrameWnd *)AfxGetMainWnd();
		CFormPadDoc *pDoc = (CFormPadDoc *)pFrame->GetActiveDocument();

		CObject *pObject = pDoc->FindObjectFromIndex(iIndex);
		m_pCombo = (CMyComboBox *)pObject;
	}

	ReflectPropery();
	return 1;
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
	if ( m_iAction == 0 )
		ActAsServer();
	else
		ActAsClient();
}

void CMyIPAddress::Stop()
{
	m_Socket.CancelBlockingCall();
	m_Socket.Close();

	m_Listen.CancelBlockingCall();
	m_Listen.Close();
}

void CMyIPAddress::ActAsServer()
{
	if ( !m_Listen.Create(SOCKET_PORT) )
	{
		TRACE( _T("Socket Create Error\n") );
		return;
	}
	
	if ( !m_Listen.Listen() )
	{
		m_Listen.Close();
		TRACE( _T("Socket Listen Error\n") );
	}
}

void CMyIPAddress::ActAsClient()
{
	if (!m_Socket.Create())
	{
		TRACE( _T("Socket Create Error\n") );
		return;
	}
	
	CString strAddress;
	GetWindowText(strAddress);

	if (!m_Socket.Connect(strAddress, SOCKET_PORT))
	{
		m_Socket.Close();
		TRACE( _T("Socket Connect Error\n") );
		return;
	}

	m_Socket.Initialize();
}

void CMyIPAddress::OnSocketAccept()
{
	// 한 개의 접속만 지원함
	if ( m_Socket.m_hSocket != INVALID_SOCKET )
	{
		m_Socket.CancelBlockingCall();
		m_Socket.Close();
	}

	m_Listen.Accept( m_Socket );
	m_Socket.Initialize();

	CString strMsg, strAddress;
	UINT uiPort;
	m_Socket.GetPeerName( strAddress, uiPort );
	strMsg.Format( _T(">> Accept %s:%d"), strAddress, uiPort );
	ReceiveData(strMsg);
}

void CMyIPAddress::OnSocketReceive( const CString &m_strMsg )
{
	ReceiveData( _T("> ") + m_strMsg );
}

void CMyIPAddress::OnSocketClose()
{
}
