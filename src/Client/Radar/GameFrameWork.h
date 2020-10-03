#pragma once

// https://code-examples.net/ko/q/8d0b80
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

class CGameTimer;

class CGameFrameWork
	: public CSingleTonBase<CGameFrameWork>
{

public:
	CGameFrameWork(tstring name = _XTT("CGameFrameWork"));

	~CGameFrameWork();
	
	virtual WARP_RESULT_ENUM Initialize() override;

	virtual WARP_RESULT_ENUM Start(void* pdata) override;

	virtual WARP_RESULT_ENUM LateStart()override;

	virtual WARP_RESULT_ENUM Reset() override;

	virtual WARP_RESULT_ENUM Release() override;

	void PreUpdate();

	void Update();

	void Render();

	WARP_RESULT_ENUM OnResizeBackBuffers(const WORD width, const WORD height);

private:
	HINSTANCE						m_hInstance;
	HWND							m_hWnd;
	RECT							m_rcClient;
	int								m_nWndClientWidth;
	int								m_nWndClientHeight;

	int lastTerm{ 0 };
	int lastValue{ 0 };

};

