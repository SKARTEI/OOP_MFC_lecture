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
