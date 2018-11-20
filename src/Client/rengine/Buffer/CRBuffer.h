#pragma once
class Buffer : public Object
{
private:
	ComPtr<D3DBuffer> buffer;

public:
	Buffer();
	virtual ~Buffer();

	D3DBuffer* operator=(D3DBuffer* rhs);
	D3DBuffer* operator()();
};

class CRRenderTarget : public Buffer
{
public:
	CRRenderTarget();
	virtual ~CRRenderTarget();
};

