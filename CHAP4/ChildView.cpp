
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "chapter4_8.h"
#include "ChildView.h"
static CList<CPoint, POINT&> clist;// 정보 보관하는 클래스
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
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
	
	while (pos != NULL)
	{
		point = clist.GetNext(pos);

		dc.Ellipse(point.x - 50, point.y - 20, point.x + 50, point.y + 20);
	}
	
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.Rectangle(point.x - 20, point.y - 20, point.x + 20, point.y + 20);
	clist.AddTail(point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.Ellipse(point.x - 20, point.y - 20, point.x + 20, point.y + 20);	
	clist.AddTail(point);
}
