
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#include "PreComplie.h"

class CGlobalvariable : public CSingleTonBase<CGlobalvariable>
{
protected:
	tstring								m_CommandLine;

	ComPtr<D3DDevice>					m_pd3dDevice;
	ComPtr<ID3D12CommandAllocator>		m_pd3dCommandAllocator;
	ComPtr<ID3D12CommandQueue>			m_pd3dCommandQueue;
	ComPtr<ID3D12GraphicsCommandList>	m_pd3dCommandList;
	ComPtr<ID3D12Fence>					m_pd3dFence;

	unsigned int				m_nCbvSrvDescriptorIncrementSize;

public:

	CGlobalvariable(const tstring& name = _XTT("CGlobalvariable")) : CSingleTonBase(name)
	{
		Initialize();
	}

	~CGlobalvariable()
	{
		if (m_pd3dDevice)
			m_pd3dDevice->Release();
		if (m_pd3dCommandAllocator)
			m_pd3dCommandAllocator->Release();
		if (m_pd3dCommandQueue)
			m_pd3dCommandQueue->Release();
		if (m_pd3dCommandList)
			m_pd3dCommandList->Release();
		if (m_pd3dFence)
			m_pd3dFence->Release();
	}

	WARP_RESULT_ENUM Release()
	{
		return CWARPResult::OK();
	}

public:

	WARP_RESULT_ENUM Initialize()
	{
		Release();
		return  WARP_RESULT_ENUM::OK;
	}
	void SetDevice(D3DDevice* pd3dDevice){ m_pd3dDevice = pd3dDevice; }
	D3DDevice*	GetDevice() { return m_pd3dDevice.Get(); }

	void SeCommandAllocator(ComPtr<ID3D12CommandAllocator> pCommandAllocator)			 { m_pd3dCommandAllocator = pCommandAllocator; }
	void SetCommandQueue(ComPtr<ID3D12CommandQueue> pCommandQueue)						 { m_pd3dCommandQueue = pCommandQueue; }
	void SetGraphicsCommandList(ComPtr<ID3D12GraphicsCommandList> pGrahpicsCommandList) { m_pd3dCommandList = pGrahpicsCommandList; }
	void SetCommandLine(LPWSTR commandLine) { m_CommandLine = commandLine; }

	ID3D12CommandAllocator*		GetCommandAllocator()									 { return m_pd3dCommandAllocator.Get(); }
	ID3D12CommandQueue*			GetCommandQueue()										 { return m_pd3dCommandQueue.Get(); }
	ID3D12GraphicsCommandList*	GetGraphicsCommandList() { return m_pd3dCommandList.Get(); }
	const tstring				GetCommandLineMsg() { return m_CommandLine; }

	void						SetCBSrvDescriptorIncrementSize(const unsigned int size) { m_nCbvSrvDescriptorIncrementSize = size; }
	unsigned int				GetCBSrvDescriptorIncrementSize() const { return m_nCbvSrvDescriptorIncrementSize;}

};	