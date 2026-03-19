
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#include <string.h>

static unsigned int gInstanceID = 0;

class Object //: public CMemoryPool<Object>
{

public:
	Object(const tstring& name = _XTT("Default_Object")) 
		: name(name)
		, nGID(gInstanceID++)
		, tag(0)
		, layer(0)
		, m_xmMatrix(DirectX::XMMatrixIdentity())
		, m_xmVector(DirectX::XMVectorZero())
		, m_xmFloat3(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))

	{
	}

	Object(const Object& other) 
	{
		nGID		= other.nGID;
		name		= other.name;
		tag			= other.tag;
		layer		= other.layer;
		m_xmMatrix	= other.m_xmMatrix;
		m_xmVector	= other.m_xmVector;
		m_xmFloat3	= other.m_xmFloat3;
	}

	virtual ~Object() {}

	virtual WARP_RESULT_ENUM Start() { isStart_ = true;  return CWARPResult::OK(); }
	virtual WARP_RESULT_ENUM Start(void* pData) { isStart_ = true;  return CWARPResult::OK(); }
	virtual WARP_RESULT_ENUM Initialize() { return CWARPResult::OK(); }
	virtual WARP_RESULT_ENUM Reset() { return CWARPResult::OK(); }

#ifdef _ADD_LATE_CREATE_START_
	virtual WARP_RESULT_ENUM LateStart() { return CWARPResult::OK(); }
	virtual WARP_RESULT_ENUM LateStart(void* pData) { return CWARPResult::OK(); }
#endif // _ADD_LATE_CREATE_START_

	virtual WARP_RESULT_ENUM Release() { return CWARPResult::OK(); }

	void setName(tstring& input_name) { name = input_name; }
	tstring& getName() { return name; }

	  void setTag(const unsigned int& input_tag)	{   tag = input_tag; }
	void setLayer(const unsigned int& input_layer)  { layer = input_layer; }

	const unsigned int&   getTag() { return tag; };
	const unsigned int& getLayer() { return layer; };

public:
	//KYT '16.07.26
	/*
		GameObject Global ID;
	*/
	unsigned int					nGID{ 0 };
	tstring							name;
	unsigned int					tag{ 0U };
	unsigned int					layer{ 0U };

protected:
	XMMATRIX						m_xmMatrix;
	XMVECTOR						m_xmVector;
	XMFLOAT3						m_xmFloat3;

private:
	bool							isStart_{ false };

protected:
	const bool& isStart() const { return isStart_; }

};



//private:	
//	int								m_nReferences;
//
//public:
//	void AddRef() { m_nReferences++; }
//
//	void Release(){	if (--m_nReferences <= 0) delete this; }

//Object(const Object&& other)
//{
//	nGID		= other.nGID;
//	name.assign(other.name);;
//	tag			= other.tag;
//	layer		= other.layer;
//	m_xmMatrix	= other.m_xmMatrix;
//	m_xmVector	= other.m_xmVector;
//	m_xmFloat3	= other.m_xmFloat3;
//}
