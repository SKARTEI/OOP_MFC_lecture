
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "ASSIGN6.h"
#include "ChildView.h"
#include <afxcoll.h>
#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CList<CPoint, POINT&> clist_left;// 좌클릭 정보 보관하는 클래스
static CList<CPoint, POINT&> clist_right;// 우클릭 정보 보관하는 클래스
// CChildView

CChildView::CChildView()
{
	CMetaFileDC dc;
	dc.CreateEnhanced(NULL, NULL, NULL, NULL);
	dc.Rectangle(0, 0, 10, 10);
	dc.Ellipse(1, 1, 9, 9);
	m_hmf = dc.CloseEnhanced();

}

CChildView::~CChildView()
{
	::DeleteEnhMetaFile(m_hmf);
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
	CWnd::Invalidate(FALSE);
	POSITION pos_left = clist_left.GetHeadPosition();


	POSITION pos_right = clist_right.GetHeadPosition();
	

	
	while (pos_left != NULL)
	{
		CPoint point_left = clist_left.GetNext(pos_left);
		CRect rect_left(point_left.x - 20, point_left.y - 20, point_left.x + 20, point_left.y + 20);
		dc.PlayMetaFile(m_hmf, &rect_left);
	}
	while(pos_right != NULL)
	{
		CPoint point_right = clist_right.GetNext(pos_right);
		CRect rect_right(point_right.x - 50, point_right.y - 20, point_right.x + 50, point_right.y + 20);
		dc.PlayMetaFile(m_hmf, &rect_right);
	}
	
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect_left(point.x - 20, point.y - 20, point.x + 20, point.y + 20);
	dc.PlayMetaFile(m_hmf, &rect_left);

	clist_left.AddTail(point);
	CWnd::Invalidate(FALSE);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect_right(point.x - 50, point.y - 20, point.x + 50, point.y + 20);
	dc.PlayMetaFile(m_hmf, &rect_right);

	clist_right.AddTail(point);
	CWnd::Invalidate(FALSE);
}
