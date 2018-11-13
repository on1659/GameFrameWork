#pragma once

/*
---------------------------------------------------------------------------------------
	싱글톤 템플릿 클레스
---------------------------------------------------------------------------------------
*/

// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma warning(disable: 4316)

template <class Type>
class CSingleTonBase : public Object
{

protected:
	CSingleTonBase(const tstring& name = _XTT("CSingleTonBase")) : Object(name) { }
	~CSingleTonBase() {};

public:
	static Type* GetInstance()
	{
		static Type instance;
		return &instance;
	}
};

////싱글턴 인스턴스 초기화
//template <class Type>
//Type* CSingleTonBase<Type>::m_sInstance = nullptr;
