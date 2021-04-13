
// TreeCtrlTest2View.cpp: CTreeCtrlTest2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TreeCtrlTest2.h"
#endif

#include "TreeCtrlTest2Doc.h"
#include "TreeCtrlTest2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeCtrlTest2View

IMPLEMENT_DYNCREATE(CTreeCtrlTest2View, CFormView)

BEGIN_MESSAGE_MAP(CTreeCtrlTest2View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_SHOWSELECTED, &CTreeCtrlTest2View::OnTestShowselected)
	ON_COMMAND(ID_TEST_DELETESELECTED, &CTreeCtrlTest2View::OnTestDeleteselected)
END_MESSAGE_MAP()

// CTreeCtrlTest2View 생성/소멸

CTreeCtrlTest2View::CTreeCtrlTest2View() noexcept
	: CFormView(IDD_TREECTRLTEST2_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTreeCtrlTest2View::~CTreeCtrlTest2View()
{
}

void CTreeCtrlTest2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BOOL CTreeCtrlTest2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CTreeCtrlTest2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// ❶ 트리 컨트롤 생성
	// -> CFormView 클래스를 사용하므로 생성 코드 불필요

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
}


// CTreeCtrlTest2View 인쇄

BOOL CTreeCtrlTest2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTreeCtrlTest2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTreeCtrlTest2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CTreeCtrlTest2View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CTreeCtrlTest2View 진단

#ifdef _DEBUG
void CTreeCtrlTest2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CTreeCtrlTest2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTreeCtrlTest2Doc* CTreeCtrlTest2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeCtrlTest2Doc)));
	return (CTreeCtrlTest2Doc*)m_pDocument;
}
#endif //_DEBUG


// CTreeCtrlTest2View 메시지 처리기


void CTreeCtrlTest2View::OnTestShowselected()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if (hItem != NULL) {
		CString str = m_tree.GetItemText(hItem);
		MessageBox(str);
	}
}


void CTreeCtrlTest2View::OnTestDeleteselected()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if (hItem != NULL) {
		m_tree.DeleteItem(hItem);
	}
}
