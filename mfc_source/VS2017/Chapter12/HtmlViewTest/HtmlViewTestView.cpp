
// HtmlViewTestView.cpp: CHtmlViewTestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "HtmlViewTest.h"
#endif

#include "HtmlViewTestDoc.h"
#include "HtmlViewTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlViewTestView

IMPLEMENT_DYNCREATE(CHtmlViewTestView, CHtmlView)

BEGIN_MESSAGE_MAP(CHtmlViewTestView, CHtmlView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

// CHtmlViewTestView 생성/소멸

CHtmlViewTestView::CHtmlViewTestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CHtmlViewTestView::~CHtmlViewTestView()
{
}

BOOL CHtmlViewTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CHtmlView::PreCreateWindow(cs);
}

void CHtmlViewTestView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	m_pBrowserApp->put_Silent(VARIANT_TRUE); // 스크립트 오류 표시 끄기
#if 1
	Navigate(_T("http://www.hanbit.co.kr/"));
#endif
#if 0
	// 폴더와 파일을 표시한다.
	Navigate(_T("C:\\"));
#endif
#if 0
	// MS 워드 문서를 열어서 편집하거나 저장한다.
	Navigate(_T("C:\\Temp\\test.docx"));
#endif
#if 0
	// MS 엑셀 문서를 열어서 편집하거나 저장한다.
	Navigate(_T("C:\\Temp\\test.xlsx"));
#endif
#if 0
	// 텍스트 문서를 표시한다.
	Navigate(_T("C:\\Temp\\test.txt"));
#endif
#if 0
	// JPEG 포맷으로 저장된 그림을 표시한다.
	Navigate(_T("C:\\Temp\\test.jpg"));
#endif
}


// CHtmlViewTestView 인쇄



// CHtmlViewTestView 진단

#ifdef _DEBUG
void CHtmlViewTestView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlViewTestView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHtmlViewTestDoc* CHtmlViewTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlViewTestDoc)));
	return (CHtmlViewTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CHtmlViewTestView 메시지 처리기
