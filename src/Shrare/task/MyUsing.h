
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

// using
#ifdef CLIENT_ONLY
#ifdef DX12

	using D3D_IA_ELEMENT	= D3D12_INPUT_ELEMENT_DESC;
	using D3D_IA_LAYOUT		= D3D12_INPUT_LAYOUT_DESC;
	using D3D_VS_SHADER		= D3D12_SHADER_BYTECODE;
	using D3D_GS_SHADER		= D3D12_SHADER_BYTECODE;
	using D3D_PS_SHADER		= D3D12_SHADER_BYTECODE;
	using D3D_GS_SHADER		= D3D12_SHADER_BYTECODE;
	using D3D_DS_SHADER		= D3D12_SHADER_BYTECODE;
	using D3D_HS_SHADER		= D3D12_SHADER_BYTECODE;
	using D3D_CS_SHADER		= D3D12_SHADER_BYTECODE;
	using D3DBlob			= ID3DBlob;

	using D3DDevice			= ID3D12Device;
	using D3DBuffer			= ID3D12Resource;
	using D3DFactory		= IDXGIFactory4;
	using DXGISSwapChain	= IDXGISwapChain3;
	using DX_VIEWPORT		= D3D12_VIEWPORT;
	using DX_RECT			= D3D12_RECT;

#else // DX12
	using D3D_INPUT_ELEMENT = D3D11_INPUT_ELEMENT_DESC;
	using D3D_IA_LAYOUT		= ID3D11InputLayout;
	using D3D_VS_SHADER		= ID3D11VertexShader;
	using D3D_GS_SHADER		= ID3D11GeometryShader;
	using D3D_PS_SHADER		= ID3D11PixelShader;
	using D3D_GS_SHADER		= ID3D11GeometryShader;
	using D3D_DS_SHADER		= ID3D11DomainShader;
	using D3D_HS_SHADER		= ID3D11HullShader;
	using D3D_CS_SHADER		= ID3D11ComputeShader;
#endif // DX11

using Microsoft::WRL::ComPtr;
#endif // CLIENT_ONLY


using float4 = struct { float x; float y; float z; float w; };
using float3 = struct { float x; float y; float z; };


#ifdef _UNICODE
	using tstring = std::wstring;
	// using tifstream = wifstream;
	// using tofstream = wofstream;

	using rbyte = wchar_t;
	#define tcout		wcout
	#define tofstream	wofstream
	#define tifstream	wifstream
	#define tatoi		_wtoi
	#define tatof		_wtof
	#define tstrtof		wcstof
	#define tstrlen		wcslen
#else
	using tstring = std::string;
	// using tifstream = ifstream;
	// using tofstream = ofstream;

	using rbyte = char;
	#define tcout		cout
	#define tofstream	ofstream
	#define tifstream	ifstream
	#define tatoi		atoi
	#define tatof		atof
	#define tstrtof		strtof
	#define tstrlen		strlen
#endif