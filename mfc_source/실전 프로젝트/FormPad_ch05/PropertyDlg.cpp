// PropertyDlg.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyDlg.h"
#include "afxdialogex.h"


// CPropertyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyDlg, CDialog)

CPropertyDlg::CPropertyDlg( CPropertyBase *pDlg, CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyDlg::IDD, pParent)
	, m_pChildDlg( pDlg )
{
}

CPropertyDlg::~CPropertyDlg()
{
}

void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPropertyDlg 메시지 처리기입니다.

int CPropertyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pChildDlg->Create( this );
	m_pChildDlg->ShowWindow( SW_SHOW );

	return 0;
}


BOOL CPropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetClientRect( rect );
	m_pChildDlg->SetWindowPos( NULL, rect.left, rect.top,
		rect.Width(), rect.Height(),
		SWP_NOZORDER | SWP_SHOWWINDOW );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
