
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

using float4 = struct { float x; float y; float z; float w; };
using float3 = struct { float x; float y; float z; };

using  S8 = signed char;
using  U8 = unsigned char;

using  S16 = signed short;
using  U16 = unsigned short;

using  S32 = signed int;
using  U32 = unsigned int;

using  F32 = float;
using  F64 = double;

using UI32 = unsigned int;

static const F32 Float_One = F32(1.0);									///< Constant float 1.0
static const F32 Float_Half = F32(0.5);									///< Constant float 0.5
static const F32 Float_Zero = F32(0.0);									///< Constant float 0.0
static const F32 Float_Pi = F32(3.14159265358979323846);				///< Constant float PI
static const F32 Float_2Pi = F32(2.0 * 3.14159265358979323846);			///< Constant float 2*PI
static const F32 Float_InversePi = F32(1.0 / 3.14159265358979323846);	///< Constant float 1 / PI
static const F32 Float_HalfPi = F32(0.5 * 3.14159265358979323846);		///< Constant float 1/2 * PI
static const F32 Float_2InversePi = F32(2.0 / 3.14159265358979323846);	///< Constant float 2 / PI
static const F32 Float_Inverse2Pi = F32(0.5 / 3.14159265358979323846);	///< Constant float 0.5 / PI

static const F32 Float_Sqrt2 = F32(1.41421356237309504880f);			///< Constant float sqrt(2)
static const F32 Float_SqrtHalf = F32(0.7071067811865475244008443f);	///< Constant float sqrt(0.5)

static const S8  S8_MIN = S8(-128);										 ///< Constant Min Limit S8
static const S8  S8_MAX = S8(127);										 ///< Constant Max Limit S8
static const U8  U8_MAX = U8(255);										 ///< Constant Max Limit U8

static const S16 S16_MIN = S16(-32768);                           ///< Constant Min Limit S16
static const S16 S16_MAX = S16(32767);                            ///< Constant Max Limit S16
static const U16 U16_MAX = U16(65535);                            ///< Constant Max Limit U16

static const S32 S32_MIN = S32(-2147483647 - 1);                  ///< Constant Min Limit S32
static const S32 S32_MAX = S32(2147483647);                       ///< Constant Max Limit S32
static const U32 U32_MAX = U32(0xffffffff);                       ///< Constant Max Limit U32

static const F32 F32_MIN = F32(1.175494351e-38F);                 ///< Constant Min Limit F32
static const F32 F32_MAX = F32(3.402823466e+38F);                 ///< Constant Max Limit F32
