
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#define WINDOWS_WIDTH						640
#define WINDOWS_HEIGHT						480

#define FRAME_BUFFER_WIDTH					WINDOWS_WIDTH
#define FRAME_BUFFER_HEIGHT					WINDOWS_HEIGHT
#define ASPECT_RATIO						(float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT))

#define SHADOW_RENDER_TARGET_WIDTH			WINDOWS_WIDTH
#define SHADOW_RENDER_TARGET_HEIGHT			WINDOWS_HEIGHT


#define GameFrameWork						CGameFrameWork::GetInstance()
#define INPUT								CInputManager::GetInstance()
#define TIMER								CGameTimer::GetInstance()
#define GLOBAL_VARIABLE						CGlobalData::GetInstance()
#define gCamera								CCamera::GetInstance()
#define gFRAME_TIME							CGlobalData::GetInstance()->GetCurrentFrameTime()

#define gDevice								CGlobalData::GetInstance()->GetDevice()
#define gSetDevice(X)						CGlobalData::GetInstance()->SetDevice(X)

#define setCBSrcDescriptorIncrementSize(X)	CGlobalData::GetInstance()->SetCBSrvDescriptorIncrementSize(X)
#define getCBSrcDescriptorIncrementSize		CGlobalData::GetInstance()->GetCBSrvDescriptorIncrementSize();

#define gCommandALlocator					CGlobalData::GetInstance()->GetCommandAllocator()
#define gCommandQueue						CGlobalData::GetInstance()->GetCommandQueue()
#define gGraphicsCommandList				CGlobalData::GetInstance()->GetGraphicsCommandList()


#define DEFAULT_MESH_SIZE		5
#define DEFAULT_WORLD_SIZE		256.0f

//
#define DEFAULT_AABB_SIZE 10

//
#define RNDER_TARGET_NUM	3

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

#define RANDOM_COLOR	XMFLOAT4(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX))

