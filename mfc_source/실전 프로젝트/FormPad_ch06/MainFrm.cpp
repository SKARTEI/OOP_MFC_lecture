﻿
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "FormPad.h"

#include "MainFrm.h"
#include "FormPadDoc.h"
#include "ControlBase.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_MODE_EDIT, &CMainFrame::OnModeEdit)
	ON_COMMAND(ID_MODE_RUN, &CMainFrame::OnModeRun)
	ON_UPDATE_COMMAND_UI(ID_MODE_EDIT, &CMainFrame::OnUpdateModeEdit)
	ON_UPDATE_COMMAND_UI(ID_MODE_RUN, &CMainFrame::OnUpdateModeRun)
	ON_COMMAND_RANGE(32781, 32790, &CMainFrame::OnControl)
	ON_UPDATE_COMMAND_UI(ID_BUTTON32781, &CMainFrame::OnUpdateButton32781)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
	: m_bRunMode(FALSE)
	, m_iDifference(::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYMENU))
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_CONTROLS))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// 툴바의 투명색 설정
	CImageList imgToolBar;
	BOOL bRtn = imgToolBar.Create( IDR_CONTROLS, 16, 15, RGB(255,0,255) );
	if ( bRtn != FALSE )
	{
		CImageList *pImageList = m_wndToolBar.GetToolBarCtrl().SetImageList( &imgToolBar );
		if ( pImageList != NULL )
			pImageList->DeleteImageList();
		imgToolBar.Detach();
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// 툴바 띄우기 (수직으로 길게 배열)
	CToolBarCtrl& tbctrl = m_wndToolBar.GetToolBarCtrl();
	int nButtonCount = tbctrl.GetButtonCount();
	CPoint pt( lpCreateStruct->x + 10, lpCreateStruct->y + 70 );
	CRect rect;

	FloatControlBar( &m_wndToolBar, CPoint(0, 0) ); // 먼저 띄운다! 
	tbctrl.SetRows( nButtonCount, TRUE, rect ); 
	m_wndToolBar.CalcDynamicLayout( rect.Width(), LM_HORZ|LM_COMMIT );
	FloatControlBar( &m_wndToolBar, pt, CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC );

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style &= ~WS_MAXIMIZEBOX;
	return TRUE;
}

BOOL CMainFrame::DestroyWindow()
{
	// 종료 전 정지모드 라우팅
	m_bRunMode = TRUE;
	OnModeEdit();
	return CFrameWnd::DestroyWindow();
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnModeEdit()
{
	if ( m_bRunMode == FALSE )
		return;
	m_bRunMode = FALSE;

#if 1	// 메뉴, 상태바, 툴바 나타내기
	SetMenu( CMenu::FromHandle(m_hMenuDefault) );
	m_wndStatusBar.ShowWindow( SW_SHOW );
	if ( m_wndToolBar.IsFloating() == TRUE )
		m_wndToolBar.GetDockingFrame()->ShowWindow( SW_SHOW );
	else
		m_wndToolBar.ShowWindow( SW_SHOW );
#endif

	HWND hWnd = GetSafeHwnd();
	LONG_PTR lStyle = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	lStyle |= WS_CAPTION;
	::SetWindowLongPtr(hWnd, GWL_STYLE, lStyle);

	CRect rect;
	GetWindowRect( rect );
	rect.top -= m_iDifference;

	SetWindowPos( NULL, rect.left, rect.top,
		rect.Width(), rect.Height(),
		SWP_NOZORDER|SWP_FRAMECHANGED );
	RecalcLayout( TRUE );

	// 정지모드 라우팅
	CFormPadDoc *pDoc = (CFormPadDoc *)GetActiveDocument();
	CObList &list = pDoc->GetControlList();
	POSITION pos = list.GetHeadPosition();
	while ( pos != NULL )
	{
		CObject *pObj = list.GetNext(pos);
		CControlBase *pControl = m_wndToolBar.GetControlBase(pObj);
		pControl->Stop();
	}
}

void CMainFrame::OnModeRun()
{
	if ( m_bRunMode == TRUE )
		return;
	m_bRunMode = TRUE;

#if 1	// 메뉴, 상태바, 툴바 숨기기
	SetMenu( NULL );
	m_wndStatusBar.ShowWindow( SW_HIDE );
	if ( m_wndToolBar.IsFloating() == TRUE )
		m_wndToolBar.GetDockingFrame()->ShowWindow( SW_HIDE );
	else
		m_wndToolBar.ShowWindow( SW_HIDE );
#endif

	HWND hWnd = GetSafeHwnd();
	LONG_PTR lStyle = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	lStyle &= ~WS_CAPTION;
	::SetWindowLongPtr(hWnd, GWL_STYLE, lStyle);

	CRect rect;
	GetWindowRect( rect );
	rect.top += m_iDifference;

	SetWindowPos( NULL, rect.left, rect.top,
		rect.Width(), rect.Height(),
		SWP_NOZORDER|SWP_FRAMECHANGED );
	RecalcLayout( TRUE );

	// 실행모드 라우팅
	CFormPadDoc *pDoc = (CFormPadDoc *)GetActiveDocument();
	CObList &list = pDoc->GetControlList();
	POSITION pos = list.GetHeadPosition();
	while ( pos != NULL )
	{
		CObject *pObj = list.GetNext(pos);
		CControlBase *pControl = m_wndToolBar.GetControlBase(pObj);
		pControl->Action();
	}
}

void CMainFrame::OnUpdateModeEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio( m_bRunMode == FALSE );
}

void CMainFrame::OnUpdateModeRun(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio( m_bRunMode == TRUE );
}

void CMainFrame::OnControl(UINT nID)
{
}

void CMainFrame::OnUpdateButton32781(CCmdUI*pCmdUI)
{
	pCmdUI->SetRadio( TRUE );
}
