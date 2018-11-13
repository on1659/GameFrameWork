
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

// using
using D3DDevice		 = ID3D12Device;
using D3DBuffer		 = ID3D12Resource;
using D3DFactory	 = IDXGIFactory4;
using DXGISSwapChain = IDXGISwapChain3;
using DX_VIEWPORT	 = D3D12_VIEWPORT;
using DX_RECT	     = D3D12_RECT;
using Microsoft::WRL::ComPtr;

using float4 = struct { float x; float y; float z; float w; };
using float3 = struct { float x; float y; float z; };


#ifdef _UNICODE
	using tstring = std::wstring;
	#define tcout wcout
#else
	using tstring = std::string;
#	define tstring string
#	define tcout	cout
#endif

#define WINDOWS_WIDTH						640
#define WINDOWS_HEIGHT						480
	
#define FRAME_BUFFER_WIDTH					WINDOWS_WIDTH
#define FRAME_BUFFER_HEIGHT					WINDOWS_HEIGHT
#define ASPECT_RATIO						(float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT))

#define SHADOW_RENDER_TARGET_WIDTH			WINDOWS_WIDTH
#define SHADOW_RENDER_TARGET_HEIGHT			WINDOWS_HEIGHT


#define GameFrameWork			CGameFrameWork::GetInstance()
#define INPUT					CInputManager::GetInstance()
#define TIMER					CGameTimer::GetInstance()
#define GLOBAL_VARIABLE			CGlobalvariable::GetInstance()
#define gCamera					CCamera::GetInstance()
#define gFRAME_TIME				CGlobalvariable::GetInstance()->GetCurrentFrameTime()

#define gDevice					CGlobalvariable::GetInstance()->GetDevice()
#define gSetDevice(X)			CGlobalvariable::GetInstance()->SetDevice(X)

#define setCBSrcDescriptorIncrementSize(X) CGlobalvariable::GetInstance()->SetCBSrvDescriptorIncrementSize(X)
#define getCBSrcDescriptorIncrementSize		CGlobalvariable::GetInstance()->GetCBSrvDescriptorIncrementSize();

#define gCommandALlocator		CGlobalvariable::GetInstance()->GetCommandAllocator()
#define gCommandQueue			CGlobalvariable::GetInstance()->GetCommandQueue()
#define gGraphicsCommandList	CGlobalvariable::GetInstance()->GetGraphicsCommandList()


#define DEFAULT_MESH_SIZE		5
#define DEFAULT_WORLD_SIZE		256.0f

//
#define DEFAULT_AABB_SIZE 10


//
#define RNDER_TARGET_NUM	3

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

#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), IID_PPV_ARGS_Helper(ppType)

//
#define	SWAP_CHAIN_BUFFER_COUNT				2
#define	RENTER_TARGET_BUFFER_COUNT			2


#define enum_def(N) \
namespace N{ enum T 
#define enum_end ; }
#define ERR_INFO __FILE__, __LINE__
#define ERROR_INFO ERR_INFO

#define SharPtr(T) std::shared_ptr<T>
#define UNIPtr(T) std::unique_ptr<T>
	 
#define MakeShardPtr(T)  std::make_shared<T>()
#define MakeUniPtr(T)	 std::make_unique<T>()()

#define RANDOM_COLOR	XMFLOAT4(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX))



