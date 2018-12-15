#include "pch.h"
#include "ScriptParsing.h"

#include <fstream>

RScriptParsing::RScriptParsing()
{
	clear();
}

RScriptParsing::~RScriptParsing()
{
	clear();
}

void RScriptParsing::start()
{
}

void RScriptParsing::clear()
{
	ifs_.close();
	fileName_.clear();
	vParsingData_.clear();
}

bool RScriptParsing::ScanType(tstring& tag) 
{
	if (!isOpen()) 
		return false;

	tstring str;
	ifs_ >> str;

	if (!isTagType(str))
		return false;

	tag = str;
	return true;
}

bool RScriptParsing::ScanInt(int& data)
{
	if (!isOpen()) return false;
	int n = -1;
	ifs_ >> n;
	data = n;
	return true;
}

bool RScriptParsing::ScanStr(tstring& data)
{
	if (!isOpen()) return false;
	tstring tstr;
	ifs_ >> tstr;
	data = tstr;
	return true;
}


void RScriptParsing::read(const string fileName)
{
	string path = fileName;
	return read(tstring(path.begin(), path.end()));
}
void RScriptParsing::read(const tstring fileName)
{
	if (!tryRead(fileName))
		return;

	cout << "size : " << vParsingData_.size() << endl;
	for (auto c : vParsingData_)
	{
		tcout << c.byte << endl;
	}
	cout << endl;

}
bool RScriptParsing::isOpen()
{
	if (!ifs_.is_open())
		re_open();
	return ifs_.is_open();
}
void RScriptParsing::re_open()
{
	if (!ifs_.is_open())
		ifs_.open(tstring(gLocal_path + fileName_), READ_IOS_MODE);
}

bool RScriptParsing::isTagType(tstring& str)
{
	if (str.size() < 3)	// [!] 최소 이렇게 3글자
		return false;

	string::size_type tag_end = 0;

	// TAG_START가 두개 이상있어도 에러
	if (str.find(TAG_START) > 0)
		return false;

	if (str.find(TAG_ERROR) > string::npos)
		return false;

	if ((tag_end = str.find(TAG_LAST)) < string::npos)
	{
		if (tag_end < 2) // `][` or `]` or `[]` 이런 태그 검사
			return false;
	}

	return true;
}

bool RScriptParsing::tryRead(const tstring fileName)
{
	fileName_ = fileName;
	bool result = false;
	tstring fullPath = gLocal_path;
	fullPath += fileName_;
	
	ifs_.open(fullPath.c_str(), READ_IOS_MODE);
	if (ifs_.is_open())
	{
		while (!ifs_.eof())
		{
			parsing par;
			ifs_.getline(par.byte, PARSING_SIZE);
			vParsingData_.push_back(par);
		}

		ifs_.close();
		result = true;
	}

	if (!result)
	{
		Radar::c_red();
		tcout << _XTT("read errror : ") << fullPath << endl;
		Radar::c_default();
	}

	return result;
}

