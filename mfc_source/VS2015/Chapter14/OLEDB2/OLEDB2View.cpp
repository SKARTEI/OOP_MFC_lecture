
// OLEDB2View.cpp : COLEDB2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OLEDB2.h"
#endif

#include "OLEDB2Set.h"
#include "OLEDB2Doc.h"
#include "OLEDB2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COLEDB2View

IMPLEMENT_DYNCREATE(COLEDB2View, COleDBRecordView)

BEGIN_MESSAGE_MAP(COLEDB2View, COleDBRecordView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COleDBRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

// COLEDB2View 생성/소멸

COLEDB2View::COLEDB2View()
	: COleDBRecordView(IDD_OLEDB2_FORM)
{
	m_pSet = NULL;
	// TODO: 여기에 생성 코드를 추가합니다.

}

COLEDB2View::~COLEDB2View()
{
}

void COLEDB2View::DoDataExchange(CDataExchange* pDX)
{
	COleDBRecordView::DoDataExchange(pDX);
	// SetDlgItem*/GetDlgItem* API 호출뿐 아니라 DDX_* 함수를 삽입하여 데이터베이스를 뷰에 연결할 수 있습니다.
	// ex. ::SetDlgItemText(m_hWnd, IDC_MYCONTROL, m_pSet->m_MyColumn);
	// 자세한 내용은 MSDN 및 OLEDB 샘플을 참조하십시오.
	DDX_Text(pDX, IDC_EDIT1, m_pSet->m_ST_NUM);
	DDX_Text(pDX, IDC_EDIT2, m_pSet->m_ST_NAME, 256);
	DDX_Text(pDX, IDC_EDIT3, m_pSet->m_ST_MAN);
	DDX_Text(pDX, IDC_EDIT4, m_pSet->m_ST_PHONE, 256);
}

BOOL COLEDB2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return COleDBRecordView::PreCreateWindow(cs);
}

void COLEDB2View::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_OLEDB2Set;
	{
		CWaitCursor wait;
		HRESULT hr = m_pSet->OpenAll();
		if (FAILED(hr))
		{
			// 레코드 집합을 열지 못했습니다.  레코드 집합이 저장
			// 프로시저인 경우 OpenAll()을 호출하기 전에 
			// 입력 매개 변수를 제대로 초기화했는지
			// 확인하십시오.

			AfxMessageBox(_T("레코드 집합을 열지 못했습니다."), MB_OK);
			// 열린 RowSet 없이 현재 레코드의 변경을 시도하면
			// 충돌할 수 있기 때문에 다음 및 이전 레코드 명령을
			// 비활성화합니다.
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}
		if (hr == DB_S_ENDOFROWSET)
		{
			// 행 집합이 비어 있습니다(행이 포함되어 있지 않음).
			AfxMessageBox(_T("레코드 집합이 열렸지만 반환할 행이 없었습니다."), MB_OK);
			// 다음 및 이전 레코드 명령을 비활성화합니다.
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}
	}
	COleDBRecordView::OnInitialUpdate();

	m_pSet->MoveFirst();
	UpdateData(FALSE);
}


// COLEDB2View 인쇄

BOOL COLEDB2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COLEDB2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COLEDB2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// COLEDB2View 진단

#ifdef _DEBUG
void COLEDB2View::AssertValid() const
{
	COleDBRecordView::AssertValid();
}

void COLEDB2View::Dump(CDumpContext& dc) const
{
	COleDBRecordView::Dump(dc);
}

COLEDB2Doc* COLEDB2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COLEDB2Doc)));
	return (COLEDB2Doc*)m_pDocument;
}
#endif //_DEBUG


// COLEDB2View 데이터베이스 지원
CRowset<>* COLEDB2View::OnGetRowset()
{
	return m_pSet->GetRowsetBase();
}



// COLEDB2View 메시지 처리기
