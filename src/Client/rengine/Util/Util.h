
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#include <stdlib.h>

namespace Radar
{
	template<typename Ty, std::size_t N>
	constexpr size_t GetArraySize(Ty(&)[N]) noexcept { return N; };

	static void c_blue() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000b); }
	static void c_red() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000c); }
	static void c_white() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000f); }
	static void c_default() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); }

	static int random(const int& start, const int& end)
	{
		return ((rand() % (end - start) + start + 1));
	}

	void print(const std::string& msg);

	void print(const std::wstring& msg);

	void convertTChar(const char* pstrSrc, wchar_t pwstrDest[])
	{
		int nLen = (int)strlen(pstrSrc) + 1;
		//mbstowcs(pwstrDest, pstrSrc, nLen);
	}

	void convertChar(const TCHAR* pwstrSrc, char pstrDest[])
	{
		const int len = static_cast<int>(wcslen(pwstrSrc));
		WideCharToMultiByte(CP_ACP, 0, pwstrSrc, len, pstrDest, len, NULL, NULL);
	}

	namespace Math
	{
		inline XMFLOAT3 XMVectorToFloat3(XMVECTOR& xmvVector)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, xmvVector);
			return(xmf3Result);
		}

		inline XMFLOAT3 ScalarProduct(XMFLOAT3& xmf3Vector, float fScalar, bool bNormalize = true)
		{
			XMFLOAT3 xmf3Result;
			if (bNormalize)
				XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)) * fScalar);
			else
				XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector) * fScalar);
			return(xmf3Result);
		}

		inline XMFLOAT3 Add(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + XMLoadFloat3(&xmf3Vector2));
			return(xmf3Result);
		}

		inline XMFLOAT3 Add(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2, float fScalar)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + (XMLoadFloat3(&xmf3Vector2) * fScalar));
			return(xmf3Result);
		}

		inline XMFLOAT3 Subtract(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) - XMLoadFloat3(&xmf3Vector2));
			return(xmf3Result);
		}

		inline float DotProduct(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, XMVector3Dot(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
			return(xmf3Result.x);
		}

		inline XMFLOAT3 CrossProduct(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2, bool bNormalize = true)
		{
			XMFLOAT3 xmf3Result;
			if (bNormalize)
				XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2))));
			else
				XMStoreFloat3(&xmf3Result, XMVector3Cross(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
			return(xmf3Result);
		}

		inline XMFLOAT3 Normalize(XMFLOAT3& xmf3Vector)
		{
			XMFLOAT3 m_xmf3Normal;
			XMStoreFloat3(&m_xmf3Normal, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)));
			return(m_xmf3Normal);
		}

		inline float Length(XMFLOAT3& xmf3Vector)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, XMVector3Length(XMLoadFloat3(&xmf3Vector)));
			return(xmf3Result.x);
		}

		inline float Angle(XMVECTOR& xmvVector1, XMVECTOR& xmvVector2)
		{
			XMVECTOR xmvAngle = XMVector3AngleBetweenNormals(xmvVector1, xmvVector2);
			return(XMConvertToDegrees(acosf(XMVectorGetX(xmvAngle))));
		}

		inline XMFLOAT3 TransformNormal(XMFLOAT3& xmf3Vector, XMMATRIX& xmmtxTransform)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, XMVector3TransformNormal(XMLoadFloat3(&xmf3Vector), xmmtxTransform));
			return(xmf3Result);
		}

		inline XMFLOAT3 TransformCoord(XMFLOAT3& xmf3Vector, XMMATRIX& xmmtxTransform)
		{
			XMFLOAT3 xmf3Result;
			XMStoreFloat3(&xmf3Result, XMVector3TransformCoord(XMLoadFloat3(&xmf3Vector), xmmtxTransform));
			return(xmf3Result);
		}

		inline XMFLOAT3 TransformCoord(XMFLOAT3& xmf3Vector, XMFLOAT4X4& xmmtx4x4Matrix)
		{
			return TransformCoord(xmf3Vector, xmmtx4x4Matrix);
		}

		inline XMFLOAT4 Add(XMFLOAT4& xmf4Vector1, XMFLOAT4& xmf4Vector2)
		{
			XMFLOAT4 xmf4Result;
			XMStoreFloat4(&xmf4Result, XMLoadFloat4(&xmf4Vector1) + XMLoadFloat4(&xmf4Vector2));
			return(xmf4Result);
		}

		inline XMFLOAT4X4 Identity()
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixIdentity());
			return(xmmtx4x4Result);
		}

		inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * XMLoadFloat4x4(&xmmtx4x4Matrix2));
			return(xmmtx4x4Result);
		}

		inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMMATRIX& xmmtxMatrix2)
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * xmmtxMatrix2);
			return(xmmtx4x4Result);
		}

		inline XMFLOAT4X4 Multiply(XMMATRIX& xmmtxMatrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, xmmtxMatrix1 * XMLoadFloat4x4(&xmmtx4x4Matrix2));
			return(xmmtx4x4Result);
		}

		inline XMFLOAT4X4 Inverse(XMFLOAT4X4& xmmtx4x4Matrix)
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixInverse(NULL, XMLoadFloat4x4(&xmmtx4x4Matrix)));
			return(xmmtx4x4Result);
		}

		inline XMFLOAT4X4 Transpose(XMFLOAT4X4& xmmtx4x4Matrix)
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixTranspose(XMLoadFloat4x4(&xmmtx4x4Matrix)));
			return(xmmtx4x4Result);
		}

		inline XMFLOAT4X4 PerspectiveFovLH(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ));
			return(xmmtx4x4Result);
		}

		inline XMFLOAT4X4 LookAtLH(XMFLOAT3& xmf3EyePosition, XMFLOAT3& xmf3LookAtPosition, XMFLOAT3& xmf3UpDirection)
		{
			XMFLOAT4X4 xmmtx4x4Result;
			XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixLookAtLH(XMLoadFloat3(&xmf3EyePosition), XMLoadFloat3(&xmf3LookAtPosition), XMLoadFloat3(&xmf3UpDirection)));
			return(xmmtx4x4Result);
		}
	};

	class Util
	{
		public:

			static D3DBuffer *CreateBuffer(D3DDevice *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList,  void *pData, UINT nBytes, D3D12_HEAP_TYPE d3dHeapType, D3D12_RESOURCE_STATES d3dResourceStates, D3DBuffer **ppd3dUploadBuffer);
			static D3DBuffer *CreateBuffer(void *pData, UINT nBytes, D3D12_HEAP_TYPE d3dHeapType, D3D12_RESOURCE_STATES d3dResourceStates, D3DBuffer **ppd3dUploadBuffer);
			static D3DBuffer* CreateTexture(D3DDevice *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, tstring pszFileName, D3DBuffer **ppd3dUploadBuffer, D3D12_RESOURCE_STATES d3dResourceStates);

			static D3DBuffer				*gCbWorldMatrix;
			static D3DBuffer				*gCbMaterialColors;
			static XMMATRIX					 gCbd3dxmtxIdentity;
			static XMFLOAT4					 gCbd3dxmf4Color;

			static void Global_CreateConstBuffers();
			static void Global_ReleaseConstBuffers();
			static void Global_WorldMatrixUpdateConstBuffer(XMMATRIX& pd3dxmtxWorld);
			//static void Global_MaterialColorUpdateConstBuffer(CMaterialColors *pMaterialColors);

			static std::vector<std::byte> ReadCSOFile(const LPCTSTR& path);

			static int ErrorMessage(const HWND& hwnd = nullptr, const LPCTSTR& title = L"", const LPCTSTR& message = L"");
	
	};

	inline void DXUT_SetDebugName(IDXGIObject* pObj, const CHAR* pstrName)
	{
		if (pObj)
			pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
	}
	inline void DXUT_SetDebugName(ID3D10Device* pObj, const CHAR* pstrName)
	{
		if (pObj)
			pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
	}
	inline void DXUT_SetDebugName(ID3D10DeviceChild* pObj, const CHAR* pstrName)
	{
		if (pObj)
			pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
	}
	inline void DXUT_SetDebugName(ID3D11Device* pObj, const CHAR* pstrName)
	{
		if (pObj)
			pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
	}
	inline void DXUT_SetDebugName(ID3D11DeviceChild* pObj, const CHAR* pstrName)
	{
		if (pObj)
			pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
	}
	
	static bool getFileExt(std::string& output, const std::string& path)
	{
		output.clear();
		char ext[10];
		_splitpath_s(path.c_str(), NULL, 0, NULL, 0, NULL, 0, ext, 10);
		//_wsplitpath(path.c_str(), NULL, NULL, name, NULL);
		output = ext;
		return !(output.empty());
	}

	static bool getFileName(std::string& output, const std::string& path)
	{
		output.clear();
		char name[100];
		_splitpath_s(path.c_str(), NULL,    0, NULL,    0, name, 100, NULL, NULL);
		//_wsplitpath(path.c_str(), NULL, NULL, name, NULL);
		output = name;
		return !(output.empty());
	}
	static bool getFileName(std::wstring& output, const std::wstring& path)
	{
		output.clear();
		TCHAR name[100];
		_wsplitpath_s(path.c_str(), NULL, NULL, NULL, NULL, name, 100, NULL, NULL);
		//path		dirve drivesize  directory   dirSize  fileName  filenameSize exe  exesize
		//_wsplitpath(path.c_str(), NULL, NULL, name, NULL);
		output = name;
		return !(output.empty());
	}


	static BYTE *ReadCompiledEffectFile(WCHAR *pszFileName, size_t *pnReadBytes)
	{
		FILE *pFile = NULL;
		::_wfopen_s(&pFile, pszFileName, L"rb");
		::fseek(pFile, 0, SEEK_END);
		int nFileSize = ::ftell(pFile);
		BYTE *pByteCode = new BYTE[nFileSize];
		::rewind(pFile);
		*pnReadBytes = ::fread(pByteCode, sizeof(BYTE), nFileSize, pFile);
		::fclose(pFile);
		return(pByteCode);
	}

	static ComPtr<ID3DBlob> CompileShader(
		const std::wstring& filename,
		const D3D_SHADER_MACRO* defines,
		const std::string& entrypoint,
		const std::string& target)
	{
		UINT compileFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)  
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		HRESULT hr = S_OK;

		ComPtr<ID3DBlob> byteCode = nullptr;
		ComPtr<ID3DBlob> errors;
		hr = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &errors);

		if (errors != nullptr)
			OutputDebugStringA((char*)errors->GetBufferPointer());
		if (hr != S_OK)
		{
			cout << errors << endl;
		}

		return byteCode;
	}

	static UINT CalcConstantBufferByteSize(UINT byteSize)
	{
		// Constant buffers must be a multiple of the minimum hardware
		// allocation size (usually 256 bytes).  So round up to nearest
		// multiple of 256.  We do this by adding 255 and then masking off
		// the lower 2 bytes which store all bits < 256.
		// Example: Suppose byteSize = 300.
		// (300 + 255) & ~255
		// 555 & ~255
		// 0x022B & ~0x00ff
		// 0x022B & 0xff00
		// 0x0200
		// 512
		return (byteSize + 255) & ~255;
	}

	static void ChornoTime(bool start = true, const std::string& msg = "time : ", const DWORD& TIME_UNIT = TIME_UNIT::UINT_NANO)
	{
		//C++ 11? 14 최신 문법으로 함수내 선언한 static 변수가 전역으로 잡힘
		static std::chrono::high_resolution_clock::time_point gStart;

		if (start) gStart = std::chrono::high_resolution_clock::now();

		else
		{
			auto gTotal_time = std::chrono::high_resolution_clock::now() - gStart;

			std::cout << msg;

			if (TIME_UNIT & TIME_UNIT::UINT_NANO) std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(gTotal_time).count() << " nanoseconds ";
			if (TIME_UNIT & TIME_UNIT::UNIT_MICRO) std::cout << std::chrono::duration_cast<std::chrono::microseconds>(gTotal_time).count() << " microseconds ";
			if (TIME_UNIT & TIME_UNIT::UINT_MS) std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(gTotal_time).count() << " milliseconds ";
			if (TIME_UNIT & TIME_UNIT::UINT_SEC) std::cout << std::chrono::duration_cast<std::chrono::seconds>(gTotal_time).count() << " seconds ";
			if (TIME_UNIT & TIME_UNIT::UINT_MIN) std::cout << std::chrono::duration_cast<std::chrono::minutes>(gTotal_time).count() << " minutes ";
			if (TIME_UNIT & TIME_UNIT::UINT_HOUR) std::cout << std::chrono::duration_cast<std::chrono::hours>(gTotal_time).count() << " hours ";

			std::cout << std::endl;


		}

	}
	static void TimeRecord(bool start = true, const std::string& msg = "time : ", const DWORD& time_unit = UINT_NANO)
	{
		ChornoTime(start, msg, time_unit);
	}


}

