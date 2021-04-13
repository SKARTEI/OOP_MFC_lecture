// OLEDB1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OLEDB1.h"
#include "CStudent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 응용 프로그램 개체입니다.

CWinApp theApp;

using namespace std;

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: 오류 코드를 필요에 따라 수정합니다.
			wprintf(L"심각한 오류: MFC를 초기화하지 못했습니다.\n");
			nRetCode = 1;
		}
		else
		{
			CoInitialize(NULL); // COM 초기화
			_tsetlocale(LC_ALL, _T(""));

			HRESULT hr; // COM 오류 저장
			CStudent* m_pSet = new CStudent();

			hr = m_pSet->OpenAll();
			if (FAILED(hr)) {
				AfxMessageBox(_T("레코드 집합을 열지 못했습니다."), MB_OK);
			}


#if 0
			m_pSet->MoveLast(); // 맨 끝으로 이동한다.

			// 레코드 추가 전에 반드시 상태 변수를 초기화해야 한다!
			m_pSet->m_dwST_NUMStatus = DBSTATUS_S_OK;
			m_pSet->m_dwST_NAMEStatus = DBSTATUS_S_OK;
			m_pSet->m_dwST_MANStatus = DBSTATUS_S_OK;
			m_pSet->m_dwST_PHONEStatus = DBSTATUS_S_OK;

			// 문자열과 같은 가변 필드는 길이를 초기화해야 한다!
			m_pSet->m_dwST_NAMELength = sizeof(_T("권석훈"));
			m_pSet->m_dwST_PHONELength = sizeof(_T("010-1234-5678"));

			// 필드 변수에 새로운 레코드의 필드 값을 넣는다.
			m_pSet->m_ST_NUM = 3010;
			wsprintf(m_pSet->m_ST_NAME, _T("권석훈"));
			m_pSet->m_ST_MAN = -1;
			wsprintf(m_pSet->m_ST_PHONE, _T("010-1234-5678"));

			// 레코드를 추가한다.
			hr = m_pSet->Insert();
			if (FAILED(hr)) {
				AfxMessageBox(_T("레코드를 추가하지 못했습니다."), MB_OK);
			}
#endif
#if 0
			m_pSet->MoveLast(); // 맨 끝으로 이동한다.

			// 레코드 변경 전에 반드시 상태 변수를 초기화해야 한다!
			m_pSet->m_dwST_NUMStatus = DBSTATUS_S_OK;
			m_pSet->m_dwST_NAMEStatus = DBSTATUS_S_OK;
			m_pSet->m_dwST_MANStatus = DBSTATUS_S_OK;
			m_pSet->m_dwST_PHONEStatus = DBSTATUS_S_OK;

			// 문자열과 같은 가변 필드는 길이를 초기화해야 한다!
			m_pSet->m_dwST_PHONELength = sizeof(_T("010-5678-1234"));

			// 필드 변수에 변경할 레코드의 필드 값을 넣는다.
			wsprintf(m_pSet->m_ST_PHONE, _T("010-5678-1234"));

			// 레코드를 변경한다.
			hr = m_pSet->SetData();
			if (FAILED(hr)) {
				AfxMessageBox(_T("레코드를 변경하지 못했습니다."), MB_OK);
			}
#endif
#if 0
			m_pSet->MoveLast(); // 맨 끝으로 이동한다.

			// 레코드를 삭제한다.
			hr = m_pSet->Delete();
			if (FAILED(hr)) {
				AfxMessageBox(_T("레코드를 삭제하지 못했습니다."), MB_OK);
			}
#endif


			m_pSet->MoveFirst();
			do {
				_tprintf(_T("%d %s %2d %s\n"),
					m_pSet->m_ST_NUM,
					m_pSet->m_ST_NAME,
					m_pSet->m_ST_MAN,
					m_pSet->m_ST_PHONE);
			} while (m_pSet->MoveNext() == S_OK);

			m_pSet->CloseAll();

			delete m_pSet;
			CoUninitialize(); // COM 종료
		}
	}
	else
	{
		// TODO: 오류 코드를 필요에 따라 수정합니다.
		wprintf(L"심각한 오류: GetModuleHandle 실패\n");
		nRetCode = 1;
	}

	return nRetCode;
}
