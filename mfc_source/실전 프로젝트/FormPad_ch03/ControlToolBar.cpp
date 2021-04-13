// ControlToolBar.cpp: 구현 파일
//

#include "pch.h"
#include "FormPad.h"
#include "ControlToolBar.h"


// CControlToolBar

IMPLEMENT_DYNAMIC(CControlToolBar, CToolBar)

CControlToolBar::CControlToolBar()
	: m_iIndex( -1 )
	, m_bDragging( FALSE )
{
	m_CursorArray[0] = 0;
	m_CursorArray[1] = 26168;
	m_CursorArray[2] = 26166;
	m_CursorArray[3] = 26169;
	m_CursorArray[4] = 26205;
	m_CursorArray[5] = 26303;
	m_CursorArray[6] = 26174;
	m_CursorArray[7] = 26299;
	m_CursorArray[8] = 26164;
	m_CursorArray[9] = 26160;

	m_SizeArray[0] = CSize(0, 0);
	m_SizeArray[1] = CSize(20, 8);
	m_SizeArray[2] = CSize(48, 40);
	m_SizeArray[3] = CSize(20, 20);
	m_SizeArray[4] = CSize(20, 20);
	m_SizeArray[5] = CSize(140, 100);
	m_SizeArray[6] = CSize(100, 15);
	m_SizeArray[7] = CSize(100, 15);
	m_SizeArray[8] = CSize(48, 30);
	m_SizeArray[9] = CSize(50, 14);

	m_ClassArray[0] = RUNTIME_CLASS(CStatic);
	m_ClassArray[1] = RUNTIME_CLASS(CStatic);
	m_ClassArray[2] = RUNTIME_CLASS(CButton);
	m_ClassArray[3] = RUNTIME_CLASS(CStatic);
	m_ClassArray[4] = RUNTIME_CLASS(CAnimateCtrl);
	m_ClassArray[5] = RUNTIME_CLASS(CStatic);
	m_ClassArray[6] = RUNTIME_CLASS(CStatic);
	m_ClassArray[7] = RUNTIME_CLASS(CIPAddressCtrl);
	m_ClassArray[8] = RUNTIME_CLASS(CComboBox);
	m_ClassArray[9] = RUNTIME_CLASS(CButton);
}

CControlToolBar::~CControlToolBar()
{
}


BEGIN_MESSAGE_MAP(CControlToolBar, CToolBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CControlToolBar 메시지 처리기

void CControlToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_iIndex = GetToolBarCtrl().HitTest( &point );
	if ( m_iIndex > 0 )
	{
		m_bDragging = TRUE;
		::SetCursor(AfxGetApp()->LoadCursor( m_CursorArray[m_iIndex]) );
		SetCapture();

		CFrameWnd *pFrame = (CFrameWnd *)AfxGetMainWnd();
		CView *pView = pFrame->GetActiveView();

		CSize size = m_SizeArray[m_iIndex];
		CRect rectUnit( CPoint(0,0), size );
		::MapDialogRect( pView->GetSafeHwnd(), &rectUnit ); 
		size = rectUnit.Size();

		CPoint pt( point );
		ClientToScreen( &pt );

		CRect rect( pt, size );
		rect.OffsetRect( -rect.Width() >> 1, -rect.Height() >> 1 );

		BOOL bSuccess = pView->SendMessage(
			WM_APP_CONTROL_DOWN,
			(WPARAM)&rect, NULL);
	}
	CToolBar::OnLButtonDown(nFlags, point);
}

void CControlToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( m_bDragging == TRUE && nFlags & MK_LBUTTON )
	{
		CFrameWnd *pFrame = (CFrameWnd *)AfxGetMainWnd();
		CView *pView = pFrame->GetActiveView();

		CSize size = m_SizeArray[m_iIndex];
		CRect rectUnit( CPoint(0,0), size );
		::MapDialogRect( pView->GetSafeHwnd(), &rectUnit ); 
		size = rectUnit.Size();

		CPoint pt( point );
		ClientToScreen( &pt );

		CRect rect( pt, size );
		rect.OffsetRect( -rect.Width() >> 1, -rect.Height() >> 1 );

		BOOL bSuccess = pView->SendMessage(
			WM_APP_CONTROL_DRAG,
			(WPARAM)&rect, NULL );
	}
	CToolBar::OnMouseMove(nFlags, point);
}

void CControlToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ( m_bDragging == TRUE )
	{
		ReleaseCapture();
		::SetCursor( LoadCursor(NULL, IDC_ARROW) );
		m_bDragging = FALSE;

		CFrameWnd *pFrame = (CFrameWnd *)AfxGetMainWnd();
		CView *pView = pFrame->GetActiveView();
		BOOL bSuccess = pView->SendMessage(
			WM_APP_CONTROL_DROP,
			(WPARAM)TRUE, (LPARAM)m_ClassArray[m_iIndex] );
	}
	CToolBar::OnLButtonUp(nFlags, point);
}
