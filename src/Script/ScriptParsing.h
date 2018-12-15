#pragma once

class RScriptParsing
{
	struct parsing
	{
		rbyte* operator()() { return byte; }
		rbyte byte[512];
	};

public:
	RScriptParsing();
	virtual ~RScriptParsing();

	virtual void start();
	virtual bool tryRead(const string filName);
	virtual bool tryRead(const tstring filName);
	virtual void read(const string filName);
	virtual void read(const tstring filName);
	virtual void clear();

private:
	vector<parsing>	vParsingData_;
	tstring			fileName_;
};

