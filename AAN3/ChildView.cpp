
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "ASSIGN3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/*
CPen RED_PEN(PS_SOLID, 1, RGB(255, 0, 0));
CPen BLUE_PEN(PS_SOLID, 1, RGB(0, 255, 0));
CPen GREEN_PEN(PS_SOLID, 1, RGB(0, 0, 255));

COLORREF colorselect = RGB(255, 0, 0);

unsigned long red = RGB(255, 0, 0);
unsigned long green= RGB(0, 255, 0);
unsigned long blue = RGB(0, 0, 255);
unsigned long color = red;
*/
// CChildView

CChildView::CChildView()
{
	m_bDrawMode = FALSE;
	colorselect = RGB(255, 0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
//	ON_WM_NCLBUTTONUP()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_KEYDOWN()
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
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDrawMode = TRUE;
	m_x1 = m_x2 = point.x;
	m_y1 = m_y2 = point.y;
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDrawMode)
	{
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
		dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
		dc.SetROP2(R2_NOT);
		m_x2 = point.x;
		m_y2 = point.y;
		dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	}
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_COPYPEN);
	m_x2 = point.x;
	m_y2 = point.y;
	//  새로 추가
	CPen pen(PS_SOLID, 1, colorselect);
	dc.SelectObject(pen);
	// 새로추가한 내용 2줄

	dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	m_bDrawMode = FALSE;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 실습 5-7 참고
	switch (nChar) {
	case 'R':	// R키 누르면 변경
		colorselect = RGB(255, 0, 0);
		break;
	case 'G':
		colorselect = RGB(0, 255, 0);
		break;
	case 'B':
		colorselect = RGB(0, 0, 255);
		break;
	default:	// 기본
		colorselect = RGB(255, 0, 0);
		break;
	}
}
