#pragma once

#include "PropertyBase.h"

// CPropertyMonthCal 대화 상자입니다.

class CPropertyMonthCal : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyMonthCal)

public:
	CPropertyMonthCal(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyMonthCal();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_MONTHCALENDAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	BOOL	m_bNoToday;

};
