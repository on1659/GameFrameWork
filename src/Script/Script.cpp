// Script.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include  "pch.h"
#include "ScriptParsing.h"

int main(int argc, char *argv[])
{
	#pragma region [touch nono]
	string path = argv[1];
	gLocal_path.assign(path.begin(), path.end());
#pragma endregion


	RScriptParsing script;
	script.read("text.txt");

	return 1;
}
