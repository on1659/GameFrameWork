
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

//
#define _XTT(X)  TEXT(X)
#define FAILED(hr) (((HRESULT)(hr)) < 0)
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)

//
#define  V_RETURN(x)    \
{\
	hr = (x); if( FAILED(hr) ) \
	{ \
		return hr; \
	} \
}

//
inline std::wstring AnsiToWString(const std::string& str)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
	return std::wstring(buffer);
}

#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw DxException(hr__, L#x, wfn, __LINE__); } \
}


#define enum_def(N) \
namespace N{ enum T 
#define enum_end ; }
#define ERR_INFO __FILE__, __LINE__
#define ERROR_INFO ERR_INFO

#define SharPtr(T) std::shared_ptr<T>
#define UNIPtr(T) std::unique_ptr<T>

#define MakeShardPtr(T)  std::make_shared<T>()
#define MakeUniPtr(T)	 std::make_unique<T>()()

namespace Radar
{
	static void c_blue() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000b); }
	static void c_red() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000c); }
	static void c_white() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000f); }
	static void c_default() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); }

}