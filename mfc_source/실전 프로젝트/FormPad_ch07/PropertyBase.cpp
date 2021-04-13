#include "pch.h"
#include "PropertyBase.h"


CPropertyBase::CPropertyBase( UINT nIDTemplate, CWnd* pParent /*=NULL*/ )
	: CDialog(nIDTemplate, pParent)
	, m_nIDTemplate(nIDTemplate)
{
}

CPropertyBase::~CPropertyBase(void)
{
}

BOOL CPropertyBase::Create(CWnd *pParentWnd)
{
	return CDialog::Create(m_nIDTemplate, pParentWnd);
}

void CPropertyBase::OnOK()
{
	CDialog *pDlg = (CDialog *)GetParent();
	pDlg->EndDialog( IDOK );
	CDialog::OnOK();
}

void CPropertyBase::OnCancel()
{
	CDialog *pDlg = (CDialog *)GetParent();
	pDlg->EndDialog( IDCANCEL );
	CDialog::OnCancel();
}
