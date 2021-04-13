
// OLEDB2Set.h: COLEDB2Set 클래스의 인터페이스
//


#pragma once


class COLEDB2SetAccessor
{
public:
	LONG m_ST_NUM;
	TCHAR m_ST_NAME[256];
	VARIANT_BOOL m_ST_MAN;
	TCHAR m_ST_PHONE[256];

	// 다음 마법사 생성 데이터 멤버에는  열 맵의 해당 
	// 필드에 대한 상태 값이 들어 있습니다. 이 값을
	// 사용하여 데이터베이스에서반환하는 NULL 값을
	// 보유하거나 컴파일러에서 오류를 반환할 때
	// 오류 정보를 보유할 수 있습니다. 이러한 필드 사용에
	// 대한 자세한 내용은 Visual C++ 설명서의
	//  "마법사 생성 접근자"에서 "필드 상태 데이터 멤버"를 참조하십시오.
	// 참고: 데이터를 설정/삽입하기 전에 이들 필드를 초기화해야 합니다.

	DBSTATUS m_dwST_NUMStatus;
	DBSTATUS m_dwST_NAMEStatus;
	DBSTATUS m_dwST_MANStatus;
	DBSTATUS m_dwST_PHONEStatus;

	// 다음 마법사 생성 데이터 멤버에는 열 맵의 해당 필드에 대한
	// 길이 값이 들어 있습니다.
	// 참고: 가변 길이 열의 경우 데이터를 설정/삽입하기 전에 
	//       이러한 	 필드를 초기화해야 합니다.

	DBLENGTH m_dwST_NUMLength;
	DBLENGTH m_dwST_NAMELength;
	DBLENGTH m_dwST_MANLength;
	DBLENGTH m_dwST_PHONELength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY,
			DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
		hr = _db.OpenFromInitializationString(L"Provider=MSDASQL.1;Persist Security Info=False;Data Source=student;Extended Properties=\"DSN=student;DBQ=C:\\SOURCE\\VS2019\\CHAPTER14\\student.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;\"");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession& ()
	{
		return m_session;
	}

	CSession m_session;

	BEGIN_COLUMN_MAP(COLEDB2SetAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_ST_NUM, m_dwST_NUMLength, m_dwST_NUMStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_ST_NAME, m_dwST_NAMELength, m_dwST_NAMEStatus)
		_COLUMN_ENTRY_CODE(3, DBTYPE_BOOL, _SIZE_TYPE(m_ST_MAN), 0, 0, offsetbuf(m_ST_MAN), offsetbuf(m_dwST_MANLength), offsetbuf(m_dwST_MANStatus))
		COLUMN_ENTRY_LENGTH_STATUS(4, m_ST_PHONE, m_dwST_PHONELength, m_dwST_PHONEStatus)
	END_COLUMN_MAP()
};

class COLEDB2Set : public CTable<CAccessor<COLEDB2SetAccessor> >
{
public:
	HRESULT OpenAll()
	{
		HRESULT hr;
		hr = OpenDataSource();
		if (FAILED(hr))
			return hr;
		__if_exists(GetRowsetProperties)
		{
			CDBPropSet propset(DBPROPSET_ROWSET);
			__if_exists(HasBookmark)
			{
				if (HasBookmark())
					propset.AddProperty(DBPROP_IRowsetLocate, true);
			}
			GetRowsetProperties(&propset);
			return OpenRowset(&propset);
		}
		__if_not_exists(GetRowsetProperties)
		{
			__if_exists(HasBookmark)
			{
				if (HasBookmark())
				{
					CDBPropSet propset(DBPROPSET_ROWSET);
					propset.AddProperty(DBPROP_IRowsetLocate, true);
					return OpenRowset(&propset);
				}
			}
		}
		return OpenRowset();
	}

	HRESULT OpenRowset(DBPROPSET* pPropSet = NULL)
	{
		HRESULT hr = Open(m_session, L"테이블1", pPropSet);
#ifdef _DEBUG
		if (FAILED(hr))
			AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

	void CloseAll()
	{
		Close();
		CloseDataSource();
	}
};

