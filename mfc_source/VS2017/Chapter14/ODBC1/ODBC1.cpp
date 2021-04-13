// ODBC1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "ODBC1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

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
			// TODO: 여기에 애플리케이션 동작을 코딩합니다.
			wprintf(L"심각한 오류: MFC 초기화 실패\n");
			nRetCode = 1;
		}
		else
		{
			_tsetlocale(LC_ALL, _T("")); // 유니코드 한국어 출력에 필요

			// ❶ 데이터베이스 객체 생성
			CDatabase db;
			db.OpenEx(_T("DSN=student"), 0);

			// ❷ 레코드셋 객체 생성
			CRecordset rs(&db);
			rs.Open(CRecordset::dynaset, _T("SELECT * FROM 테이블1"));

			// ❸ 데이터 출력
			CString str;
			while (!rs.IsEOF()) {
				rs.GetFieldValue(short(0), str);
				_tprintf(_T("%s "), (LPCTSTR)str);
				rs.GetFieldValue(short(1), str);
				_tprintf(_T("%s "), (LPCTSTR)str);
				rs.GetFieldValue(short(2), str);
				_tprintf(_T("%s "), (LPCTSTR)str);
				rs.GetFieldValue(short(3), str);
				_tprintf(_T("%s\n"), (LPCTSTR)str);
				rs.MoveNext();
			}

			// ❹ 종료 처리
			rs.Close();
			db.Close();
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
