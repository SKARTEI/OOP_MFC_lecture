#pragma once

#include "PropertyBase.h"

class CMyComboBox;

// CPropertyIPAddress 대화 상자입니다.

class CPropertyIPAddress : public CPropertyBase
{
	DECLARE_DYNAMIC(CPropertyIPAddress)

public:
	CPropertyIPAddress(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertyIPAddress();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPERTY_IPADDRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CComboBox		m_ctrlCombo;
	int				m_iAction;
	CMyComboBox	*	m_pCombo;

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();

};
