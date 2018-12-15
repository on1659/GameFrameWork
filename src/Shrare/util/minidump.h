
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <DbgHelp.h>
#include "Util.h"

/*
	프로그램 crash 확인
*/


typedef BOOL(WINAPI *MINIDUMPWRITEDUMP)
(
	// Callback 함수의 원형
	HANDLE hProcess,
	DWORD dwPid,
	HANDLE hFile,
	MINIDUMP_TYPE DumpType,
	const PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
	const PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
	const PMINIDUMP_CALLBACK_INFORMATION CallbackParam
	);

LPTOP_LEVEL_EXCEPTION_FILTER PreviousExceptionFilter = nullptr;

LONG __stdcall UnHandledExceptionFilter(struct _EXCEPTION_POINTERS *exceptionInfo)
{
	HMODULE	DllHandle = nullptr;

	// Windows 2000 이전에는따로DBGHELP를배포해서설정해주어야한다.
	DllHandle = LoadLibrary(TEXT("DBGHELP.DLL"));

	if (DllHandle)
	{
		auto result = MessageBox(NULL, TEXT("Dump 파일 만드실껀가요?"), TEXT(" - Error - "), MB_OKCANCEL);

		if (result == IDCANCEL) return EXCEPTION_EXECUTE_HANDLER;

		//MiniDumpWriteDump 함수의 주소를 얻어와서 호출
		MINIDUMPWRITEDUMP Dump = (MINIDUMPWRITEDUMP)GetProcAddress(DllHandle, "MiniDumpWriteDump");

		if (Dump)
		{
			TCHAR		DumpPath[MAX_PATH] = { 0, };
			SYSTEMTIME	SystemTime;

			GetLocalTime(&SystemTime);

			//언제 죽었는지 확인
			_sntprintf_s(
				DumpPath, MAX_PATH, _T("../Assets/08.Dump/%d-%d-%d %d_%d_%d.dmp"),
				SystemTime.wYear,
				SystemTime.wMonth,
				SystemTime.wDay,
				SystemTime.wHour,
				SystemTime.wMinute,
				SystemTime.wSecond
			);

			HANDLE FileHandle = CreateFile
			(
				DumpPath,
				GENERIC_WRITE,
				FILE_SHARE_WRITE,
				NULL, CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

			if (FileHandle != INVALID_HANDLE_VALUE)
			{
				_MINIDUMP_EXCEPTION_INFORMATION MiniDumpExceptionInfo;

				MiniDumpExceptionInfo.ThreadId = GetCurrentThreadId();
				MiniDumpExceptionInfo.ExceptionPointers = exceptionInfo;
				MiniDumpExceptionInfo.ClientPointers = NULL;

				//Dump에 정보 씌우기
				BOOL Success = Dump(
					GetCurrentProcess(),
					GetCurrentProcessId(),
					FileHandle,
					MiniDumpNormal,
					&MiniDumpExceptionInfo,
					NULL,
					NULL);
				if (Success)
				{
					CloseHandle(FileHandle);

					std::string temp;
					std::string express = std::string("");
					std::string title = std::string("Dump Make Succ");

					std::wstring wstr;
					wstr = DumpPath;
					express.assign(wstr.begin(), wstr.end());
					express += "\n File :";

					Radar::getFileName(temp, __FILE__);
					express += temp;

					Radar::getFileExt(temp, __FILE__);
					express += temp;

					temp.clear();
					int line = __LINE__;
					express += "\n Line : ";
					express += std::to_string(line);


					MessageBoxA(NULL, express.c_str(), title.c_str(), MB_OK);

					return EXCEPTION_EXECUTE_HANDLER;
				}
			}
			MessageBox(NULL, TEXT("Dump Make Error"), TEXT(" - Error - "), MB_ICONHAND);
			CloseHandle(FileHandle);


		}
		else
		{
			 MessageBox(NULL, TEXT("Dump Make Error"), TEXT(" - Error - "), MB_ICONHAND);
		}
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

class CMiniDump
{
public:
	static bool Start()
	{
		SetErrorMode(SEM_FAILCRITICALERRORS);

		//죽기전에 UnHandledExceptionFilter 함수를 호출하고 죽을 것
		PreviousExceptionFilter = SetUnhandledExceptionFilter(UnHandledExceptionFilter);

		return true;
	}

	static bool End()
	{
		SetUnhandledExceptionFilter(PreviousExceptionFilter);

		return true;
	}
};