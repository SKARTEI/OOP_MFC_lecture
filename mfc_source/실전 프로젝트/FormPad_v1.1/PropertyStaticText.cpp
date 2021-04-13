// PropertyStaticText.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyStaticText.h"


// CPropertyStaticText 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyStaticText, CPropertyBase)

CPropertyStaticText::CPropertyStaticText(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyStaticText::IDD, pParent)
	, m_bWebLink(FALSE)
	, m_strCaption(_T(""))
{
}

CPropertyStaticText::~CPropertyStaticText()
{
}

void CPropertyStaticText::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_WEBLINK, m_bWebLink);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_strCaption);
}


BEGIN_MESSAGE_MAP(CPropertyStaticText, CPropertyBase)
END_MESSAGE_MAP()


// CPropertyStaticText 메시지 처리기입니다.
