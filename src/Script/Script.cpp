// Script.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include  "pch.h"
#include "ScriptParsing.h"

struct QuestScript
{
	tstring name;
	pair<int,int> level;
};
using CustomType = variant<float, int, tstring>;



int main(int argc, char *argv[])
{
	#pragma region [touch nono]
	string path = argv[1];
	gLocal_path.assign(path.begin(), path.end());
#pragma endregion


	Radar::Script::RScriptParsing script;
	script.read("text.txt");

	bool result = false;

	tstring type;
	if (!script.ScanType(type))
		return 33;

	int i;
	// if (!script.ScanInt(i))
	// 	return 33;

	if (!script.ScanStr(type))
		return 33;

	if (!script.ScanInt(i))
		return 33;

	script.clear();

	QuestScript questScript;

	while (true)
	{
		tstring type;
		tstring buffer;

		if (!script.ScanType(type))
			return 33;

		if (type == _XTT("[name]"))
		{
			if (!script.ScanStr(buffer))
				return 2;
			questScript.name = buffer;
		}
		else if (type == _XTT("[level]"))
		{
			int minLv, maxLv;
			if (!script.ScanInt(minLv))
				return 2;

			if (!script.ScanInt(maxLv))
				return 2;
			questScript.level = make_pair(minLv, maxLv);
		}
		else
		{
			return 2;
		}
	}


	return 1;
}
