
// ListCtrlTest1View.cpp: CListCtrlTest1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ListCtrlTest1.h"
#endif

#include "ListCtrlTest1Doc.h"
#include "ListCtrlTest1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListCtrlTest1View

IMPLEMENT_DYNCREATE(CListCtrlTest1View, CView)

BEGIN_MESSAGE_MAP(CListCtrlTest1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CListCtrlTest1View 생성/소멸

CListCtrlTest1View::CListCtrlTest1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CListCtrlTest1View::~CListCtrlTest1View()
{
}

BOOL CListCtrlTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CListCtrlTest1View 그리기

void CListCtrlTest1View::OnDraw(CDC* /*pDC*/)
{
	CListCtrlTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CListCtrlTest1View 인쇄

BOOL CListCtrlTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CListCtrlTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CListCtrlTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CListCtrlTest1View 진단

#ifdef _DEBUG
void CListCtrlTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CListCtrlTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CListCtrlTest1Doc* CListCtrlTest1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListCtrlTest1Doc)));
	return (CListCtrlTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CListCtrlTest1View 메시지 처리기


int CListCtrlTest1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ❶ 리스트 컨트롤 생성
	m_list.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT,
		CRect(10, 10, 310, 110), this, IDC_LIST1);

	// ❷ 이미지 리스트 생성과 초기화
	CImageList ilLarge, ilSmall;
	ilLarge.Create(32, 32, ILC_COLOR4, 1, 1);
	ilSmall.Create(16, 16, ILC_COLOR4, 1, 1);
	ilLarge.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	ilSmall.Add(AfxGetApp()->LoadIcon(IDI_ICON1));

	// ❸ 이미지 리스트 설정
	m_list.SetImageList(&ilLarge, LVSIL_NORMAL);
	m_list.SetImageList(&ilSmall, LVSIL_SMALL);
	ilLarge.Detach();
	ilSmall.Detach();

	// ❹ 헤더 초기화
	m_list.InsertColumn(0, _T("이름"), LVCFMT_LEFT, 100, 0);
	m_list.InsertColumn(1, _T("성적"), LVCFMT_LEFT, 100, 1);
	m_list.InsertColumn(2, _T("학점"), LVCFMT_LEFT, 100, 2);

	// ❺ 항목 추가
	m_list.InsertItem(0, _T("임현선"), 0);
	m_list.InsertItem(1, _T("김기태"), 0);
	m_list.InsertItem(2, _T("서유경"), 0);

	// ❻ 하위 항목 추가
	m_list.SetItemText(0, 1, _T("90"));
	m_list.SetItemText(0, 2, _T("A0"));
	m_list.SetItemText(1, 1, _T("95"));
	m_list.SetItemText(1, 2, _T("A+"));
	m_list.SetItemText(2, 1, _T("70"));
	m_list.SetItemText(2, 2, _T("B0"));

	// 확장 스타일 지정
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	return 0;
}
