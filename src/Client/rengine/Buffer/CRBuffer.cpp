#include "PreComplie.h"
#include "CRBuffer.h"


Buffer::Buffer()
{
}

Buffer::~Buffer()
{
	if (buffer)
		buffer->Release();
}

D3DBuffer* Buffer::operator=(D3DBuffer* rhs)
{
	buffer.Reset();
	buffer.Attach(rhs);
	return buffer.Get();
}

D3DBuffer* Buffer::operator()()
{
	return buffer.Get();
}



CRRenderTarget::CRRenderTarget() : Buffer()
{

}

CRRenderTarget::~CRRenderTarget()
{

}