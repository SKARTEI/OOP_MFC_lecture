// CMyDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ModalDialog3.h"
#include "CMyDialog.h"
#include "afxdialogex.h"


// CMyDialog 대화 상자

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_str(_T(""))
	, m_font(0)
	, m_fontsize(0)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STR, m_str);
	DDX_CBIndex(pDX, IDC_FONT, m_font);
	DDX_Text(pDX, IDC_FONTSIZE, m_fontsize);
	DDV_MinMaxInt(pDX, m_fontsize, 10, 40);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_BN_CLICKED(IDC_CLEAR, &CMyDialog::OnBnClickedClear)
END_MESSAGE_MAP()


// CMyDialog 메시지 처리기


void CMyDialog::OnBnClickedClear()
{
	EndDialog(IDC_CLEAR);
}
