
// TreeCtrlTest1View.cpp: CTreeCtrlTest1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TreeCtrlTest1.h"
#endif

#include "TreeCtrlTest1Doc.h"
#include "TreeCtrlTest1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeCtrlTest1View

IMPLEMENT_DYNCREATE(CTreeCtrlTest1View, CView)

BEGIN_MESSAGE_MAP(CTreeCtrlTest1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CTreeCtrlTest1View 생성/소멸

CTreeCtrlTest1View::CTreeCtrlTest1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTreeCtrlTest1View::~CTreeCtrlTest1View()
{
}

BOOL CTreeCtrlTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTreeCtrlTest1View 그리기

void CTreeCtrlTest1View::OnDraw(CDC* /*pDC*/)
{
	CTreeCtrlTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTreeCtrlTest1View 인쇄

BOOL CTreeCtrlTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTreeCtrlTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTreeCtrlTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTreeCtrlTest1View 진단

#ifdef _DEBUG
void CTreeCtrlTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CTreeCtrlTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTreeCtrlTest1Doc* CTreeCtrlTest1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeCtrlTest1Doc)));
	return (CTreeCtrlTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CTreeCtrlTest1View 메시지 처리기


int CTreeCtrlTest1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ❶ 트리 컨트롤 생성
	m_tree.Create(WS_CHILD | WS_VISIBLE | WS_BORDER |
		TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT,
		CRect(10, 10, 180, 180), this, IDC_TREE1);

	// ❷ 이미지 리스트 생성과 초기화
	CImageList il;
	il.Create(IDB_BITMAP1, 16, 1, RGB(255, 255, 255));

	// ❸ 이미지 리스트 설정
	m_tree.SetImageList(&il, TVSIL_NORMAL);
	il.Detach();

	// ❹ 항목 추가
	/* 1st 레벨 초기화 */
	HTREEITEM hSun = m_tree.InsertItem(_T("태양"), 0, 0, TVI_ROOT, TVI_LAST);

	/* 2nd 레벨 초기화 */
	m_tree.InsertItem(_T("수성"), 1, 1, hSun, TVI_LAST);
	m_tree.InsertItem(_T("금성"), 1, 1, hSun, TVI_LAST);
	HTREEITEM hEarth = m_tree.InsertItem(_T("지구"), 1, 1, hSun, TVI_LAST);
	HTREEITEM hMars = m_tree.InsertItem(_T("화성"), 1, 1, hSun, TVI_LAST);

	/* 3rd 레벨 초기화 */
	m_tree.InsertItem(_T("달"), 2, 2, hEarth, TVI_LAST);
	m_tree.InsertItem(_T("포보스"), 2, 2, hMars, TVI_LAST);
	m_tree.InsertItem(_T("데이모스"), 2, 2, hMars, TVI_LAST);

	return 0;
}
