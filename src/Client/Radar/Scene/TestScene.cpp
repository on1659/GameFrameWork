
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

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
