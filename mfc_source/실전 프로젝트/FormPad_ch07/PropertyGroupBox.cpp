// PropertyGroupBox.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyGroupBox.h"


// CPropertyGroupBox 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyGroupBox, CPropertyBase)

CPropertyGroupBox::CPropertyGroupBox(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyGroupBox::IDD, pParent)
	, m_strCaption(_T(""))
{
}

CPropertyGroupBox::~CPropertyGroupBox()
{
}

void CPropertyGroupBox::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_strCaption);
}


BEGIN_MESSAGE_MAP(CPropertyGroupBox, CPropertyBase)
END_MESSAGE_MAP()


// CPropertyGroupBox 메시지 처리기입니다.
