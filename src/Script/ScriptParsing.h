#pragma once

#include <fstream>

#define PARSING_SIZE 512
#define READ_IOS_MODE (ios::in | ios::binary)

#define TAG_START _XTT("[")
#define TAG_ERROR _XTT("/")
#define TAG_LAST _XTT("]")

class RScriptParsing
{
	struct parsing
	{
		parsing() { memset(byte, 0, sizeof(byte)); }
		rbyte byte[PARSING_SIZE];
	};

public:
	RScriptParsing();
	virtual ~RScriptParsing();
	virtual void start();
	virtual void clear();

public:
	bool ScanType(tstring& msg);
	bool ScanInt(int& data);
	bool ScanStr(tstring& data);

	template<class T>
	bool ScanData(T& data)
	{
		if (!isOpen()) return false;

		T str;
		ifs_ >> str;

		data = str;
		return true;
	}


	virtual void read(const string filName);
	virtual void read(const tstring filName);
private:
	bool isOpen();
	void re_open() ;
	bool isTagType(tstring& str);
	virtual bool tryRead(const tstring filName);

private:
	tifstream		ifs_;
	vector<parsing>	vParsingData_;
	tstring			fileName_;
};

