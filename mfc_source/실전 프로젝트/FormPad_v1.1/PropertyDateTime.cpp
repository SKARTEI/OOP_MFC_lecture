// PropertyDateTime.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyDateTime.h"


// CPropertyDateTime 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyDateTime, CPropertyBase)

CPropertyDateTime::CPropertyDateTime(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyDateTime::IDD, pParent)
	, m_bAlarm(FALSE)
	, m_tAlarm(0)
{
}

CPropertyDateTime::~CPropertyDateTime()
{
}

void CPropertyDateTime::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_ALARM, m_bAlarm);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_tAlarm);
}


BEGIN_MESSAGE_MAP(CPropertyDateTime, CPropertyBase)
	ON_BN_CLICKED(IDC_BUTTON_NOW, &CPropertyDateTime::OnBnClickedButtonNow)
END_MESSAGE_MAP()


// CPropertyDateTime 메시지 처리기입니다.

void CPropertyDateTime::OnBnClickedButtonNow() 
{
	UpdateData( TRUE );
	m_tAlarm = CTime::GetCurrentTime();
	UpdateData( FALSE );
}
