#pragma once

#include "PropertyBase.h"

// CPropertyButton 대화 상자입니다.

class CPropertyButton : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyButton)

public:
	CPropertyButton(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyButton();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_BUTTON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CString m_strCaption;
	CString m_strPath;
	int m_iAction;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPath();
	afx_msg void OnRadio(UINT nID);

};
