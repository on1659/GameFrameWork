
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.
 
#include "PreComplie.h"
#include "Camera.h"

CCamera* CCamera::CamPtr = nullptr;

CCamera::CCamera(const tstring& name)
	: Object(name)
{
}