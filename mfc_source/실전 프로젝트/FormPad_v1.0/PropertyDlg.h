#pragma once

#include "PropertyBase.h"

// CPropertyDlg 대화 상자입니다.

class CPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropertyDlg)

public:
	CPropertyDlg( CPropertyBase *pDlg, CWnd* pParent = NULL );   // 표준 생성자입니다.
	virtual ~CPropertyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONTROL_PROPERTY };

protected:
	CPropertyBase	*	m_pChildDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
