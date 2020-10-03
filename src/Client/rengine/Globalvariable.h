
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

#pragma once

#include "PreComplie.h"

class CGlobalData : public CSingleTonBase<CGlobalData>
{
protected:
	float m_fCurrentFrameTime;

public:

	CGlobalData(const tstring& name = _XTT("CGlobalData")) : CSingleTonBase(name)
	{
		Initialize();
	}

	~CGlobalData()
	{
	}

	WARP_RESULT_ENUM Release()
	{
		return CWARPResult::OK();
	}

public:

	WARP_RESULT_ENUM Initialize()
	{
		m_fCurrentFrameTime = 0.0f;
		Release();
		return  WARP_RESULT_ENUM::OK;
	}

	void SetCurrentFrameTime(const float frameTime)
	{ 
		m_fCurrentFrameTime = frameTime;
	}

	const float GetCurrentFrameTime() const
	{
		return m_fCurrentFrameTime; 
	}

};	