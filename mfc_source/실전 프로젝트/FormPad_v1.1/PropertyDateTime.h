#pragma once

#include "PropertyBase.h"

// CPropertyDateTime 대화 상자입니다.

class CPropertyDateTime : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyDateTime)

public:
	CPropertyDateTime(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyDateTime();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_DATETIMEPICKER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	BOOL	m_bAlarm;
	CTime	m_tAlarm;

public:
	afx_msg void OnBnClickedButtonNow();

};
