
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#include "PreComplie.h"

#include <vector>
#include <DirectXMath.h>

#include "Util.h"
#include "task/MyFlag.h"
#include "task/MyDefine.h"
#include "task/MyClientDefine.h"
#include "task/MyEnum.h"

#include <fstream>

using namespace Radar;

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