
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once


//#define _FIRST_
class CCamera : public Object
{
	static CCamera* CamPtr;

public:

	CCamera(const tstring& name = _XTT("Camera"));
	~CCamera() { }
};
