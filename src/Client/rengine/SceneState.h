#pragma once

/*
---------------------------------------------------------------------------------------
	싱글톤 템플릿 클레스
---------------------------------------------------------------------------------------
*/

// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

//InterFace
class RSceneState
{

protected:
	HWND								m_hWnd;
	HINSTANCE							m_hInstance;
	tstring								m_name;
	int									m_width;
	int									m_height;

public:
	RSceneState(const tstring& name) : m_name(name) {};

	virtual ~RSceneState() {}

	virtual void Start(HWND hWnd, HINSTANCE m_hInstance, int nWndClientWidth, int nWndClientHeight) = 0;

	virtual void Exit() = 0;

	virtual void Pause() = 0;

	virtual void Resume() = 0;

	//Render & Logic
	virtual void OnDraw(HDC hdc) = 0;

	virtual void OnUpdate(const float fTimeElapsed) = 0;


	//Call
	virtual void onEvent(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
	{

	}

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
	{

	}

	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
	{

	}

};

