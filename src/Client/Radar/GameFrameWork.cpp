
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.


#include "PreComplie.h"
#include "GameFrameWork.h"

CGameFrameWork::CGameFrameWork(tstring name) : CSingleTonBase(name)
{
	Initialize();
}

CGameFrameWork::~CGameFrameWork()
{
}

WARP_RESULT_ENUM CGameFrameWork::Initialize()
{
	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::Start(void* pData)
{
	// _tcscpy_s(m_pszBuffer, _T("DirectX 11 ("));
	FrameWorkStartData *data = reinterpret_cast<FrameWorkStartData*>(pData);

	if (nullptr == data)
	{
		MessageBox(nullptr, _XTT("Program Exit"), _XTT("FrameWork_Start_Error"), MB_OK);
		return CWARPResult::FAIL(ERR_INFO);
	}

	m_hInstance = data->instance;
	m_hWnd = data->hwnd;
	GetClientRect(m_hWnd, &m_rcClient);

	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::LateStart()
{
	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::Reset()
{
	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::Release()
{
	return WARP_RESULT_ENUM::OK;
}

void CGameFrameWork::PreUpdate()
{
	if (INPUT->KeyUp(WP_Q))
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);

	TIMER->Tick(60);
	INPUT->Update((float)TIMER->GetFrameRate());
}

void CGameFrameWork::Update()
{
}

void CGameFrameWork::Render()
{
	_TCHAR   pszFrameRate[50] = { NULL };
	TIMER->GetFrameRate(pszFrameRate, 37);
	::SetWindowText(m_hWnd, pszFrameRate);
}

WARP_RESULT_ENUM CGameFrameWork::OnResizeBackBuffers(const WORD width, const WORD height)
{
	return WARP_RESULT_ENUM::OK;
}
