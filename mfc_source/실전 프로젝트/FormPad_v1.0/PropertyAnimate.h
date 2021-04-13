#pragma once

#include "PropertyBase.h"

// CPropertyAnimate 대화 상자입니다.

class CPropertyAnimate : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyAnimate)

public:
	CPropertyAnimate(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyAnimate();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_ANIMATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CString m_strPath;

public:
	afx_msg void OnBnClickedButtonPath();

};
