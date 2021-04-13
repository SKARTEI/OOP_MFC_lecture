// PropertyMonthCal.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyMonthCal.h"


// CPropertyMonthCal 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyMonthCal, CPropertyBase)

CPropertyMonthCal::CPropertyMonthCal(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyMonthCal::IDD, pParent)
	, m_bNoToday(FALSE)
{
}

CPropertyMonthCal::~CPropertyMonthCal()
{
}

void CPropertyMonthCal::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_NOTODAY, m_bNoToday);
}


BEGIN_MESSAGE_MAP(CPropertyMonthCal, CPropertyBase)
END_MESSAGE_MAP()


// CPropertyMonthCal 메시지 처리기입니다.
