#pragma once

#include "PropertyBase.h"

// CPropertyComboBox 대화 상자입니다.

class CPropertyComboBox : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyComboBox)

public:
	CPropertyComboBox(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyComboBox();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_COMBOBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CString	m_strName;

};
