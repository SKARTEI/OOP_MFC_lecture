
// ListCtrlTest2View.cpp: CListCtrlTest2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ListCtrlTest2.h"
#endif

#include "ListCtrlTest2Doc.h"
#include "ListCtrlTest2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListCtrlTest2View

IMPLEMENT_DYNCREATE(CListCtrlTest2View, CFormView)

BEGIN_MESSAGE_MAP(CListCtrlTest2View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CListCtrlTest2View::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CListCtrlTest2View::OnNMDblclkList1)
	ON_COMMAND(ID_PRINT_INDEX, &CListCtrlTest2View::OnPrintIndex)
END_MESSAGE_MAP()

// CListCtrlTest2View 생성/소멸

CListCtrlTest2View::CListCtrlTest2View() noexcept
	: CFormView(IDD_LISTCTRLTEST2_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CListCtrlTest2View::~CListCtrlTest2View()
{
}

void CListCtrlTest2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BOOL CListCtrlTest2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CListCtrlTest2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// ❶ 리스트 컨트롤 생성
	// -> CFormView 클래스를 사용하므로 생성 코드 불필요

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
}


// CListCtrlTest2View 인쇄

BOOL CListCtrlTest2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CListCtrlTest2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CListCtrlTest2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CListCtrlTest2View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CListCtrlTest2View 진단

#ifdef _DEBUG
void CListCtrlTest2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CListCtrlTest2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CListCtrlTest2Doc* CListCtrlTest2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListCtrlTest2Doc)));
	return (CListCtrlTest2Doc*)m_pDocument;
}
#endif //_DEBUG


// CListCtrlTest2View 메시지 처리기


void CListCtrlTest2View::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV->uChanged & LVIF_STATE) { // 상태가 변경되었다면...
		if (pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED)) {
			CString str = m_list.GetItemText(pNMLV->iItem, 0);
			AfxGetMainWnd()->SetWindowText(str);
		}
	}

	*pResult = 0;
}


void CListCtrlTest2View::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1) {
		CString str = m_list.GetItemText(pNMItemActivate->iItem, 0);
		MessageBox(str);
	}

	*pResult = 0;
}


void CListCtrlTest2View::OnPrintIndex()
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos != NULL) {
		while (pos) {
			int nItem = m_list.GetNextSelectedItem(pos);
			TRACE(_T("Item %d selected.\n"), nItem);
		}
	}
}
