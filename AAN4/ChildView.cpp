
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "ASSIGN8.h"
#include "ChildView.h"
#include <afxtempl.h>
#include <afxcoll.h>

static CList<CPoint, POINT&> clist;// 마우스 좌표 보관하는 클래스

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_bDrawMode = FALSE;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	POSITION pos = clist.GetHeadPosition();
	CPoint point;
	

	//while (pos != NULL)
	if (pos != NULL)
	{
		point = clist.GetNext(pos);
		dc.MoveTo(point);
	}
	while (pos != NULL)
	{
		point = clist.GetNext(pos);
		dc.LineTo(point);
	}
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{	
	CClientDC dc(this);
	m_bDrawMode = TRUE;

	// 변경
	clist.AddTail(point);	
	dc.MoveTo(point);
	dc.LineTo(point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDrawMode)
	{
		CClientDC dc(this);
		CPoint memorized_point = clist.GetTail();
		clist.AddTail(point);
		dc.MoveTo(memorized_point);
		dc.LineTo(point);
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPoint memorized_point = clist.GetTail();
	clist.AddTail(point);
	dc.MoveTo(memorized_point);
	dc.LineTo(point);
	m_bDrawMode = FALSE;
	
	Invalidate(FALSE);
	//CWnd::InvalidateRect(FALSE);
}
