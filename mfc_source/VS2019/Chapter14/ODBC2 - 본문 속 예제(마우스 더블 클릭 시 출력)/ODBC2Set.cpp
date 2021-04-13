
// ODBC2Set.cpp : CODBC2Set 클래스의 구현
//

#include "stdafx.h"
#include "ODBC2.h"
#include "ODBC2Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CODBC2Set 구현

IMPLEMENT_DYNAMIC(CODBC2Set, CRecordset)

CODBC2Set::CODBC2Set(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ST_NUM = 0;
	m_ST_NAME = L"";
	m_ST_MAN = FALSE;
	m_ST_PHONE = L"";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CODBC2Set::GetDefaultConnect()
{
	return _T("DSN=student;DBQ=C:\\SOURCE\\VS2019\\CHAPTER14\\student.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CODBC2Set::GetDefaultSQL()
{
	return _T("[테이블1]");
}

void CODBC2Set::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Long(pFX, _T("[ST_NUM]"), m_ST_NUM);
	RFX_Text(pFX, _T("[ST_NAME]"), m_ST_NAME);
	RFX_Bool(pFX, _T("[ST_MAN]"), m_ST_MAN);
	RFX_Text(pFX, _T("[ST_PHONE]"), m_ST_PHONE);
}
/////////////////////////////////////////////////////////////////////////////
// CODBC2Set 진단

#ifdef _DEBUG
void CODBC2Set::AssertValid() const
{
	CRecordset::AssertValid();
}

void CODBC2Set::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

