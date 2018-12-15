#include "pch.h"
#include "ScriptParsing.h"

#include <fstream>
RScriptParsing::RScriptParsing()
{
}

RScriptParsing::~RScriptParsing()
{
	clear();
}

void RScriptParsing::start()
{
}

bool RScriptParsing::tryRead(const string fileName)
{
	string path = fileName;
	return tryRead(tstring(path.begin(), path.end()));
}

bool RScriptParsing::tryRead(const tstring fileName)
{
	fileName_ = fileName;
	bool result = false;
	tstring fullPath = gLocal_path;
	fullPath += fileName_;
	
	wifstream ifs(fullPath.c_str(), ios::binary);
	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			//
			parsing par;
			ifs.getline(par.byte, 512);

			vParsingData_.push_back(par);
		}

		ifs.close();
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

void RScriptParsing::clear()
{
	fileName_.clear();
	vParsingData_.clear();
}

