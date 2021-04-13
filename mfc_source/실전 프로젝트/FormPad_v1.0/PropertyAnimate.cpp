// PropertyAnimate.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyAnimate.h"


// CPropertyAnimate 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyAnimate, CPropertyBase)

CPropertyAnimate::CPropertyAnimate(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyAnimate::IDD, pParent)
	, m_strPath(_T(""))
{
}

CPropertyAnimate::~CPropertyAnimate()
{
}


void CPropertyAnimate::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
}


BEGIN_MESSAGE_MAP(CPropertyAnimate, CPropertyBase)
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CPropertyAnimate::OnBnClickedButtonPath)
END_MESSAGE_MAP()


// CPropertyAnimate 메시지 처리기입니다.


void CPropertyAnimate::OnBnClickedButtonPath() 
{
	UpdateData( TRUE );

	CFileDialog dlg( TRUE, NULL, m_strPath, OFN_FILEMUSTEXIST,
		_T("AVI Files (*.avi)|*.avi|All Files (*.*)|*.*||") );
	
	int nResponse = dlg.DoModal();
	if ( nResponse == IDOK )
	{
		m_strPath = dlg.GetPathName();
		UpdateData( FALSE );
	}
	else if (nResponse == IDCANCEL)
	{
	}	
}
