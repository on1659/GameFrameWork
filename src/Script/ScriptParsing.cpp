#include "pch.h"
#include "ScriptParsing.h"

#include <fstream>
#include <cstdlib>

namespace Radar::Script
{
	RScriptParsing::TagInfo::TagInfo()
	{
		clear();
	}

	RScriptParsing::TagInfo Radar::Script::RScriptParsing::TagInfo::operator=(const TagInfo& rhs)
	{
		tag_ = rhs.tag_;
		for (auto iter : rhs.dataMap_)
		{
			vector<scriptType> v;
			for (auto it : iter.second)
				v.push_back(it);
			dataMap_.insert(make_pair(iter.first, v));
		}
		return *this;
	}

	bool RScriptParsing::TagInfo::operator==(const TagInfo& rhs)
	{
		if (tag_.find(rhs.tag_) > string::npos)
			return false;

		if (dataMap_.size() != rhs.dataMap_.size())
			return false;

		int i = 0;
		for (auto iter : rhs.dataMap_)
		{
			auto findIter = dataMap_.find(iter.first);
			if (findIter == rhs.dataMap_.end())
				return false;

			if (findIter->second.size() != iter.second.size())
				return false;

			for (int i = 0; i < findIter->second.size(); ++i)
			{
				if (findIter->second[i] != iter.second[i])
					return false;
			}
		}

		return true;
	}

	void RScriptParsing::TagInfo::clear()
	{
		tag_.clear();
		dataMap_.clear();
		errCode_ = TAG_INFO_TPYE::NONE;
	}


	 RScriptParsing::TAG_INFO_TPYE RScriptParsing::TagInfo::isVaild() const
	{
		if (dataMap_.empty())
			return TAG_INFO_TPYE::DATA_NOT;
		if (tag_.empty())
			return TAG_INFO_TPYE::TAG_NOT;
		return errCode_;
	}

	void RScriptParsing::TagInfo::push(const scriptType s)
	{
		dataMap_[s.index()].push_back(s);

		// dataMap_.insert(make_pair(s.index(), s));
		// vData.push_back(s);
	}

	void RScriptParsing::TagInfo::pushTag(const tstring s)
	{
		if (s.empty())
		{
			errCode_ = TAG_INFO_TPYE::TAG_NOT;
		}
		else
		{
			errCode_ = TAG_INFO_TPYE::NONE;
			tag_ = s;
		}
	}

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
		// vParsingData_.clear();
		vTagData_.clear();
		failCount_ = 0;
	}

	bool RScriptParsing::ScanType(tstring& tag)
	{
		if (!isOpen())
			return false;

		tstring str;
		ifs_ >> str;

		if (isTagType(str) != SCAN_TAG::NONE)
			return false;

		tag = str;
		return true;
	}

	bool RScriptParsing::ScanInt(int& data)
	{
		if (!isOpen()) return false;
		int n = -1;

		ifs_ >> n;

		if (ifs_.fail())
			return false;

		data = n;
		return true;
	}

	bool RScriptParsing::ScanStr(tstring& data)
	{
		if (!isOpen()) return false;
		tstring tstr;
		ifs_ >> tstr;

		if (ifs_.fail() && !isStrType(tstr))
			return false;

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

		for (auto d : vTagData_)
		{
			//wcout << d.tag_ << "--";
		}
	}
	bool RScriptParsing::isOpen()
	{
		return ifs_.is_open();
	}
	void RScriptParsing::re_open()
	{
		if (!ifs_.is_open())
			ifs_.open(tstring(gLocal_path + fileName_), READ_IOS_MODE);
	}

	bool RScriptParsing::isFail()
	{
		return false;
	}

	const RScriptParsing::SCAN_TAG RScriptParsing::isTagType(const tstring str) const
	{
		if (str.size() < 3)	// [!] 최소 이렇게 3글자
			return SCAN_TAG::ERR;

		string::size_type tag_end = 0;
		

		string::size_type tag_start;
		if ((tag_start = str.find(TAG_START)) > 0)
		{
			if (tag_start < string::npos) // .] 이런것도 에러
				return SCAN_TAG::ERR;
		}

		if (str.find(TAG_ERROR) > string::npos)
			return SCAN_TAG::ERR;

		if ((tag_end = str.find(TAG_LAST)) < string::npos)
		{
			if (tag_end < 2) // `][` or `]` or `[]` 이런 태그 검사
				return SCAN_TAG::ERR;
		}
		else
		{
			return SCAN_TAG::NOT;
		}

		return SCAN_TAG::NONE;
	}

	const bool RScriptParsing::isStrType(const tstring str) const
	{
		size_t size = str.size();

		if (size < 3)		// `!` 이런식으로 3글자
			return false;

		string::size_type strTag = 0;
		while ((strTag = str.find(STRING_TAG)) < string::npos)
		{
			if (strTag != 0 && strTag != size)
				return false;
		}

		return false;
	}

	const bool RScriptParsing::isIntType(const tstring str) const
	{
		return true;
	}

	RScriptParsing::TagInfo RScriptParsing::tryMakeTagData(const tstring in)
	{
		tstring inTemp = in;
		size_t curPivot = 0;

		TagInfo info;

		while (true)
		{
			tstring temp(inTemp.begin() + curPivot, inTemp.end());

			if (temp.empty())
				break;

			if (temp[0] == _XTT(' '))
			{
				curPivot++;
				continue;
			}

			string::size_type parsingEnd = 0;
			if ((parsingEnd = temp.find(PARSING_END)) < 1)
			{
				if (parsingEnd < string::npos)
					return info;
			}

			if ((parsingEnd = temp.find(FOOTNOTE_LINE)) < 1)
			{
				if (parsingEnd < string::npos)
					return info;
			}

			SCAN_TAG type = isTagType(temp);
			if (type == SCAN_TAG::NONE)
			{
				string::size_type tag_end = 0;
				auto iter = temp.begin();
				if ((tag_end = temp.find(TAG_LAST, tag_end)) < string::npos)
				{
					info.pushTag(tstring(temp.begin(), temp.begin() + (tag_end + 1)));
					curPivot = (tag_end + 1);
				}
			}

			else if (type == SCAN_TAG::ERR)
			{
				info.errCode_ = TAG_INFO_TPYE::ERR;
				info.clear();
				break;
			}

			// string check
			else
			{
				// string check
				string::size_type strSize;
				if (temp.find(STRING_TAG) < 1)
				{
					// 처음 ` 뺴고
					if ((strSize = temp.find(STRING_TAG, 1)) < string::npos)
					{
						tstring str;
						str.assign(temp.begin() + 1, temp.begin() + strSize);
						info.push(str);
						// tag.push(tatoi(str.c_str()));
						curPivot += (strSize + 1);
					}
				}
				else if ((strSize = temp.find(PARSING_END)) < string::npos)
				{
					string::size_type s2 = temp.find(FOOTNOTE_LINE);
					strSize = min(strSize, s2);

					// int, float을 정확히 구분할 수 없음
					tstring str;
					str.assign(temp.begin() + 1, temp.begin() + strSize);

					if (temp.find(COMMA) < string::npos)
					{
						//float
						wchar_t* buffer = nullptr;
						float f = tstrtof(str.c_str(),  &buffer);
						if (buffer)
							info.push(f);
					}
					else
					{
						// int
						info.push(tatoi(str.c_str()));
					}
					curPivot += strSize;
				}

				else
				{
					curPivot++;
				}
			}
		}
		return info;
	}

	bool RScriptParsing::tryRead(const tstring fileName)
	{
		fileName_ = fileName;
		bool result = false;
		tstring fullPath = gLocal_path;
		fullPath += fileName_;

		vector<tstring> vecErrTag;
		ifs_.open(fullPath.c_str(), READ_IOS_MODE);
		if (ifs_.is_open())
		{
			result = true;
			bool isFootnote = false;
			while (!ifs_.eof())
			{
				parsing par;
				ifs_.getline(par.byte, PARSING_SIZE);
				// vParsingData_.push_back(par);

				tstring str = par.byte;
				tstring::size_type strSize;
				if (str.empty())
				{
					continue;
				}
				else if (str[0] == PARSING_END)
				{
					continue;
				}
				else if ((strSize = str.find(FOOTNOTE_LINE)) < string::npos)
				{
					if (strSize < 1)
						continue;
					tstring temp;
					temp.assign(str.begin() + (strSize + tstrlen(FOOTNOTE_LINE)), str.end());
				}
				else if (str.find(FOOTNOTE_START) < 1)
				{
					if ((strSize = str.find(FOOTNOTE_LAST)) < string::npos)
					{
						if (strSize < 1)
						{
							isFootnote = true;
							continue;
						}
						else
						{
							tstring temp;
							temp.assign(str.begin() + (strSize + tstrlen(FOOTNOTE_LAST)), str.end());
						}
					}
					else
					{
						isFootnote = true;
						continue;
					}
				}
				else if ((strSize = str.find(FOOTNOTE_LAST)) < string::npos)
				{
					isFootnote = false;

					if (strSize > 1)
					{
						tstring temp;
						temp.assign(str.begin() + (strSize + 2), str.end());
					}
					else
					{
						continue;
					}
				}
				else if (str.find(PARSING_END) < 1)
				{
					continue;
				}
				if (!isFootnote)
				{
					TagInfo info = tryMakeTagData(str);
					if (info.isVaild() == TAG_INFO_TPYE::NONE)
					{
						vTagData_.push_back(info);
					}
					else
					{
						if (info.isVaild() != TAG_INFO_TPYE::DATA_NOT)
						{
							tstring er = par.byte;
							vecErrTag.push_back(er);
							result = false;
							break;
						}
					}
				}
			}

			ifs_.close();
		}

		if (!result)
		{
			Radar::c_red();
			tcout << _XTT("read errror : ") << fullPath << endl;
			Radar::c_blue();
			for (auto err : vecErrTag)
				tcout << err << endl;
			Radar::c_default();
		}

		return result;
	}
}