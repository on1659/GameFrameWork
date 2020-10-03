
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

#pragma once

#include <string.h>

static uint32 gInstanceID = 0;

class Object //: public CMemoryPool<Object>
{

public:
	Object(const tstring& name = _XTT("Default_Object")) 
		: name(name)
		, nGID(gInstanceID++)
		, tag(0U)
		, layer(0U)
		, isStart_(false)
	{
	}

	Object(const Object& other) 
	{
		nGID		= other.nGID;
		name		= other.name;
		tag			= other.tag;
		layer		= other.layer;
	}

	virtual ~Object() {}

	virtual WARP_RESULT_ENUM Start() { isStart_ = true;  return WARP_RESULT_ENUM::OK; }
	virtual WARP_RESULT_ENUM Start(void* pData) { isStart_ = true;  return WARP_RESULT_ENUM::OK; }
	virtual WARP_RESULT_ENUM Initialize() { return WARP_RESULT_ENUM::OK; }
	virtual WARP_RESULT_ENUM Reset() { return WARP_RESULT_ENUM::OK; }

	virtual WARP_RESULT_ENUM LateStart() { return WARP_RESULT_ENUM::OK; }
	virtual WARP_RESULT_ENUM LateStart(void* pData) { return WARP_RESULT_ENUM::OK; }

	virtual WARP_RESULT_ENUM Release() { return WARP_RESULT_ENUM::OK; }

	void setName(tstring& input_name) { name = input_name; }
	tstring& getName() { return name; }

	void setTag(const uint32& input_tag)	{   tag = input_tag; }
	void setLayer(const uint32& input_layer)  { layer = input_layer; }

	const uint32&   getTag() { return tag; };
	const uint32& getLayer() { return layer; };

public:
	//KYT '16.07.26
	/*
		GameObject Global ID;
	*/
	uint32					nGID;
	tstring					name;
	uint32					tag;
	uint32					layer;

protected:
	// xm �Լ��� ��ȯ �� ���Ͽ�
	XMMATRIX						m_xmMatrix;
	XMVECTOR						m_xmVector;
	XMFLOAT3						m_xmFloat3;

private:
	bool							isStart_;

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
