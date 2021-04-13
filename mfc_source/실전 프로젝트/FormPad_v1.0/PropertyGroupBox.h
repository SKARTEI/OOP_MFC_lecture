#pragma once

#include "PropertyBase.h"

// CPropertyGroupBox 대화 상자입니다.

class CPropertyGroupBox : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyGroupBox)

public:
	CPropertyGroupBox(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyGroupBox();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_GROUPBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	CString	m_strCaption;

};
