
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

#pragma once


//#define _FIRST_
class CCamera : public Object
{
	static CCamera* CamPtr;

public:

	CCamera(const tstring& name = _XTT("Camera"));
	~CCamera() { }
};
