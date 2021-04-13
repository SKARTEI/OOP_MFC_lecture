#pragma once

#include "PropertyBase.h"

// CPropertyStaticText 대화 상자입니다.

class CPropertyStaticText : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyStaticText)

public:
	CPropertyStaticText(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyStaticText();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_STATICTEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	BOOL	m_bWebLink;
	CString	m_strCaption;

};
