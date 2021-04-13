// PropertyIPAddress.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "PropertyIPAddress.h"

#include "MainFrm.h"
#include "FormPadDoc.h"
#include "FormPadView.h"

#include "MyComboBox.h"
#include "MyIPAddress.h"


// CPropertyIPAddress 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyIPAddress, CPropertyBase)

CPropertyIPAddress::CPropertyIPAddress(CWnd* pParent /*=NULL*/)
	: CPropertyBase(CPropertyIPAddress::IDD, pParent)
	, m_iAction(0)
	, m_pCombo( NULL )
{
}

CPropertyIPAddress::~CPropertyIPAddress()
{
}

void CPropertyIPAddress::DoDataExchange(CDataExchange* pDX)
{
	CPropertyBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LIST, m_ctrlCombo);
	DDX_Radio(pDX, IDC_RADIO_ACTION, m_iAction);
}


BEGIN_MESSAGE_MAP(CPropertyIPAddress, CPropertyBase)
END_MESSAGE_MAP()


// CPropertyIPAddress 메시지 처리기입니다.


BOOL CPropertyIPAddress::OnInitDialog() 
{
	CPropertyBase::OnInitDialog();
	
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CFormPadDoc *pDoc = (CFormPadDoc *)pFrame->GetActiveDocument();

	CObList list;
	pDoc->LookUpControl( list, RUNTIME_CLASS(CMyComboBox) );
	POSITION pos = list.GetHeadPosition();
	CString str;
	int iIndex;

	while ( pos != NULL )
	{
		CMyComboBox *pCombo = (CMyComboBox *)list.GetNext( pos );
		str.Format( _T("%s - %p"), pCombo->GetName(), pCombo );
		iIndex = m_ctrlCombo.AddString( str );
		if ( iIndex >= 0 )
			m_ctrlCombo.SetItemDataPtr( iIndex, pCombo );
	}

	CFormPadView *pView = (CFormPadView *)pFrame->GetActiveView();
	CObject *pObj = (CObject *)::GetWindowLongPtr( pView->GetSafeHwnd(), GWLP_USERDATA );
	if ( pObj != NULL )
	{
		CMyIPAddress *pIPAddress = (CMyIPAddress *)pObj;
		CMyComboBox *pCombo = pIPAddress->GetCurrentCombo();
		if ( pCombo != NULL )
		{
			str.Format( _T("%s - %p"), pCombo->GetName(), pCombo );
			m_ctrlCombo.SelectString(-1, str);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyIPAddress::OnOK() 
{
	int iIndex = m_ctrlCombo.GetCurSel();
	if ( iIndex >= 0 )
		m_pCombo = (CMyComboBox *)m_ctrlCombo.GetItemDataPtr( iIndex );
	else
		m_pCombo = NULL;

	CPropertyBase::OnOK();
}
