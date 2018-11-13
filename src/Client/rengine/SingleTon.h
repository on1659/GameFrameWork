#pragma once

/*
---------------------------------------------------------------------------------------
	�̱��� ���ø� Ŭ����
---------------------------------------------------------------------------------------
*/

// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

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

////�̱��� �ν��Ͻ� �ʱ�ȭ
//template <class Type>
//Type* CSingleTonBase<Type>::m_sInstance = nullptr;
