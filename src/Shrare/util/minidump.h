
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

#pragma once

#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <DbgHelp.h>
#include "Util.h"

/*
	���α׷� crash Ȯ��
*/


typedef BOOL(WINAPI *MINIDUMPWRITEDUMP)
(
	// Callback �Լ��� ����
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

	// Windows 2000 �������µ���DBGHELP�������ؼ��������־���Ѵ�.
	DllHandle = LoadLibrary(TEXT("DBGHELP.DLL"));

	if (DllHandle)
	{
		auto result = MessageBox(NULL, TEXT("Dump ���� ����ǲ�����?"), TEXT(" - Error - "), MB_OKCANCEL);

		if (result == IDCANCEL) return EXCEPTION_EXECUTE_HANDLER;

		//MiniDumpWriteDump �Լ��� �ּҸ� ���ͼ� ȣ��
		MINIDUMPWRITEDUMP Dump = (MINIDUMPWRITEDUMP)GetProcAddress(DllHandle, "MiniDumpWriteDump");

		if (Dump)
		{
			TCHAR		DumpPath[MAX_PATH] = { 0, };
			SYSTEMTIME	SystemTime;

			GetLocalTime(&SystemTime);

			//���� �׾����� Ȯ��
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

				//Dump�� ���� �����
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

		//�ױ����� UnHandledExceptionFilter �Լ��� ȣ���ϰ� ���� ��
		PreviousExceptionFilter = SetUnhandledExceptionFilter(UnHandledExceptionFilter);

		return true;
	}

	static bool End()
	{
		SetUnhandledExceptionFilter(PreviousExceptionFilter);

		return true;
	}
};