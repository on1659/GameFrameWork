
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#include <stdlib.h>

namespace Radar
{
	template<typename Ty, std::size_t N>
	constexpr size_t GetArraySize(Ty(&)[N]) noexcept { return N; };

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
			static std::vector<std::byte> ReadCSOFile(const LPCTSTR& path);
			static int ErrorMessage(const HWND& hwnd = nullptr, const LPCTSTR& title = L"", const LPCTSTR& message = L"");
	};

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


	static int32 Memcmp(const void* Buf1, const void* Buf2, SIZE_T Count)
	{
		return memcmp(Buf1, Buf2, Count);
	}

	static void* Memset(void* Dest, uint8 Char, SIZE_T Count)
	{
		return memset(Dest, Char, Count);
	}

	static void* Memzero(void* Dest, SIZE_T Count)
	{
		return memset(Dest, 0, Count);
	}

	static void* Memcpy(void* Dest, const void* Src, SIZE_T Count)
	{
		return memcpy(Dest, Src, Count);
	}

}

