#pragma once

// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

class Sound;
class RSceneState;

class CGameFrameWork :public CSingleTonBase<CGameFrameWork>
{
private:
	std::vector<RSceneState*>		states;


	HINSTANCE						m_hInstance;
	HWND							m_hWnd;
	RECT							m_rcClient;

	//Render
	HDC								m_hdc;
	HBITMAP							m_hBitmapFrameBuffer;
	HBITMAP							m_hBitmapSelect;
	DWORD							m_bBackgroundColor;


	float							m_fTimeElapsed;
	int								m_nWndClientWidth;
	int								m_nWndClientHeight;


public:
	CGameFrameWork();

	~CGameFrameWork();

	//State 
	void SceneStart(RSceneState *pState);

	void SceneChangeState(RSceneState *pState);

	void SceneExit();

	void ScenePushState(RSceneState* pState);

	void ScenePopState();


	//Render & Logic & Init

	WARP_RESULT_ENUM Start(void* pData);

	void PreDraw(DWORD dwColor);

	void BeginDraw();

	void OnDraw();

	void EndDraw();

	void OnPreUpdate();

	void OnUpdate();

	void OnLateUpdate();

	void OnDestory();


	//Get
	int GetWindowWidth() { return m_nWndClientWidth; }

	int GetWindowHeight() { return m_nWndClientHeight - 70; }

};