#pragma once

#include "PropertyBase.h"

// CPropertyPicture 대화 상자입니다.

class CPropertyPicture : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyPicture)

public:
	CPropertyPicture(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyPicture();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_PICTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CString	m_strPath;
	int		m_iAction;

public:
	afx_msg void OnBnClickedButtonPath();

};
