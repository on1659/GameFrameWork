
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

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

	virtual void UpdateShaderState();		// CCamera::UpdateShaderStateȣ�� �� �ؾ��Ѵ�. 

	virtual void Rotate(const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f);
	virtual void Update(const float& fTime);
};