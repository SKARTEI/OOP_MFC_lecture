// PropertyPicture.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyPicture.h"


// CPropertyPicture 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyPicture, CPropertyBase)

CPropertyPicture::CPropertyPicture(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyPicture::IDD, pParent)
	, m_strPath(_T(""))
	, m_iAction(0)
{
}

CPropertyPicture::~CPropertyPicture()
{
}

void CPropertyPicture::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	DDX_Radio(pDX, IDC_RADIO_ACTION, m_iAction);
}


BEGIN_MESSAGE_MAP(CPropertyPicture, CPropertyBase)
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CPropertyPicture::OnBnClickedButtonPath)
END_MESSAGE_MAP()


// CPropertyPicture 메시지 처리기입니다.

void CPropertyPicture::OnBnClickedButtonPath() 
{
	UpdateData( TRUE );

	CFileDialog dlg(TRUE, NULL, m_strPath, OFN_FILEMUSTEXIST,
		m_iAction == 0 ? _T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||")
		: _T("Enhanced Meta Files (*.emf)|*.emf|All Files (*.*)|*.*||") );
	
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
