
// CommonDialogView.cpp: CCommonDialogView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CommonDialog.h"
#endif

#include "CommonDialogDoc.h"
#include "CommonDialogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommonDialogView

IMPLEMENT_DYNCREATE(CCommonDialogView, CView)

BEGIN_MESSAGE_MAP(CCommonDialogView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CCommonDialogView 생성/소멸

CCommonDialogView::CCommonDialogView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCommonDialogView::~CCommonDialogView()
{
}

BOOL CCommonDialogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCommonDialogView 그리기

void CCommonDialogView::OnDraw(CDC* /*pDC*/)
{
	CCommonDialogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCommonDialogView 인쇄

BOOL CCommonDialogView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCommonDialogView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCommonDialogView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCommonDialogView 진단

#ifdef _DEBUG
void CCommonDialogView::AssertValid() const
{
	CView::AssertValid();
}

void CCommonDialogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommonDialogDoc* CCommonDialogView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommonDialogDoc)));
	return (CCommonDialogDoc*)m_pDocument;
}
#endif //_DEBUG


// CCommonDialogView 메시지 처리기


void CCommonDialogView::OnLButtonDown(UINT nFlags, CPoint point)
{
/* CColorDialog 예제 */
#if 1
	CColorDialog dlg;
	dlg.DoModal();
	COLORREF color = dlg.GetColor(); // 사용자가 선택한 색상을 알아낸다.
#endif
#if 0
	CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN);
	dlg.DoModal();
	COLORREF color = dlg.GetColor(); // 사용자가 선택한 색상을 알아낸다.
#endif

/* CFileDialog 예제 */
#if 0
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
		MessageBox(dlg.GetPathName());
#endif
#if 0
	CFileDialog dlg(FALSE);
	if (dlg.DoModal() == IDOK)
		MessageBox(dlg.GetPathName());
#endif

/* CFontDialog 예제 */
#if 0
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK) {
		CClientDC dc(this);
		// 화면을 지운다.
		CRect rect;
		GetClientRect(&rect);
		dc.SelectStockObject(WHITE_PEN);
		dc.SelectStockObject(WHITE_BRUSH);
		dc.Rectangle(&rect);
		// 선택된 색상을 알아낸다.
		COLORREF color = dlg.GetColor();
		dc.SetTextColor(color);
		// 선택된 글꼴을 알아낸다.
		LOGFONT lf;
		dlg.GetCurrentFont(&lf);
		CFont font;
		font.CreateFontIndirect(&lf);
		dc.SelectObject(&font);
		// 텍스트를 출력한다.
		dc.TextOut(10, 10, CString(_T("한국어 & English")));
	}
#endif

/* CPageSetupDialog 예제 */
#if 0
	CPageSetupDialog dlg;
	dlg.DoModal();
#endif

/* CPageSetupDialog 예제 */
#if 0
	CPrintDialog dlg(TRUE);
	dlg.DoModal();
#endif
#if 0
	CPrintDialog dlg(FALSE);
	dlg.DoModal();
#endif
}
