
// chatper_8View.cpp: Cchatper8View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "chatper_8.h"
#endif

#include "chatper_8Doc.h"
#include "chatper_8View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cchatper8View

IMPLEMENT_DYNCREATE(Cchatper8View, CFormView)

BEGIN_MESSAGE_MAP(Cchatper8View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_CHECK2, &Cchatper8View::OnBnClickedCheck2)
END_MESSAGE_MAP()

// Cchatper8View 생성/소멸

Cchatper8View::Cchatper8View() noexcept
	: CFormView(IDD_CHATPER_8_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cchatper8View::~Cchatper8View()
{
}

void Cchatper8View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL Cchatper8View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void Cchatper8View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// Cchatper8View 인쇄

BOOL Cchatper8View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cchatper8View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cchatper8View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void Cchatper8View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// Cchatper8View 진단

#ifdef _DEBUG
void Cchatper8View::AssertValid() const
{
	CFormView::AssertValid();
}

void Cchatper8View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

Cchatper8Doc* Cchatper8View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cchatper8Doc)));
	return (Cchatper8Doc*)m_pDocument;
}
#endif //_DEBUG


// Cchatper8View 메시지 처리기


void Cchatper8View::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
