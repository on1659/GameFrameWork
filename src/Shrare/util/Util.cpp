
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#include "PreComplie.h"

#include <vector>
#include <DirectXMath.h>

#include "Util.h"
#include "task/MyFlag.h"
#include "task/MyDefine.h"
#include "task/MyEnum.h"

#include <fstream>

using namespace Radar;

D3DBuffer  *Radar::Util::gCbWorldMatrix = nullptr;
D3DBuffer  *Radar::Util::gCbMaterialColors = nullptr;
XMMATRIX	Radar::Util::gCbd3dxmtxIdentity;
XMFLOAT4	Radar::Util::gCbd3dxmf4Color;

D3DBuffer* Util::CreateBuffer(D3DDevice *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pData, UINT nBytes, D3D12_HEAP_TYPE d3dHeapType, D3D12_RESOURCE_STATES d3dResourceStates, D3DBuffer **ppd3dUploadBuffer)
{
	ID3D12Resource *pd3dBuffer = NULL;

	D3D12_HEAP_PROPERTIES d3dHeapPropertiesDesc;
	::ZeroMemory(&d3dHeapPropertiesDesc, sizeof(D3D12_HEAP_PROPERTIES));
	d3dHeapPropertiesDesc.Type = d3dHeapType;
	d3dHeapPropertiesDesc.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	d3dHeapPropertiesDesc.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	d3dHeapPropertiesDesc.CreationNodeMask = 1;
	d3dHeapPropertiesDesc.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC d3dResourceDesc;
	::ZeroMemory(&d3dResourceDesc, sizeof(D3D12_RESOURCE_DESC));
	d3dResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	d3dResourceDesc.Alignment = 0;
	d3dResourceDesc.Width = nBytes;
	d3dResourceDesc.Height = 1;
	d3dResourceDesc.DepthOrArraySize = 1;
	d3dResourceDesc.MipLevels = 1;
	d3dResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	d3dResourceDesc.SampleDesc.Count = 1;
	d3dResourceDesc.SampleDesc.Quality = 0;
	d3dResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	d3dResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	D3D12_RESOURCE_STATES d3dResourceInitialStates = D3D12_RESOURCE_STATE_COPY_DEST;
	if (d3dHeapType == D3D12_HEAP_TYPE_UPLOAD) d3dResourceInitialStates = D3D12_RESOURCE_STATE_GENERIC_READ;
	else if (d3dHeapType == D3D12_HEAP_TYPE_READBACK) d3dResourceInitialStates = D3D12_RESOURCE_STATE_COPY_DEST;

	HRESULT hResult = pd3dDevice->CreateCommittedResource(&d3dHeapPropertiesDesc, D3D12_HEAP_FLAG_NONE, &d3dResourceDesc, d3dResourceInitialStates, NULL, __uuidof(ID3D12Resource), (void **)&pd3dBuffer);

	if (pData)
	{
		switch (d3dHeapType)
		{
		case D3D12_HEAP_TYPE_DEFAULT:
		{
			if (ppd3dUploadBuffer)
			{
				d3dHeapPropertiesDesc.Type = D3D12_HEAP_TYPE_UPLOAD;
				pd3dDevice->CreateCommittedResource(&d3dHeapPropertiesDesc, D3D12_HEAP_FLAG_NONE, &d3dResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, __uuidof(ID3D12Resource), (void **)ppd3dUploadBuffer);
#ifdef _WITH_MAPPING
				D3D12_RANGE d3dReadRange = { 0, 0 };
				UINT8 *pBufferDataBegin = NULL;
				(*ppd3dUploadBuffer)->Map(0, &d3dReadRange, (void **)&pBufferDataBegin);
				memcpy(pBufferDataBegin, pData, nBytes);
				(*ppd3dUploadBuffer)->Unmap(0, NULL);

				pd3dCommandList->CopyResource(pd3dBuffer, *ppd3dUploadBuffer);
#else
				D3D12_SUBRESOURCE_DATA d3dSubResourceData;
				::ZeroMemory(&d3dSubResourceData, sizeof(D3D12_SUBRESOURCE_DATA));
				d3dSubResourceData.pData = pData;
				d3dSubResourceData.SlicePitch = d3dSubResourceData.RowPitch = nBytes;
				::UpdateSubresources<1>(pd3dCommandList, pd3dBuffer, *ppd3dUploadBuffer, 0, 0, 1, &d3dSubResourceData);

#endif
				D3D12_RESOURCE_BARRIER d3dResourceBarrier;
				::ZeroMemory(&d3dResourceBarrier, sizeof(D3D12_RESOURCE_BARRIER));
				d3dResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				d3dResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				d3dResourceBarrier.Transition.pResource = pd3dBuffer;
				d3dResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
				d3dResourceBarrier.Transition.StateAfter = d3dResourceStates;
				d3dResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				pd3dCommandList->ResourceBarrier(1, &d3dResourceBarrier);
			}
			break;
		}
		case D3D12_HEAP_TYPE_UPLOAD:
		{
			D3D12_RANGE d3dReadRange = { 0, 0 };
			UINT8 *pBufferDataBegin = NULL;
			pd3dBuffer->Map(0, &d3dReadRange, (void **)&pBufferDataBegin);
			memcpy(pBufferDataBegin, pData, nBytes);
			pd3dBuffer->Unmap(0, NULL);
			break;
		}
		case D3D12_HEAP_TYPE_READBACK:
			break;
		}
	}
	return(pd3dBuffer);
}

D3DBuffer* Util::CreateBuffer(void *pData, UINT nBytes, D3D12_HEAP_TYPE d3dHeapType, D3D12_RESOURCE_STATES d3dResourceStates, D3DBuffer **ppd3dUploadBuffer)
{
	return CreateBuffer(gDevice, gGraphicsCommandList, pData, nBytes, d3dHeapType, d3dResourceStates, ppd3dUploadBuffer);
}


// 파일로부터 텍스쳐 리소스를 만들어낸다.
D3DBuffer* Util::CreateTexture(D3DDevice *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, tstring pszFileName, D3DBuffer **ppd3dUploadBuffer, D3D12_RESOURCE_STATES d3dResourceStates)
{
	D3DBuffer *pd3dTexture = NULL;
	std::unique_ptr<uint8_t[]> ddsData;
	std::vector<D3D12_SUBRESOURCE_DATA> vSubresources;
	DDS_ALPHA_MODE ddsAlphaMode = DDS_ALPHA_MODE_UNKNOWN;
	bool bIsCubeMap = false;


	tstring fullPath = GLOBAL_VARIABLE->GetCommandLineMsg();
	fullPath += pszFileName;

	HRESULT hResult = DirectX::LoadDDSTextureFromFileEx(pd3dDevice, fullPath.c_str(), 0, D3D12_RESOURCE_FLAG_NONE, DDS_LOADER_DEFAULT, &pd3dTexture, ddsData, vSubresources, &ddsAlphaMode, &bIsCubeMap);
	if (hResult != S_OK)
	{
		MessageBox(NULL, pszFileName.c_str(), _XTT("Create Texture FAIL"), MB_OK);
		return nullptr;
	}
	D3D12_HEAP_PROPERTIES d3dHeapPropertiesDesc;
	::ZeroMemory(&d3dHeapPropertiesDesc, sizeof(D3D12_HEAP_PROPERTIES));

	// 업로드 힙을 만들어야한다.
	d3dHeapPropertiesDesc.Type = D3D12_HEAP_TYPE_UPLOAD;
	d3dHeapPropertiesDesc.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	d3dHeapPropertiesDesc.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	d3dHeapPropertiesDesc.CreationNodeMask = 1;
	d3dHeapPropertiesDesc.VisibleNodeMask = 1;

	//	D3D12_RESOURCE_DESC d3dResourceDesc = pd3dTexture->GetDesc();
	//	UINT nSubResources = d3dResourceDesc.DepthOrArraySize * d3dResourceDesc.MipLevels;
	UINT nSubResources = (UINT)vSubresources.size();
	//	UINT64 nBytes = 0;
	//	pd3dDevice->GetCopyableFootprints(&d3dResourceDesc, 0, nSubResources, 0, NULL, NULL, NULL, &nBytes);
	UINT64 nBytes = GetRequiredIntermediateSize(pd3dTexture, 0, nSubResources);

	D3D12_RESOURCE_DESC d3dResourceDesc;
	::ZeroMemory(&d3dResourceDesc, sizeof(D3D12_RESOURCE_DESC));
	d3dResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; //Upload Heap에는 텍스쳐를 생성할 수 없음
	d3dResourceDesc.Alignment = 0;
	d3dResourceDesc.Width = nBytes;
	d3dResourceDesc.Height = 1;
	d3dResourceDesc.DepthOrArraySize = 1;
	d3dResourceDesc.MipLevels = 1;
	d3dResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	d3dResourceDesc.SampleDesc.Count = 1;
	d3dResourceDesc.SampleDesc.Quality = 0;
	d3dResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	d3dResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	pd3dDevice->CreateCommittedResource(&d3dHeapPropertiesDesc, D3D12_HEAP_FLAG_NONE, &d3dResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, __uuidof(ID3D12Resource), (void **)ppd3dUploadBuffer);

	//UINT nSubResources = (UINT)vSubresources.size();
	//D3D12_SUBRESOURCE_DATA *pd3dSubResourceData = new D3D12_SUBRESOURCE_DATA[nSubResources];
	//for (UINT i = 0; i < nSubResources; i++) pd3dSubResourceData[i] = vSubresources.at(i);

	//	std::vector<D3D12_SUBRESOURCE_DATA>::pointer ptr = &vSubresources[0];
	::UpdateSubresources(pd3dCommandList, pd3dTexture, *ppd3dUploadBuffer, 0, 0, nSubResources, &vSubresources[0]);

	D3D12_RESOURCE_BARRIER d3dResourceBarrier;
	::ZeroMemory(&d3dResourceBarrier, sizeof(D3D12_RESOURCE_BARRIER));
	d3dResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	d3dResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	d3dResourceBarrier.Transition.pResource = pd3dTexture;
	d3dResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	d3dResourceBarrier.Transition.StateAfter = d3dResourceStates;
	d3dResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	pd3dCommandList->ResourceBarrier(1, &d3dResourceBarrier);

	//	delete[] pd3dSubResourceData;

	return(pd3dTexture);
}


//Create
/*
	WorldMatrix , MaterialClor Matrix
*/
void Util::Global_CreateConstBuffers()
{
	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	d3dBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3dBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	d3dBufferDesc.ByteWidth = sizeof(VS_CB_WORLD_MATRIX);

	Util::gCbd3dxmtxIdentity = XMMatrixIdentity();
	UINT ncbElementBytes = ((sizeof(VS_CB_WORLD_MATRIX) + 255) & ~255); //256의 배수
	Util::gCbWorldMatrix =
		CreateBuffer(NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	Util::gCbWorldMatrix->Map(0, NULL, (void **)&Radar::Util::gCbd3dxmtxIdentity);


	Util::gCbd3dxmf4Color = XMFLOAT4(1, 1, 1, 1);
	ncbElementBytes = ((sizeof(XMFLOAT4) + 255) & ~255); //256의 배수
	Util::gCbMaterialColors =
		CreateBuffer(NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	Util::gCbMaterialColors->Map(0, NULL, (void **)&Radar::Util::gCbd3dxmf4Color);

	// gDeviceContext->VSSetConstantBuffers(VS_CB_SLOT_WORLD_MATRIX, 1, &Radar::Util::gCbWorldMatrix);
	// gDeviceContext->GSSetConstantBuffers(VS_CB_SLOT_WORLD_MATRIX, 1, &Radar::Util::gCbWorldMatrix);
	// gDeviceContext->PSSetConstantBuffers(PS_CB_SLOT_MATERIAL, 1, &Radar::Util::gCbMaterialColors);
}

void Util::Global_ReleaseConstBuffers()
{
	if (Radar::Util::gCbWorldMatrix)    Radar::Util::gCbWorldMatrix->Release();
	if (Radar::Util::gCbMaterialColors) Radar::Util::gCbMaterialColors->Release();
}

void Util::Global_WorldMatrixUpdateConstBuffer(XMMATRIX& pd3dxmtxWorld)
{
	Util::gCbd3dxmtxIdentity = XMMatrixIdentity();
	UINT ncbElementBytes = ((sizeof(VS_CB_WORLD_MATRIX) + 255) & ~255); //256의 배수

	Util::gCbWorldMatrix =
		CreateBuffer(NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);



	// D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	// gDeviceContext->Map(Radar::Util::gCbWorldMatrix, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	// VS_CB_WORLD_MATRIX *pcbWorldMatrix = (VS_CB_WORLD_MATRIX *)d3dMappedResource.pData;
	// //XMStoreFloat4x4(&pcbWorldMatrix->m_d3dxmtxWorld, XMMatrixTranspose(pd3dxmtxWorld));
	// 
	// gDeviceContext->Unmap(Radar::Util::gCbWorldMatrix, 0);
	// gDeviceContext->VSSetConstantBuffers(VS_CB_SLOT_WORLD_MATRIX, 1, &Radar::Util::gCbWorldMatrix);
	// 
	// //GeoShader
	// gDeviceContext->GSSetConstantBuffers(VS_CB_SLOT_WORLD_MATRIX, 1, &Radar::Util::gCbWorldMatrix);
}


std::vector<std::byte> Util::ReadCSOFile(const LPCTSTR& path)
{
	std::ifstream inputShaderCSO(path, std::ios::in | std::ios::binary);

	if (!inputShaderCSO.is_open())
	{
		return std::vector<std::byte>();
	}

	// size check;
	inputShaderCSO.seekg(0, std::fstream::end);
	size_t szData = inputShaderCSO.tellg();
	inputShaderCSO.seekg(0);

	std::vector<std::byte> retval;
	retval.resize(szData);

	inputShaderCSO.read(reinterpret_cast<char*>(&(retval[0])), szData);
	inputShaderCSO.close();

	return retval;
}

int Radar::Util::ErrorMessage(const HWND& hwnd,const LPCTSTR & title, const LPCTSTR & message)
{
	return MessageBox(hwnd, title, message, MB_OK);
}

void Radar::print(const std::string& msg)
{
	cout << msg << endl;
}

void Radar::print(const std::wstring& msg)
{
	std::wcout << msg << std::endl;
}