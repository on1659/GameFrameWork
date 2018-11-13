
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once
#include "Camera.h"


class CFreeCamera :public CCamera
{
public:
	CFreeCamera(const tstring& name = _XTT("FreeCamera"));
	~CFreeCamera() {}

	virtual WARP_RESULT_ENUM Start() override;
	virtual WARP_RESULT_ENUM Release() override;

	virtual void SetShaderState();
	virtual void CleanShaderState() { }

	virtual void UpdateShaderState();		// CCamera::UpdateShaderState호출 꼭 해야한다. 

	virtual void Rotate(const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f);
	virtual void Update(const float& fTime);
};