
#include "PreComplie.h"
#include "GameFrameWork.h"
#include "SceneState.h"
#include "Scene/TestScene.h"
#include <time.h>

//#define _CONSOL_

CGameFrameWork::CGameFrameWork()
{
	m_hdc = nullptr;;
	m_hBitmapFrameBuffer = nullptr;;
	m_hBitmapSelect = nullptr;;
	m_hInstance = nullptr;;
	m_hWnd = nullptr;;
	m_bBackgroundColor = 0x00FFFFFF;
}

CGameFrameWork::~CGameFrameWork()
{
	while (!states.empty()) 
	{
		states.back()->Exit();
		states.pop_back();
	}
}


//State

void CGameFrameWork::SceneStart(RSceneState *state)
{
	srand((uint32)time(nullptr));
	states.push_back(state);
	states.back()->Start(m_hWnd, m_hInstance, m_nWndClientWidth, m_nWndClientHeight);
}

void CGameFrameWork::SceneChangeState(RSceneState *pState)
{
	if (!states.empty())
	{
		states.back()->Exit();
		states.pop_back();
	}

	states.push_back(pState);

	states.back()->Start(m_hWnd, m_hInstance, m_nWndClientWidth, m_nWndClientHeight);

}

void CGameFrameWork::SceneExit()
{
	RESOURCE->Release();
	//SOUNDMGR->ReleseInstance();

#ifdef _CONSOL_
	FreeConsole(); // Free Console Window
#endif 
}

void CGameFrameWork::ScenePushState(RSceneState* pState)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}
	// store and init the new state
	states.push_back(pState);
	states.back()->Start(m_hWnd, m_hInstance, m_nWndClientWidth, m_nWndClientHeight);

}

void CGameFrameWork::ScenePopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Exit();
		states.pop_back();
	}
	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}



//Render & Logic & Init

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


	srand((uint32)time(nullptr));

	//제일 먼저
	TIMER->Tick();						//타이머
	RESOURCE->LoadCImage();				//랜더매니저
	//SOUNDMGR->LoadSound();					//사운드매니저
	m_nWndClientWidth = FRAME_BUFFER_WIDTH;
	m_nWndClientHeight = FRAME_BUFFER_HEIGHT;

 	SceneStart(new CTestScene(_XTT("CTestScene")));

	return WARP_RESULT_ENUM::OK;
}

void CGameFrameWork::PreDraw(DWORD dwColor)
{
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hdc, hBrush);
	::Rectangle(m_hdc, 0, 0, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, hOldBrush);
	::DeleteObject(hBrush);
}

void CGameFrameWork::BeginDraw()
{
	HDC hDC = ::GetDC(m_hWnd);

	if (!m_hdc)
		m_hdc = ::CreateCompatibleDC(hDC);
	if (m_hBitmapFrameBuffer)
	{
		::SelectObject(m_hdc, nullptr);
		::DeleteObject(m_hBitmapFrameBuffer);
		m_hBitmapFrameBuffer = nullptr;;
	}

	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hdc, TRANSPARENT);

}

void CGameFrameWork::OnDraw()
{
	if (states.empty())
		return;

	BeginDraw();

	states.back()->OnDraw(m_hdc);

	EndDraw();

}

void CGameFrameWork::EndDraw()
{
	HDC hDC = ::GetDC(m_hWnd);

	::BitBlt(hDC, 0, 0, m_nWndClientWidth, m_nWndClientHeight, m_hdc, 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);


}

void CGameFrameWork::OnPreUpdate()
{
}

void CGameFrameWork::OnUpdate()
{
	//::gotoxy(0, 0, "mouse(%d,%d)", INPUT->GetMousePoint().x, INPUT->GetMousePoint().y);

	TIMER->Tick(20);

	m_fTimeElapsed = TIMER->GetTimeElapsed();

	if (!states.empty())
	{
		states.back()->OnUpdate(m_fTimeElapsed);
	}
	// resume previous state
	else if (!states.empty()) {
		states.back()->OnUpdate(m_fTimeElapsed);
	}


	//SOUNDMGR->OnUpdate();
}

void CGameFrameWork::OnLateUpdate()
{
}

void CGameFrameWork::OnDestory()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Exit();
		states.pop_back();
	}
	// resume previous state
	if (!states.empty()) {
		states.back()->Exit();
	}
	SceneExit();

	cout << "Exit" << endl;
}
