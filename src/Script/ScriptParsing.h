#pragma once

/*
	// 참고사이트
	http://yongho1037.tistory.com/513 
	https://modoocode.com/165
*/
#include <fstream>
#include <variant>

#define PARSING_SIZE 512
#define READ_IOS_MODE (ios::in | ios::binary)

#define TAG_START		_XTT('[')
#define TAG_ERROR		_XTT('/')
#define TAG_LAST		_XTT(']')

#define STRING_TAG		_XTT('`')

#define FOOTNOTE_LINE	_XTT("//")
#define FOOTNOTE_START	_XTT("/*")
#define FOOTNOTE_LAST	_XTT("*/")

#define PARSING_END		_XTT('\r')
#define COMMA			_XTT('.')
#define FLOAT_SYMBOL	_XTT('f')


namespace Radar::Script
{
	class RScriptParsing
	{
		using scriptType = variant<float, int, tstring>;

		enum class SCAN_TAG
		{
			NONE,
			ERR,
			NOT,
		};

		enum class TAG_INFO_TPYE
		{
			NONE,
			TAG_NOT,
			DATA_NOT,
			ERR,
		};

		struct parsing
		{
			parsing() { memset(byte, 0, sizeof(byte)); }
			rbyte byte[PARSING_SIZE];
		};

		struct TagInfo
		{
			TagInfo();
			TagInfo operator=(const TagInfo& rhs);
			bool operator==(const TagInfo& rhs);
			void clear();
			
			TAG_INFO_TPYE isVaild() const;
			void push(const scriptType s);
			void pushTag(const tstring s);

			TAG_INFO_TPYE errCode_;
			tstring tag_;
			vector<scriptType> vData;
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
		void re_open();
		bool isFail();
		const SCAN_TAG isTagType(const tstring str) const;
		const bool isStrType(const tstring str) const;
		const bool isIntType(const tstring str) const;
		TagInfo tryMakeTagData(const tstring in);

		virtual bool tryRead(const tstring filName);

	private:
		tifstream		ifs_;
		//vector<parsing>	vParsingData_;
		vector<TagInfo>	vTagData_;
		tstring			fileName_;
		int				failCount_;

		// vector<tstring>	vParsingString_;
	};

}