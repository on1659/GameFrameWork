
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

#include "PreComplie.h"
#include "TestScene.h"

CTestScene::CTestScene(const tstring& name) : RSceneState(name)
{
}

CTestScene::~CTestScene()
{
}

void CTestScene::Start(HWND hWnd, HINSTANCE m_hInstance, int nWndClientWidth, int nWndClientHeight)
{
}

void CTestScene::Exit()
{
}

void CTestScene::Pause()
{
}

void CTestScene::Resume()
{
}

void CTestScene::OnDraw(HDC hdc)
{
	Draw_2D::drawRect(hdc, 100, 100, 20, RColor::RED);
}

void CTestScene::OnUpdate(const float fTimeElapsed)
{
}
