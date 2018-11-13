
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

// -- Enum -- //

enum class WARP_RESULT_ENUM
{
	   OK		= 0
	,  FAIL		
	,  NOT_FOUND_GRAPHIC
	,  FAIL_QUERY_INTERFACE
	,  FAIL_CREATE_SWAP_CHAIN
	,  FAIL_CREATE_DXGI_FACTORY_
	,  FAIL_GET_BUFFER
	,  FAIL_CREATE_RTV
	,  FAIL_CREATE_RS
	,  FAIL_CREATE_BS // Bleand States
	,  FAIL_CREATE_DSV
	,  FAIL_CREATE_TXT2D
	,  FAIL_CREATE_VS
	,  FAIL_CREATE_HS
	,  FAIL_CREATE_DS
	,  FAIL_CREATE_GS
	,  FAIL_CREATE_PS
	,  FAIL_LATE_START 
};


// Line 까지 기재해주면 좋을 것 같다.
class CWarpResultHash
{
public:
	static tstring Error_Message(const WARP_RESULT_ENUM& result)
	{
		switch (result)
		{
			case WARP_RESULT_ENUM::OK:
				return _XTT("OK");

			case WARP_RESULT_ENUM::FAIL:
				return _XTT("FAIL");

			case WARP_RESULT_ENUM::NOT_FOUND_GRAPHIC:
				return _XTT("NOT_FOUND_GRAPHIC");

			case WARP_RESULT_ENUM::FAIL_QUERY_INTERFACE:
				return _XTT("FAIL_QUERY_INTERFACE");

			case WARP_RESULT_ENUM::FAIL_CREATE_SWAP_CHAIN:
				return _XTT("FAIL_CREATE_SWAP_CHAIN");

			case WARP_RESULT_ENUM::FAIL_CREATE_DXGI_FACTORY_:
				return _XTT("FAIL_CREATE_DXGI_FACTORY_");

			case WARP_RESULT_ENUM::FAIL_GET_BUFFER:
				return _XTT("FAIL_GET_BUFFER");

			case WARP_RESULT_ENUM::FAIL_CREATE_RTV:
				return _XTT("FAIL_CREATE_RTV");

			case WARP_RESULT_ENUM::FAIL_CREATE_RS:
				return _XTT("FAIL_CREATE_RS");

			case WARP_RESULT_ENUM::FAIL_CREATE_BS:
				return _XTT("FAIL_CREATE_BLENDSTATE");

			case WARP_RESULT_ENUM::FAIL_CREATE_DSV:
				return _XTT("FAIL_CREATE_DSV");

			case WARP_RESULT_ENUM::FAIL_CREATE_TXT2D:
				return _XTT("FAIL_CREATE_TEXTURE2D");

			case WARP_RESULT_ENUM::FAIL_CREATE_VS:
				return _XTT("FAIL_CREATE_VS");

			case WARP_RESULT_ENUM::FAIL_CREATE_HS:
				return _XTT("FAIL_CREATE_HS");

			case WARP_RESULT_ENUM::FAIL_CREATE_DS:
				return _XTT("FAIL_CREATE_DS");

			case WARP_RESULT_ENUM::FAIL_CREATE_GS:
				return _XTT("FAIL_CREATE_GS");

			case WARP_RESULT_ENUM::FAIL_CREATE_PS:
				return _XTT("FAIL_CREATE_PS");

			case WARP_RESULT_ENUM::FAIL_LATE_START:
				return _XTT("FAIL_LATE_START");

		}
		return _XTT("Not Found Error");
	}
};

class CWARPResult
{
public:
	constexpr CWARPResult(const WARP_RESULT_ENUM& state = WARP_RESULT_ENUM::OK) : state(state) { }
	const constexpr bool operator==(const CWARPResult& other) const { return (state == other.state); }
	const constexpr bool operator==(const WARP_RESULT_ENUM& other) const { return (state == other); }
	const constexpr bool operator!=(const WARP_RESULT_ENUM& other) const { return (state != other); }

	static WARP_RESULT_ENUM RETURN(const WARP_RESULT_ENUM& res, const char* err = __FILE__, const int& line = __LINE__, const TCHAR* message = _XTT(""))
	{
		if (res != WARP_RESULT_ENUM::OK) 
			return FAIL(res, err, line, message);
		return OK(); 
	}

	static WARP_RESULT_ENUM OK() { return WARP_RESULT_ENUM::OK; }
	static WARP_RESULT_ENUM FAIL() { return WARP_RESULT_ENUM::FAIL; }
	static WARP_RESULT_ENUM FAIL(const WARP_RESULT_ENUM& err_enum, const char* err = __FILE__, const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, err_enum, message);  return WARP_RESULT_ENUM::FAIL; }
	static WARP_RESULT_ENUM FAIL(const char* err, const int& line, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL, message);  return WARP_RESULT_ENUM::FAIL; }
	static WARP_RESULT_ENUM FAIL_CREATE_RS(const char* err = __FILE__, const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL_CREATE_RS, message);  return WARP_RESULT_ENUM::FAIL_CREATE_RS; }
	static WARP_RESULT_ENUM FAIL_CREATE_BS(const char* err = __FILE__, const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL_CREATE_BS, message);  return WARP_RESULT_ENUM::FAIL_CREATE_BS; }
	static WARP_RESULT_ENUM FAIL_CREATE_DSV(const char* err = __FILE__, const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL_CREATE_DSV, message);  return WARP_RESULT_ENUM::FAIL_CREATE_DS; }

	static WARP_RESULT_ENUM FAIL(const WARP_RESULT_ENUM& err_enum, const TCHAR* err = _XTT(__FILE__), const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, err_enum, message);  return WARP_RESULT_ENUM::FAIL; }
	static WARP_RESULT_ENUM FAIL(const TCHAR* err, const int& line, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL, message);  return WARP_RESULT_ENUM::FAIL; }
	static WARP_RESULT_ENUM FAIL_CREATE_RS(const TCHAR* err = _XTT(__FILE__), const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL_CREATE_RS, message);  return WARP_RESULT_ENUM::FAIL_CREATE_RS; }
	static WARP_RESULT_ENUM FAIL_CREATE_BS(const TCHAR* err = _XTT(__FILE__), const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL_CREATE_BS, message);  return WARP_RESULT_ENUM::FAIL_CREATE_BS; }
	static WARP_RESULT_ENUM FAIL_CREATE_DSV(const TCHAR* err = _XTT(__FILE__), const int& line = __LINE__, const TCHAR* message = _XTT("")) { print(err, line, WARP_RESULT_ENUM::FAIL_CREATE_DSV, message);  return WARP_RESULT_ENUM::FAIL_CREATE_DS; }


private:

	static void setColorblue()    { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000b); }
	static void setColorred()     { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000c); }
	static void setColorwhite()   { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000f); }
	static void setColordefault() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); }

	static void print(const char* err,const int& line, const WARP_RESULT_ENUM& re_enum, const TCHAR* message)
	{
		TCHAR name[100];
		TCHAR exe[5];
		std::string str = err;
		std::wstring wstr;
		wstr.reserve(str.size());
		wstr.assign(str.begin(), str.end());
		_wsplitpath_s(wstr.c_str(), nullptr, 0U, nullptr, 0U, name, 100, exe, 5);


		setColorwhite();
		std::wcout << _XTT("Error Type (");
		setColorred();
		std::wcout << CWarpResultHash::Error_Message(re_enum);
		setColorwhite();
		std::wcout << _XTT(") File : ");
		setColorblue();
		std::wcout << name << exe;

		setColorwhite();
		std::wcout << _XTT(" - (");
		
		setColorred();
		std::wcout << line;
		
		setColorwhite();
		std::wcout << _XTT(") ") << message << std::endl;

		setColordefault();
	}

	static void print(const TCHAR* err, const int& line, const WARP_RESULT_ENUM& re_enum, const TCHAR* message)
	{
		TCHAR name[100];
		TCHAR exe[5];
		std::wstring wstr = err;

		setColorwhite();
		std::wcout << _XTT("Error Type (");
		setColorred();
		std::wcout << CWarpResultHash::Error_Message(re_enum);
		setColorwhite();
		std::wcout << _XTT(") File : ");
		setColorblue();
		std::wcout << name << exe;

		setColorwhite();
		std::wcout << _XTT(" - (");

		setColorred();
		std::wcout << line;

		setColorwhite();
		std::wcout << _XTT(") ") << message << std::endl;

		setColordefault();
	}

private:
	const WARP_RESULT_ENUM state;

};


// -- Enum -- //


// ------------------------ Slot ------------------------ \\


	enum VS_SHADER_SLOT
	{
		  VS_CB_SLOT_CAMERA_PROJECTION	= 0x00
		, VS_CB_SLOT_WORLD_MATRIX		= 0x02
		, VS_CB_SLOT_TEXTURE_MATRIX		= 0x03
	};

	enum GS_SHADER_SLOT
	{
		GS_CB_SLOT_CAMERA_PROJECTION = 0x00
	};

	enum DS_SHADER_SLOT
	{
		  DS_CB_SLOT_CAMERA_PROJECTION  = 0x00
		, DS_CB_SLOT_LIGHT_CB			= 0x02
		,
	};

	enum HS_SHADER_SLOT
	{

	};

	enum PS_SHADER_SLOT
	{
		  PS_CB_SLOT_UNPACKET_CAMERA	  = 0x01
		, PS_CB_SLOT_LIGHT_CB			  = 0x02
		, PS_CB_SLOT_MATERIAL			  = 0x03
		,
	};



// ------------------------ Slot ------------------------ \\


#pragma region [Light]

	enum class LIGHT_ID
	{
		  LIGHT_DIRECTIONAL
		, LIGHT_POINT
		, LIGHT_SPOT
		, LIGHT_CAPSULE
		, LIGHT_END
	};

	enum LIGHT_TYPE
	{
		  LIGHT_TYPE_POINT = 0
		, LIGHT_TYPE_SPOT			
		, LIGHT_TYPE_DIRECTIONAL	
		, LIGHT_TYPE_SHADOW	
	};

	enum PACK_UNPACKK_BUFFER
	{
		UNPACK_BUFFER_SLOT = 0x09
	};

#pragma endregion
		
#pragma region[Shader Bind Flag]

	enum Shader_Bind_Flag
	{		
		    SHADER_BIND_NOT = 0b0000000000	// 00
		,	SHADER_BIND_VS	= 0b0000000001	// 01
		,	SHADER_BIND_HS	= 0b0000000010	// 02
		,	SHADER_BIND_DS  = 0b0000000100	// 04
		,	SHADER_BIND_GS  = 0b0000001000	// 08
		,	SHADER_BIND_PS  = 0b0000010000	// 16
		,	SHADER_BIND_CS  = 0b0000100000	// 32
	};

#pragma endregion


// ------------------------ Slot ------------------------ \\

enum TIME_UNIT
{
	  UINT_NANO  = 0x00000001
	, UNIT_MICRO = 0x00000002
	, UINT_MS    = 0x00000004
	, UINT_SEC   = 0x00000010
	, UINT_MIN   = 0x00000020
	, UINT_HOUR  = 0x00000040
};
