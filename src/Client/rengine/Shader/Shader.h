
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

// #define _ADD_SHAYER_SYSTEM_

#ifdef _ADD_SHAYER_SYSTEM_
class CRShader : public Object
{
public:
	CRShader();
	virtual ~CRShader();

protected:
	MESH_TYPE						m_nType;
	int								m_nInputElements;

	D3D_IA_ELEMENT				m_I;
	D3D_IA_LAYOUT				m_inputLayout;			// Vertex -LayOut
	D3D_VS_SHADER				m_vsShader;				// Vertex -Shader
	D3D_GS_SHADER				m_GeoMetoryShader;		// Geo   -Shader
	D3D_PS_SHADER				m_PixelShader;			// Sov	- Shader
	D3D_DS_SHADER				m_DomainShader;			// Domain- Shader
	D3D_HS_SHADER				m_HullShader;			// Hull   - SHader
	D3D_CS_SHADER				m_ComputeShader;		// Compute   - SHader
	//D3D_GS_SHADER				m_gsShader;				// Pixel -Shader
	//D3D_GS_SHADER				m_gsSOShader;			// SOGeo - Shader

protected:
	virtual D3D12_SHADER_BYTECODE CreateShader(ID3DBlob **ppd3dShaderBlob);


	void CreateVertexShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11VertexShader **ppd3dVertexShader, D3D11_INPUT_ELEMENT_DESC *pd3dInputElements, UINT nElements, ID3D11InputLayout **ppd3dInputLayout);
	void CreatePixelShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11PixelShader **ppd3dPixelShader);
	void CreateGeometryShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11GeometryShader **ppd3dGeometryShader);
	void CreateSOGeometryShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11GeometryShader **ppd3dGeometryShader);
	void CreateSOGeometryShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11GeometryShader **ppd3dGeometryShader, SO_Geometry_INFO sgi);
	void CreateHullShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11HullShader **ppd3dHullShader);
	void CreateDomainShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11DomainShader **ppd3dDomainShader);
	void CreateComputeShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11ComputeShader **ppd3dComputeShader);

	//KYT 16.08.06 
	/*
		컴파일 된 쉐이더를 사용하기 위해 추가.
										feat.백길쌍
	*/
	void CreateVertexShaderFromCompiledFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, D3D11_INPUT_ELEMENT_DESC *pd3dInputLayout, UINT nElements, ID3D11VertexShader **ppd3dVertexShader);
	void CreateSOVertexShaderFromCompiledFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, D3D11_INPUT_ELEMENT_DESC *pd3dInputLayout, UINT nElements, ID3D11VertexShader **ppd3dVertexShader, ID3D11InputLayout *ppInputLayout);
	void CreateGeoMoetryShaderFromCompiledFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, ID3D11GeometryShader **ppd3dGeomeotryShader);
	void CreatePixelShaderFromCompiledFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, ID3D11PixelShader **ppd33dPixelShader);
	void CreateComputeShaderFromCompiledFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, ID3D11ComputeShader **ppd33dComputeShader);
	void CreateDomainShaderFromCompiledFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, ID3D11DomainShader **ppd33dPixelShader);
	void CreateHullShaderFromCompiledFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, ID3D11HullShader **ppd33dHullShader);




public:
	virtual WARP_RESULT_ENUM Initialize();

	virtual void GetInputElementDesc(UINT nVertexElementType);
	virtual void GetShaderName(UINT nVertexElementType, LPCSTR *ppszVSShaderName, LPCSTR *ppszVSShaderModel, LPCSTR *ppszPSShaderName, LPCSTR *ppszPSShaderModel);

	virtual void CreateShader(ID3D11Device *pd3dDevice) { }
	virtual void CreateShader(ID3D11Device *pd3dDevice, UINT nType);
	virtual void CreateShader(ID3D11Device *pd3dDevice, D3D11_INPUT_ELEMENT_DESC *pd3dInputElementDesc, int nInputElements, WCHAR *pszFileName, LPCSTR pszVSShaderName, LPCSTR pszVSShaderModel, LPCSTR pszPSShaderName, LPCSTR pszPSShaderModel);

	virtual void CreateConstBuffers(ID3D11Device *pd3dDevice);
	virtual void ReleaseShaderVariables();

	virtual void OnPrepareRender(ID3D11DeviceContext *pd3dDeviceContext);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, std::shared_ptr<CCamera> pCamera);

public:
	static ID3D11Buffer *CreateBuffer(ID3D11Device *pd3dDevice, UINT nStride, int nElements, void *pBufferData, UINT nBindFlags, D3D11_USAGE d3dUsage, UINT nCPUAccessFlags);


protected:
	// 공간분할 랜더링
	// 매 프레임마다 이 벡터에 랜더링할 오브젝트를 업데이트 해준다. 
	std::vector<std::shared_ptr<CGameObject>>		m_vRenderObject;

public:

	//KYT '15.01.29 
	std::vector<std::shared_ptr<CGameObject>> GetvRenderObject() { return m_vRenderObject; }

	void PushRenderObject(std::shared_ptr<CGameObject> object = nullptr);

	void ClearRenderObject() { m_vRenderObject.clear(); }

	virtual void SpacePartitioningRender(ID3D11DeviceContext *pd3dDeviceContext, std::shared_ptr<CCamera> pCamera);

	CMesh* GetMesh(int index = 0) { return m_pMesh.get(); }

protected:
	vector<ComPtr<CMesh>>		vMesh;

};
#endif // _ADD_SHAYER_SYSTEM_

struct CB_GAMEOBJECT_INFO
{
	XMFLOAT4X4						m_xmf4x4World;
};

class CShader
{
public:
	CShader();
	virtual ~CShader();

public:
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState();
	virtual D3D12_BLEND_DESC CreateBlendState();
	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);

	D3D12_SHADER_BYTECODE CompileShaderFromFile(tstring pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob);
	D3D12_SHADER_BYTECODE CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob);

	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual void UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World);

	virtual void ReleaseUploadBuffers();

	virtual void OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList);

protected:
	ID3D12PipelineState				**m_ppd3dPipelineStates = NULL;
	int								m_nPipelineStates = 0;

protected:
	D3DBuffer						*m_pd3dcbGameObject = NULL;			// constant 버퍼
	CB_GAMEOBJECT_INFO				*m_pcbMappedGameObject = NULL;		// 리소스에 대한 메모리 주소
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CDiffusedShader : public CShader
{
public:
	CDiffusedShader();
	virtual ~CDiffusedShader();

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();

	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
};
