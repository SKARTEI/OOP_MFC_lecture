#pragma once

class CPropertyBase : public CDialog
{
public:
	CPropertyBase( UINT nIDTemplate, CWnd* pParent = NULL );
	virtual ~CPropertyBase(void);

public:
	BOOL Create( CWnd *pParentWnd );

protected:
	virtual void OnOK();
	virtual void OnCancel();

private:
	UINT m_nIDTemplate;

};
