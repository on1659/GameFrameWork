
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.


#include "PreComplie.h"
#include "GameFrameWork.h"
#include "FreeCamera.h"

CGameFrameWork::CGameFrameWork(tstring name) : CSingleTonBase(name)
{
	Initialize();
}

CGameFrameWork::~CGameFrameWork()
{
}

WARP_RESULT_ENUM CGameFrameWork::Initialize()
{
	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::Start(void* pData)
{
	// _tcscpy_s(m_pszBuffer, _T("DirectX 11 ("));
	FrameWorkStartData *data = reinterpret_cast<FrameWorkStartData*>(pData);

	if (nullptr == data)
	{
		MessageBox(nullptr, _XTT("Program Exit"), _XTT("FrameWork_Start_Error"), MB_OK);
		return CWARPResult::FAIL(ERR_INFO);
	}

	m_hInstance = data->instance;
	m_hWnd = data->hwnd;
	GetClientRect(m_hWnd, &m_rcClient);

	if (CreateDeivce() != WARP_RESULT_ENUM::OK)
		return CWARPResult::FAIL();

	if (CreateCommandQueueAndList() != WARP_RESULT_ENUM::OK)
		return CWARPResult::FAIL();

	if (CreateRtvAndDsvDescriptorHeaps() != WARP_RESULT_ENUM::OK)
		return CWARPResult::FAIL();

	if (CreateSwapChain() != WARP_RESULT_ENUM::OK)
		return CWARPResult::FAIL();

	// if (CreateCommandComplete() != WARP_RESULT_ENUM::OK)
	//    return CWARPResult::FAIL();

#ifdef NOSCENE_CREATE_CUBE_

	// 요기서하면될까?
	gCommandALlocator->Reset();
	gGraphicsCommandList->Reset(gCommandALlocator, nullptr);

	// 데이터 로딩
	CreateCube();


	gGraphicsCommandList->Close();
	ID3D12CommandList *ppd3dCommandLists[] = { gGraphicsCommandList };
	gCommandQueue->ExecuteCommandLists(1, ppd3dCommandLists);

#endif // NOSCENE_CREATE_CUBE_

	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::LateStart()
{
	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::Reset()
{
	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::Release()
{
	::CloseHandle(m_hFenceEvent);
	SAFE_DELETE(m_pCamera);
#if defined(_DEBUG)
	SAFE_RELEASE(m_pd3dDebugController);
#endif

#ifdef NOSCENE_CREATE_CUBE_
	SAFE_RELEASE(vsShader);
	SAFE_RELEASE(psShader);
	SAFE_RELEASE(gsShader);

	ReleaseCube();
#endif // NOSCENE_CREATE_CUBE_
	return WARP_RESULT_ENUM::OK;
}

void CGameFrameWork::Update()
{

}

void CGameFrameWork::Render()
{
	TIMER->Tick(60);

	if (INPUT->KeyUp(WP_Q))
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);

	HRESULT hResult = gCommandALlocator->Reset();
	hResult = gGraphicsCommandList->Reset(gCommandALlocator, NULL);

	D3D12_RESOURCE_BARRIER d3dResourceBarrier;
	::ZeroMemory(&d3dResourceBarrier, sizeof(D3D12_RESOURCE_BARRIER));
	d3dResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	d3dResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	d3dResourceBarrier.Transition.pResource = m_ppd3dSwapChainBackBuffers[m_nSwapChainBufferIndex].Get();
	d3dResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	d3dResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	d3dResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	gGraphicsCommandList->ResourceBarrier(1, &d3dResourceBarrier);

	D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle = m_pd3dRtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	d3dRtvCPUDescriptorHandle.ptr += (m_nSwapChainBufferIndex * m_nRtvDescriptorIncrementSize);

	// clear RTV
	float pfClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	gGraphicsCommandList->ClearRenderTargetView(d3dRtvCPUDescriptorHandle, pfClearColor/*Colors::Azure*/, 0, NULL);

	// clear DSV
	D3D12_CPU_DESCRIPTOR_HANDLE d3dDsvCPUDescriptorHandle = m_pd3dDsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	gGraphicsCommandList->ClearDepthStencilView(d3dDsvCPUDescriptorHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, NULL);

	// Set RTV
	gGraphicsCommandList->OMSetRenderTargets(1, &d3dRtvCPUDescriptorHandle, TRUE, &d3dDsvCPUDescriptorHandle);


	//Render
#ifdef NOSCENE_CREATE_CUBE_
	UpdateCube(gGraphicsCommandList);
	RenderCube(gGraphicsCommandList);
#endif // NOSCENE_CREATE_CUBE_

	// m_pScene->Render(m_pd3dCommandList, m_pCamera);


	d3dResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	d3dResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	d3dResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	gGraphicsCommandList->ResourceBarrier(1, &d3dResourceBarrier);

	hResult = gGraphicsCommandList->Close();

	ID3D12CommandList *ppd3dCommandLists[] = { gGraphicsCommandList };
	gCommandQueue->ExecuteCommandLists(1, ppd3dCommandLists);

	WaitForGpuComplete();

	m_pDXGISwapChain->Present(0, 0);

	//   m_nSwapChainBufferIndex = m_pdxgiSwapChain->GetCurrentBackBufferIndex();
	MoveToNextFrame();

	_TCHAR   pszFrameRate[50] = { NULL };
	TIMER->GetFrameRate(pszFrameRate, 37);
	::SetWindowText(m_hWnd, pszFrameRate);
}

WARP_RESULT_ENUM CGameFrameWork::CreateDeivce()
{
	HRESULT hResult = S_OK;
	IDXGIAdapter1 *pd3dAdapter = nullptr;

#ifdef _DEBUG
	hResult = D3D12GetDebugInterface(__uuidof(ID3D12Debug), (void **)&m_pd3dDebugController);
	m_pd3dDebugController->EnableDebugLayer();
#endif //_DEBUG

	if (FAILED(hResult = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (LPVOID*)&m_pdxgiFactory)))
	{
		MessageBox(m_hWnd, _XTT("DXGIFactory에서의 객체 생성이 실패했습니다. 프로그램을 종료합니다."), _XTT("프로그램 구동 실패"), MB_OK);
		return CWARPResult::FAIL(WARP_RESULT_ENUM::FAIL_CREATE_DXGI_FACTORY_, ERR_INFO);
	}

#ifdef _SELECT_GPU_DRIVE_170904
	size_t ui64VideoMemory;
	IDXGIAdapter1* pAdapter;
	DXGI_ADAPTER_DESC1 adapterDesc;

	// DirectX 그래픽 인터페이스 팩토리를 만듭니다. 
	if (FAILED(m_pdxgiFactory->EnumAdapters1(0, (IDXGIAdapter1**)&pAdapter)))
	{
		MessageBox(m_hWnd, TEXT("요청한 그래픽 카드 인터페이스에 대한 어댑터가 없습니다. 프로그램을 종료합니다."), TEXT("프로그램 구동 실패"), MB_OK);
	}
	pAdapter->GetDesc1(&adapterDesc);
	ui64VideoMemory = (std::size_t)(adapterDesc.DedicatedVideoMemory + adapterDesc.SharedSystemMemory);

	// warp 여기부터 외장그래픽
	//비디오 메모리 비교해서 더 좋은 GPU 찾기
	int gpu_idx = 0;
	int select = 0;
	std::size_t comparison_videoMemory;
	std::map<unsigned long long, std::wstring, std::greater<unsigned long long >> GpuInfoMap;

	while (m_pdxgiFactory->EnumAdapters1(gpu_idx, &pAdapter) != DXGI_ERROR_NOT_FOUND)   // 그래픽 카드를 검사
	{
		pAdapter->GetDesc1(&adapterDesc);
		comparison_videoMemory = (std::size_t)(adapterDesc.DedicatedVideoMemory + adapterDesc.SharedSystemMemory);

		auto memory = comparison_videoMemory / 1024 / 1024;

		std::wstring tstr;
		tstr = TEXT("GPU");
		tstr += adapterDesc.Description;
		tstr += TEXT("\t[");
		tstr += std::to_wstring(gpu_idx);
		tstr += TEXT("] : ");
		GpuInfoMap.insert(std::make_pair(memory, tstr));
		if (comparison_videoMemory > ui64VideoMemory)
		{
			ui64VideoMemory = comparison_videoMemory;
			select = gpu_idx;
		}
		++gpu_idx;
	}
	for (const auto& m : GpuInfoMap)
	{
		std::wcout << m.second;
		std::wcout << m.first;
		std::wcout << "Mb" << std::endl;
	}
	std::wcout << "seletc " << select << std::endl;
	m_pdxgiFactory->EnumAdapters1(select, &pAdapter);
#endif //  _SELECT_GPU_DRIVE_170904

	D3DDevice *pDevice = nullptr;

	hResult = D3D12CreateDevice
	(
		pd3dAdapter,
		D3D_FEATURE_LEVEL_12_0,
		_uuidof(ID3D12Device),
		(void **)&pDevice
	);

	hResult = D3D12CreateDevice(pd3dAdapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), (void **)&pDevice);

	if (pDevice == nullptr)
	{
		MessageBox(NULL, L"Direct3D 12 Device Cannot be Created.", L"Error", MB_OK);
		::PostQuitMessage(0);
		return WARP_RESULT_ENUM::FAIL;
	}

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS d3dMsaaQualityLevels;
	d3dMsaaQualityLevels.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dMsaaQualityLevels.SampleCount = 4;
	d3dMsaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	d3dMsaaQualityLevels.NumQualityLevels = 0;
	hResult = pDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &d3dMsaaQualityLevels, sizeof(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS));
	m_nMsaa4xQualityLevels = d3dMsaaQualityLevels.NumQualityLevels;
	m_bMsaa4xEnable = (m_nMsaa4xQualityLevels > 1) ? true : false;

	// CPU한테 내가 깨워줄테니깐 기다려랴
	hResult = pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void **)&m_pd3dFence);
	for (UINT i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
		m_nFenceValues[i] = 1;
	m_hFenceEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	setCBSrcDescriptorIncrementSize(pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

	if (pd3dAdapter) pd3dAdapter->Release();

	gSetDevice(pDevice);

	return WARP_RESULT_ENUM::OK;
}

WARP_RESULT_ENUM CGameFrameWork::CreateCommandQueueAndList()
{
	ID3D12CommandAllocator         *pd3dCommandAllocator = nullptr;
	ID3D12CommandQueue            *pd3dCommandQueue = nullptr;
	ID3D12GraphicsCommandList      *pd3dCommandList = nullptr;

	D3D12_COMMAND_QUEUE_DESC d3dCommandQueueDesc;
	::ZeroMemory(&d3dCommandQueueDesc, sizeof(D3D12_COMMAND_QUEUE_DESC));
	d3dCommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	d3dCommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	HRESULT hResult;
	if (gDevice == nullptr)
		return WARP_RESULT_ENUM::FAIL;
	hResult = gDevice->CreateCommandQueue(&d3dCommandQueueDesc, _uuidof(ID3D12CommandQueue), (void **)&pd3dCommandQueue);

	hResult = gDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void **)&pd3dCommandAllocator);

	hResult = gDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pd3dCommandAllocator, nullptr, __uuidof(ID3D12GraphicsCommandList), (void **)&pd3dCommandList);

	hResult = pd3dCommandList->Close();

	CGlobalvariable::GetInstance()->SeCommandAllocator(pd3dCommandAllocator);
	CGlobalvariable::GetInstance()->SetCommandQueue(pd3dCommandQueue);
	CGlobalvariable::GetInstance()->SetGraphicsCommandList(pd3dCommandList);

	if (hResult == S_OK)
		return CWARPResult::OK();
	return CWARPResult::FAIL(ERR_INFO, _XTT("CreateCommandQueueAndList"));
}

WARP_RESULT_ENUM CGameFrameWork::CreateRtvAndDsvDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	::ZeroMemory(&d3dDescriptorHeapDesc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
	d3dDescriptorHeapDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT + RENTER_TARGET_BUFFER_COUNT;
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	HRESULT hResult = gDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dRtvDescriptorHeap);
	m_nRtvDescriptorIncrementSize = gDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	d3dDescriptorHeapDesc.NumDescriptors = 1;
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	hResult = gDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dDsvDescriptorHeap);

	if (hResult == S_OK)
		return CWARPResult::OK();
	return CWARPResult::FAIL(ERR_INFO, _XTT("CreateRtvAndDsvDescriptorHeaps"));
}

WARP_RESULT_ENUM CGameFrameWork::CreateSwapChain()
{
	m_nWndClientWidth = m_rcClient.right - m_rcClient.left;
	m_nWndClientHeight = m_rcClient.bottom - m_rcClient.top;

#ifdef _WITH_CREATE_SWAPCHAIN_FOR_HWND
	DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc;
	::ZeroMemory(&dxgiSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC1));
	dxgiSwapChainDesc.Width = m_nWndClientWidth;
	dxgiSwapChainDesc.Height = m_nWndClientHeight;
	dxgiSwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSwapChainDesc.SampleDesc.Count = (m_bMsaa4xEnable) ? 4 : 1;
	dxgiSwapChainDesc.SampleDesc.Quality = (m_bMsaa4xEnable) ? (m_nMsaa4xQualityLevels - 1) : 0;
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDesc.BufferCount = m_nSwapChainBuffers;
	dxgiSwapChainDesc.Scaling = DXGI_SCALING_NONE;
	dxgiSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiSwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
#ifdef _WITH_ONLY_RESIZE_BACKBUFFERS
	dxgiSwapChainDesc.Flags = 0;
#else
	dxgiSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
#endif
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC dxgiSwapChainFullScreenDesc;
	::ZeroMemory(&dxgiSwapChainFullScreenDesc, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));
	dxgiSwapChainFullScreenDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainFullScreenDesc.RefreshRate.Denominator = 1;
	dxgiSwapChainFullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	dxgiSwapChainFullScreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	dxgiSwapChainFullScreenDesc.Windowed = TRUE;

	HRESULT hResult = m_pdxgiFactory->CreateSwapChainForHwnd(m_pd3dCommandQueue, m_hWnd, &dxgiSwapChainDesc, &dxgiSwapChainFullScreenDesc, NULL, (IDXGISwapChain1 **)&m_pDXGISwapChain);
#else
	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	::ZeroMemory(&dxgiSwapChainDesc, sizeof(dxgiSwapChainDesc));
	dxgiSwapChainDesc.BufferCount = SWAP_CHAIN_BUFFER_COUNT;
	dxgiSwapChainDesc.BufferDesc.Width = m_nWndClientWidth;
	dxgiSwapChainDesc.BufferDesc.Height = m_nWndClientHeight;
	dxgiSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiSwapChainDesc.OutputWindow = m_hWnd;
	dxgiSwapChainDesc.SampleDesc.Count = (m_bMsaa4xEnable) ? 4 : 1;
	dxgiSwapChainDesc.SampleDesc.Quality = (m_bMsaa4xEnable) ? (m_nMsaa4xQualityLevels - 1) : 0;
	dxgiSwapChainDesc.Windowed = TRUE;
#ifdef _WITH_ONLY_RESIZE_BACKBUFFERS
	dxgiSwapChainDesc.Flags = 0;
#else
	dxgiSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
#endif

	HRESULT hResult = m_pdxgiFactory->CreateSwapChain(gCommandQueue, &dxgiSwapChainDesc, (IDXGISwapChain **)&m_pDXGISwapChain);
#endif

	if (!m_pDXGISwapChain)
	{
		MessageBox(NULL, L"Swap Chain Cannot be Created.", L"Error", MB_OK);
		return CWARPResult::FAIL(ERR_INFO, _XTT("Swap Chain Cannot be Created."));
	}

	hResult = m_pdxgiFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_ALT_ENTER);
	m_nSwapChainBufferIndex = m_pDXGISwapChain->GetCurrentBackBufferIndex();
	return CWARPResult::OK();
}

WARP_RESULT_ENUM CGameFrameWork::OnResizeBackBuffers(const WORD width, const WORD height)
{
	m_nWndClientWidth = width; m_nWndClientHeight = height;

	WaitForGpuComplete();
	gGraphicsCommandList->Reset(gCommandALlocator, nullptr);

	for (int i = 0; i < m_nSwapChainBuffers; i++)
	{
		if (m_ppd3dSwapChainBackBuffers[i])
			m_ppd3dSwapChainBackBuffers[i]->Release();
	}

	if (m_pd3dDepthStencilBuffer) m_pd3dDepthStencilBuffer->Release();
#ifdef _WITH_ONLY_RESIZE_BACKBUFFERS
	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	m_pdxgiSwapChain->GetDesc(&dxgiSwapChainDesc);
	m_pdxgiSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
	m_nSwapChainBufferIndex = 0;
#else
	//m_pdxgiSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	m_pDXGISwapChain->GetDesc(&dxgiSwapChainDesc);
	m_pDXGISwapChain->ResizeBuffers(m_nSwapChainBuffers, m_nWndClientWidth, m_nWndClientHeight, dxgiSwapChainDesc.BufferDesc.Format, dxgiSwapChainDesc.Flags);
	m_nSwapChainBufferIndex = 0;
#endif

	CreateRenderTargetViews();
	CreateDepthStencilView();

	gGraphicsCommandList->Close();

	ID3D12CommandList *ppd3dCommandLists[] = { gGraphicsCommandList };
	gCommandQueue->ExecuteCommandLists(1, ppd3dCommandLists);

	WaitForGpuComplete();

	return WARP_RESULT_ENUM::OK;
}

void CGameFrameWork::CreateRenderTargetViews()
{
	D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle = m_pd3dRtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i < m_nSwapChainBuffers; i++)
	{
		m_pDXGISwapChain->GetBuffer(i, __uuidof(ID3D12Resource), (void **)&m_ppd3dSwapChainBackBuffers[i]);
		gDevice->CreateRenderTargetView(m_ppd3dSwapChainBackBuffers[i].Get(), NULL, d3dRtvCPUDescriptorHandle);
		d3dRtvCPUDescriptorHandle.ptr += m_nRtvDescriptorIncrementSize;
	}
}

void CGameFrameWork::CreateDepthStencilView()
{
	D3D12_RESOURCE_DESC d3dResourceDesc;
	d3dResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	d3dResourceDesc.Alignment = 0;
	d3dResourceDesc.Width = m_nWndClientWidth;
	d3dResourceDesc.Height = m_nWndClientHeight;
	d3dResourceDesc.DepthOrArraySize = 1;
	d3dResourceDesc.MipLevels = 1;
	d3dResourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dResourceDesc.SampleDesc.Count = (m_bMsaa4xEnable) ? 4 : 1;
	d3dResourceDesc.SampleDesc.Quality = (m_bMsaa4xEnable) ? (m_nMsaa4xQualityLevels - 1) : 0;
	d3dResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	d3dResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_HEAP_PROPERTIES d3dHeapProperties;
	::ZeroMemory(&d3dHeapProperties, sizeof(D3D12_HEAP_PROPERTIES));
	d3dHeapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	d3dHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	d3dHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	d3dHeapProperties.CreationNodeMask = 1;
	d3dHeapProperties.VisibleNodeMask = 1;

	D3D12_CLEAR_VALUE d3dClearValue;
	d3dClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dClearValue.DepthStencil.Depth = 1.0f;
	d3dClearValue.DepthStencil.Stencil = 0;

	D3D12_CPU_DESCRIPTOR_HANDLE d3dDsvCPUDescriptorHandle = m_pd3dDsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	gDevice->CreateCommittedResource(&d3dHeapProperties, D3D12_HEAP_FLAG_NONE, &d3dResourceDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &d3dClearValue, __uuidof(ID3D12Resource), (void **)&m_pd3dDepthStencilBuffer);

	D3D12_DEPTH_STENCIL_VIEW_DESC d3dDepthStencilViewDesc;
	::ZeroMemory(&d3dDepthStencilViewDesc, sizeof(D3D12_DEPTH_STENCIL_VIEW_DESC));
	d3dDepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dDepthStencilViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	d3dDepthStencilViewDesc.Flags = D3D12_DSV_FLAG_NONE;

	gDevice->CreateDepthStencilView(m_pd3dDepthStencilBuffer.Get(), NULL, d3dDsvCPUDescriptorHandle);
	//   m_pd3dDevice->CreateDepthStencilView(m_pd3dDepthStencilBuffer, &d3dDepthStencilViewDesc, d3dDsvCPUDescriptorHandle);
}

WARP_RESULT_ENUM CGameFrameWork::CreateCommandComplete()
{
	gCommandALlocator->Reset();
	gGraphicsCommandList->Reset(gCommandALlocator, nullptr);
	ID3D12CommandList *ppd3dCommandLists[] = { gGraphicsCommandList };
	gGraphicsCommandList->Close();
	gCommandQueue->ExecuteCommandLists(1, ppd3dCommandLists);
	WaitForGpuComplete();

	return CWARPResult::OK();
}

WARP_RESULT_ENUM CGameFrameWork::WaitForGpuComplete()
{
	const UINT64 nFenceValue = ++m_nFenceValues[m_nSwapChainBufferIndex];
	HRESULT hResult = gCommandQueue->Signal(m_pd3dFence.Get(), nFenceValue);
	if (m_pd3dFence->GetCompletedValue() < nFenceValue)
	{
		hResult = m_pd3dFence->SetEventOnCompletion(nFenceValue, m_hFenceEvent);
		::WaitForSingleObject(m_hFenceEvent, INFINITE);
	}
	return CWARPResult::OK();
}

WARP_RESULT_ENUM CGameFrameWork::MoveToNextFrame()
{
	m_nSwapChainBufferIndex = m_pDXGISwapChain->GetCurrentBackBufferIndex();
	//m_nSwapChainBufferIndex = (m_nSwapChainBufferIndex + 1) % m_nSwapChainBuffers;

	UINT64 nFenceValue = ++m_nFenceValues[m_nSwapChainBufferIndex];
	HRESULT hResult = gCommandQueue->Signal(m_pd3dFence.Get(), nFenceValue);

	if (m_pd3dFence->GetCompletedValue() < nFenceValue)
	{
		hResult = m_pd3dFence->SetEventOnCompletion(nFenceValue, m_hFenceEvent);
		::WaitForSingleObject(m_hFenceEvent, INFINITE);
	}

	return WARP_RESULT_ENUM::OK;

}

#ifdef NOSCENE_CREATE_CUBE_
#define _FIRST_

void CGameFrameWork::CreateCube()
{

#pragma  region[Create Camera]
	m_pCamera = new CFreeCamera();
	m_pCamera->SetViewport(0, 0, m_nWndClientWidth, m_nWndClientHeight, 0.0f, 1.0f);
	m_pCamera->CreatesProjectionMatrix(90.0f, ASPECT_RATIO, 1.0f, 500.0f);
	m_pCamera->SetLookAt(XMFLOAT3(0.0f, 0.0f, -12.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));
#pragma endregion

	// Create Root Signature
#pragma region [Creaet Signature]

	D3D12_ROOT_PARAMETER pd3dRootParameters[4];

	int index = 0;
	pd3dRootParameters[index].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // 루트 서술자를 사용하자
	pd3dRootParameters[index].Descriptor.ShaderRegister = 0;
	pd3dRootParameters[index].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[index].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	index++;

	pd3dRootParameters[index].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[index].Constants.Num32BitValues = 32; // 행렬 2개
	pd3dRootParameters[index].Constants.ShaderRegister = 1;
	pd3dRootParameters[index].Constants.RegisterSpace = 0;
	pd3dRootParameters[index].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	index++;

	D3D12_DESCRIPTOR_RANGE tablerange[2];
	tablerange[0].BaseShaderRegister = 0;
	tablerange[0].NumDescriptors = 1;
	tablerange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	tablerange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	tablerange[0].RegisterSpace = 0;

	tablerange[1].BaseShaderRegister = 0;
	tablerange[1].NumDescriptors = 1;
	tablerange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	tablerange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
	tablerange[1].RegisterSpace = 0;

	pd3dRootParameters[index].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[index].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[index].DescriptorTable.pDescriptorRanges = &tablerange[0];
	pd3dRootParameters[index].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	index++;

	pd3dRootParameters[index].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[index].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[index].DescriptorTable.pDescriptorRanges = &tablerange[1];
	pd3dRootParameters[index].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	index++;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;
	//	D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
	//	D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = nullptr;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = nullptr;
	ID3DBlob *pd3dErrorBlob = nullptr;

	HRESULT hr = D3D12SerializeRootSignature
	(
		&d3dRootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&pd3dSignatureBlob,
		&pd3dErrorBlob
	);
	hr = gDevice->CreateRootSignature
	(
		0,
		pd3dSignatureBlob->GetBufferPointer(),
		pd3dSignatureBlob->GetBufferSize(),
		__uuidof(ID3D12RootSignature),
		(void **)&m_mRootSignature
	);

	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();
#pragma endregion [Creaet Signature]

#pragma region [Create Mesh & GameObject & Shader]

	const int constmaxCount = 1;
	VertexPositionColor pVertices[constmaxCount];
	pVertices[0] = VertexPositionColor{ XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) }; //XMFLOAT4(Colors::Red)
	//pVertices[1] = VertexPositionColor{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) };
	//pVertices[2] = VertexPositionColor{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::Blue)/*XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)*/ };

	/*
		inputLayOut =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			// { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};
		여기 들어가는 pos, color이 저 verteies랑 같음.
		그리고 여기는 용빠코드에서 mesh부분이양

		struct VS_INPUT		// 이거랑 일치
		{
			float3 position : POSITION; // 3
			float4 color : COLOR; // 4
		};
	*/

	ComPtr<D3DBuffer> uploadBuffer;
	vsBuffer =
		Radar::Util::CreateBuffer
		(
			gDevice,
			gGraphicsCommandList,
			pVertices,
			sizeof(VertexPositionColor) * constmaxCount,
			D3D12_HEAP_TYPE_DEFAULT,
			D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
			&uploadBuffer
		);

	vsBufferView.BufferLocation = vsBuffer->GetGPUVirtualAddress();
	vsBufferView.StrideInBytes = sizeof(VertexPositionColor);
	vsBufferView.SizeInBytes = sizeof(VertexPositionColor) * constmaxCount;

	// Shader & Gameobjectc cb
	// D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	// cbvHeapDesc.NumDescriptors = 1;
	// cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	// cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	// cbvHeapDesc.NodeMask = 0;
	// 
	// hr = gDevice->CreateDescriptorHeap
	// (
	// 	&cbvHeapDesc,
	// 	__uuidof(ID3D12DescriptorHeap),
	// 	(void **)(&descriptorHeap)
	// );

	cbWorldMatrix = std::make_unique<UploadBuffer<XMFLOAT4X4>>(gDevice, 1, true);
	//UINT elementByteSize = Radar::CalcConstantBufferByteSize(sizeof(XMFLOAT4X4));
	//D3D12_GPU_VIRTUAL_ADDRESS cbAddress = cbWorldMatrix->Resource()->GetGPUVirtualAddress();
	
	// Offset to the ith object constant buffer in the buffer.
	// int boxCBufIndex = 0;//버퍼인덱스!
	// cbAddress += boxCBufIndex * elementByteSize;
	// 
	// D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	// cbvDesc.BufferLocation = cbAddress;      //콘스턴트 버퍼의 주소
	// cbvDesc.SizeInBytes = elementByteSize;   //
	// 
	// gDevice->CreateConstantBufferView
	// (
	// 	&cbvDesc,
	// 	descriptorHeap->GetCPUDescriptorHandleForHeapStart()
	// );


	//-------------------------

	vsShader = Radar::CompileShader(_XTT("hlsl/GSShader.hlsl"), nullptr, "VSDiffused", "vs_5_0");
	if (vsShader == nullptr)
		MessageBoxA(NULL, "vsShader make fail", "create fail", MB_OK);

	gsShader = Radar::CompileShader(_XTT("hlsl/GSShader.hlsl"), nullptr, "GSCube", "gs_5_0");
	if (gsShader == nullptr)
		MessageBoxA(NULL, "gsShader make fail", "create fail", MB_OK);

	psShader = Radar::CompileShader(_XTT("hlsl/GSShader.hlsl"), nullptr, "PSDiffused", "ps_5_0");
	if (psShader == nullptr)
		MessageBoxA(NULL, "psShader make fail", "create fail", MB_OK);


	//inputLayOut =
	//{
	// { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	// { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	// // { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//};

	UINT nInputElementDescs = 1;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = 
	{ 
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
		0
	};
	//pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	inputLayOut.pInputElementDescs = pd3dInputElementDescs;
	inputLayOut.NumElements = nInputElementDescs;

	
	/*
		여기부터 쉐이더 추가부분
	*/

	//	m_TextureuploadBuffer = std::make_unique<UploadBuffer<D3DBuffer>>(gDevice, 1, true);
	m_pTexture = Radar::Util::CreateTexture
	(gDevice, gGraphicsCommandList, tstring(_XTT("default2.dds")),
		&m_TextureuploadBuffer, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);


	// heap
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = 1; //CBVs + SRVs 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	gDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, IID_PPV_ARGS(&m_pd3dCbvSrvDescriptorHeap));

	// Desc
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D12_CPU_DESCRIPTOR_HANDLE hDescriptor{ m_pd3dCbvSrvDescriptorHeap.Get()->GetCPUDescriptorHandleForHeapStart() };
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = m_pTexture->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = m_pTexture->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	srvDesc.Texture2D.PlaneSlice = 0;
	gDevice->CreateShaderResourceView(m_pTexture.Get(), &srvDesc, hDescriptor);//힙에대한......
	// Creaet Resourec 

	D3D12_DESCRIPTOR_HEAP_DESC desc;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NumDescriptors = 1;
	desc.NodeMask = 0;

	hr = gDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_SamplerHeap));
	//..네~ 힙만들엇어용!

	D3D12_SAMPLER_DESC samplerdesc;
	samplerdesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	samplerdesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerdesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerdesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerdesc.MinLOD = 0;
	samplerdesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerdesc.MipLODBias = 0.0f;
	samplerdesc.MaxAnisotropy = 1;
	samplerdesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	gDevice->CreateSampler(&samplerdesc, m_SamplerHeap->GetCPUDescriptorHandleForHeapStart());


	// PSO 생성
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

	psoDesc.InputLayout = inputLayOut;//
	psoDesc.pRootSignature = m_mRootSignature.Get();
	psoDesc.VS =
	{
		reinterpret_cast<BYTE*>(vsShader->GetBufferPointer()),
		vsShader->GetBufferSize()
	};
	psoDesc.GS =
	{
		reinterpret_cast<BYTE*>(gsShader->GetBufferPointer()),
		gsShader->GetBufferSize()
	};

	psoDesc.PS =
	{
		reinterpret_cast<BYTE*>(psShader->GetBufferPointer()),
		psShader->GetBufferSize()
	};

	CD3DX12_RASTERIZER_DESC raster(D3D12_DEFAULT);
	raster.CullMode = D3D12_CULL_MODE_NONE;
	psoDesc.RasterizerState = raster;
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.SampleDesc.Quality = 0;
	psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	hr = gDevice->CreateGraphicsPipelineState
	(
		&psoDesc,
		__uuidof(ID3D12PipelineState),
		(void **)&pipeState
	);

	if (psoDesc.InputLayout.pInputElementDescs)
		delete[] psoDesc.InputLayout.pInputElementDescs;
	if (hr != S_OK)
		MessageBoxA(NULL, "pipeState make fail", "create fail", MB_OK);

#pragma endregion

}

void CGameFrameWork::ReleaseCube()
{
	//if (m_mRootSignature)
	//	m_mRootSignature->Release();
	//SAFE_RELEASE(m_mRootSignature);
	//SAFE_RELEASE(uploadBuffer);
	//SAFE_RELEASE(vsBuffer);
	//SAFE_RELEASE(psBuffer);

	SAFE_RELEASE(m_pTexture);

	if (m_pCamera)
		delete m_pCamera;
}

void CGameFrameWork::RenderCube(ID3D12GraphicsCommandList *pd3dCommandList)
{
	pd3dCommandList->SetGraphicsRootSignature(m_mRootSignature.Get());
	pd3dCommandList->SetPipelineState(pipeState.Get());

	m_pCamera->SetViewportsAndScissorRects(gGraphicsCommandList);
	m_pCamera->UpdateShaderVariables(gGraphicsCommandList);

	// 
	D3D12_GPU_VIRTUAL_ADDRESS pd3dGpuAddress = cbWorldMatrix->Resource()->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(0, pd3dGpuAddress);

	ID3D12DescriptorHeap*descriptorHeaps[2]{ m_pd3dCbvSrvDescriptorHeap.Get(), m_SamplerHeap.Get() };
	pd3dCommandList->SetDescriptorHeaps(2, descriptorHeaps);

	pd3dCommandList->SetGraphicsRootDescriptorTable(2, m_pd3dCbvSrvDescriptorHeap.Get()->GetGPUDescriptorHandleForHeapStart());//텍스쳐 연결하기.
	pd3dCommandList->SetGraphicsRootDescriptorTable(3, m_SamplerHeap->GetGPUDescriptorHandleForHeapStart()); //셈플러연결하기

	pd3dCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	pd3dCommandList->IASetVertexBuffers(0, 1, &vsBufferView);
	pd3dCommandList->DrawInstanced(1, 1, 0, 0);

	// pd3dCommandList->SetGraphicsRootDescriptorTable
	//    (0, descriptorHeap->GetGPUDescriptorHandleForHeapStart());

}

void CGameFrameWork::UpdateCube(ID3D12GraphicsCommandList *pd3dCommandList)
{
	static int angle = 0;
	angle += (int)(0.17f * 10);
	XMFLOAT4X4 xm = Radar::Math::Identity();
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians((float)angle), XMConvertToRadians((float)angle), XMConvertToRadians(0.f));
	xm = Radar::Math::Multiply(mtxRotate, xm);
	XMStoreFloat4x4(&xm, XMMatrixTranspose(XMLoadFloat4x4(&xm)));
	cbWorldMatrix->CopyData(0, xm);

	if (m_pCamera)
		m_pCamera->Update(0.17f);
}
#endif // NOSCENE_CREATE_CUBE_

//src2