
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

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