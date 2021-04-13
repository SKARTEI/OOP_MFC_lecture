// PropertyButton.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyButton.h"
#include "afxdialogex.h"


// CPropertyButton 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyButton, CPropertyBase)

CPropertyButton::CPropertyButton(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyButton::IDD, pParent)
	, m_strCaption(_T(""))
	, m_strPath(_T(""))
	, m_iAction(0)
{

}

CPropertyButton::~CPropertyButton()
{
}

void CPropertyButton::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_strCaption);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	DDX_Radio(pDX, IDC_RADIO_ACTION, m_iAction);
}


BEGIN_MESSAGE_MAP(CPropertyButton, CPropertyBase)
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CPropertyButton::OnBnClickedButtonPath)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_ACTION, IDC_RADIO5, &CPropertyButton::OnRadio)
END_MESSAGE_MAP()


// CPropertyButton 메시지 처리기입니다.


BOOL CPropertyButton::OnInitDialog()
{
	CPropertyBase::OnInitDialog();

	OnRadio(m_iAction == 0 ? IDC_RADIO_ACTION : IDC_RADIO5);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPropertyButton::OnRadio(UINT nID) 
{
	if (nID == IDC_RADIO_ACTION)
	{
		GetDlgItem(IDC_EDIT_PATH)->EnableWindow( TRUE );
		GetDlgItem(IDC_BUTTON_PATH)->EnableWindow( TRUE );
	}
	else
	{
		GetDlgItem(IDC_EDIT_PATH)->EnableWindow( FALSE );	
		GetDlgItem(IDC_BUTTON_PATH)->EnableWindow( FALSE );	
	}
}

void CPropertyButton::OnBnClickedButtonPath()
{
	UpdateData(TRUE);

	CFileDialog dlg(TRUE, NULL, m_strPath, OFN_FILEMUSTEXIST,
		_T("Excutable Files (*.exe)|*.exe|All Files (*.*)|*.*||") );
	
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		m_strPath = dlg.GetPathName();
		UpdateData(FALSE);
	}
	else if (nResponse == IDCANCEL)
	{
	}	
}
