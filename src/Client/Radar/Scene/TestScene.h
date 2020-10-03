
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#include "SceneState.h"

class CTestScene : public RSceneState
{
public:

	CTestScene(const tstring& name);
    ~CTestScene();

	virtual void Start(HWND hWnd, HINSTANCE m_hInstance, int nWndClientWidth, int nWndClientHeight);

	virtual void Exit();

	virtual void Pause();

	virtual void Resume();

	//Render & Logic
	virtual void OnDraw(HDC hdc);

	virtual void OnUpdate(const float fTimeElapsed);
};
