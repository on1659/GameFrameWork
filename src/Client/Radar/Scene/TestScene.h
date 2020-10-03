
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

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
