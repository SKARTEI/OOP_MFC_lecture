
// FormPadView.cpp: CFormPadView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FormPad.h"
#endif

#include "FormPadDoc.h"
#include "FormPadView.h"
#include "MainFrm.h"
#include "MyButton.h"
#include "PropertyDlg.h"

#include "MyAnimate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFormPadView

IMPLEMENT_DYNCREATE(CFormPadView, CFormView)

BEGIN_MESSAGE_MAP(CFormPadView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_APP_CONTROL_DOWN, &CFormPadView::OnControlDown)
	ON_MESSAGE(WM_APP_CONTROL_DRAG, &CFormPadView::OnControlDrag)
	ON_MESSAGE(WM_APP_CONTROL_DROP, &CFormPadView::OnControlDrop)
	ON_COMMAND(ID_CONTROL_DELETE, &CFormPadView::OnControlDelete)
	ON_COMMAND(ID_CONTROL_PROPERTY, &CFormPadView::OnControlProperty)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CFormPadView 생성/소멸

CFormPadView::CFormPadView() noexcept
	: CFormView(IDD_FORMPAD_FORM)
{
	m_rectOld.SetRectEmpty();
}

CFormPadView::~CFormPadView()
{
}

void CFormPadView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CFormPadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CFormPadView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CFormPadView 인쇄

BOOL CFormPadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFormPadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFormPadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CFormPadView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CFormPadView 진단

#ifdef _DEBUG
void CFormPadView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormPadView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFormPadDoc* CFormPadView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFormPadDoc)));
	return (CFormPadDoc*)m_pDocument;
}
#endif //_DEBUG


// CFormPadView 메시지 처리기

void CFormPadView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CFormView::ShowScrollBar(SB_VERT, FALSE);
	CFormView::ShowScrollBar(SB_HORZ, FALSE);
}

void CFormPadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame *pFrame = (CMainFrame *)GetParentFrame();
	if ( pFrame->GetMode() == TRUE )
	{
		pFrame->PostMessage( WM_NCLBUTTONDOWN,
			HTCAPTION, MAKELPARAM(point.x, point.y) );
	}
	else
	{
		CObList list;
		GetDocument()->LookUpControl( list, RUNTIME_CLASS(CMyAnimate) );

		POSITION pos = list.GetHeadPosition();
		while ( pos != NULL )
		{
			CMyAnimate *pAnimate = (CMyAnimate *)list.GetNext( pos );
			CRect rect;
			pAnimate->GetClientRect( rect );
			pAnimate->ClientToScreen( rect );
			ScreenToClient(rect);
			if ( rect.PtInRect(point) == TRUE )
			{
				ClientToScreen( &point );
				pAnimate->OnLButtonDown( nFlags, point );
				return;
			}
		}
	}
	CFormView::OnLButtonDown(nFlags, point);
}

LRESULT CFormPadView::OnControlDown(WPARAM wParam, LPARAM lParam) 
{
	if ( wParam != NULL )
	{
		CClientDC dc( this );
		CRect *pRect = (CRect *)wParam;
		CRect rect( *pRect );
		ScreenToClient( rect );

		dc.DrawDragRect( rect, CSize(1, 1),
			m_rectOld.IsRectEmpty() ? NULL : m_rectOld,
			CSize(1, 1) );
		if ( m_rectOld.IsRectEmpty() == FALSE )
			m_rectOld = rect;
	}
	Invalidate();
	return 1;
}

LRESULT CFormPadView::OnControlDrag(WPARAM wParam, LPARAM lParam)
{
	if ( wParam != NULL )
	{
		CClientDC dc( this );
		CRect *pRect = (CRect *)wParam;
		CRect rect( *pRect );
		ScreenToClient( rect );

		dc.DrawDragRect( rect, CSize(1, 1),
			m_rectOld, CSize(1, 1) );
		m_rectOld = rect;
	}
	return 1;
}

LRESULT CFormPadView::OnControlDrop(WPARAM wParam, LPARAM lParam)
{
	CClientDC dc( this );
	dc.DrawDragRect( m_rectOld, CSize(0, 0),
		m_rectOld, CSize(1, 1) );
	CRect rect = m_rectOld;
	m_rectOld.SetRectEmpty();

	if ( wParam == TRUE )
	{
		CRuntimeClass *pClass = (CRuntimeClass *)lParam;
		CObject *pObj = pClass->CreateObject();
		if ( pObj != NULL )
		{
#if 0
			if ( pObj->IsKindOf(RUNTIME_CLASS( CButton )) == TRUE )
			{
				CMyButton *pButton = (CMyButton *)pObj;
				CControlBase *pControl = (CControlBase *)pButton;
				pControl->Create( rect, this );

				//pButton->Create( rect, this );

				//CButton *pButton = (CButton *)pObj;
				//pButton->Create( _T("Button"),
				//	WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				//	rect, this, 101);
			}
#else
			CMainFrame *pFrame = (CMainFrame *)GetParentFrame();
			CControlToolBar &wndToolBar = pFrame->GetToolBar();
			CControlBase *pControl = wndToolBar.GetControlBase( pObj );
			pControl->Create( rect, this );
#endif
			GetDocument()->AddControl( pObj );
		}
	}
	else
	{
		if (rect.IsRectEmpty() == FALSE)
		{
			CWnd *pWnd = (CWnd *)lParam;
			pWnd->SetWindowPos(NULL, rect.left, rect.top,
				rect.Width(), rect.Height(),
				SWP_NOREPOSITION|SWP_NOZORDER|SWP_SHOWWINDOW);
		}
	}
	Invalidate();
	return 1;
}


void CFormPadView::OnControlDelete()
{
	CObject *pObj = (CObject *)::GetWindowLongPtr(GetSafeHwnd(), GWLP_USERDATA);
	if ( pObj != NULL )
	{
		CWnd *pWnd = (CWnd *)pObj;
		pWnd->ShowWindow( SW_HIDE );
		pWnd->DestroyWindow();

		GetDocument()->RemoveControl( pObj );

		::SetWindowLongPtr( GetParent()->GetSafeHwnd(),
			GWLP_USERDATA, NULL );
	}
}

void CFormPadView::OnControlProperty()
{
	CObject *pObj = (CObject *)::GetWindowLongPtr(GetSafeHwnd(), GWLP_USERDATA);
	if ( pObj != NULL )
	{
		CMainFrame *pFrame = (CMainFrame *)GetParentFrame();
		CControlToolBar &wndToolBar = pFrame->GetToolBar();
		CControlBase *pControl = wndToolBar.GetControlBase( pObj );

		CPropertyDlg dlg( pControl->GetProperyPage() );
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
			pControl->ReflectPropery();

		::SetWindowLongPtr( GetParent()->GetSafeHwnd(),
			GWLP_USERDATA, NULL );
	}
}

void CFormPadView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMainFrame *pFrame = (CMainFrame *)GetParentFrame();
	if ( pFrame->GetMode() == FALSE )
	{
		CObList list;
		GetDocument()->LookUpControl( list, RUNTIME_CLASS(CMyAnimate) );

		POSITION pos = list.GetHeadPosition();
		while ( pos != NULL )
		{
			CMyAnimate *pAnimate = (CMyAnimate *)list.GetNext( pos );
			CRect rect;
			pAnimate->GetClientRect( rect );
			pAnimate->ClientToScreen( rect );
			if ( rect.PtInRect(point) == TRUE )
			{
				pAnimate->OnContextMenu( pWnd, point );
				return;
			}
		}
	}
}
