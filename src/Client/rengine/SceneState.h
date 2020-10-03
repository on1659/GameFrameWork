#pragma once

/*
---------------------------------------------------------------------------------------
	�̱��� ���ø� Ŭ����
---------------------------------------------------------------------------------------
*/

// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

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

