#pragma once

#ifndef DEF_STR_CONVERTER
#define DEF_STR_CONVERTER

#include <string>

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CStringConverter
{
public:
	CStringConverter();
	virtual ~CStringConverter();

public:
	static void CSTR2STR(IN CString& cstr, OUT std::string& str);
	static void CSTR2WSTR(IN CString& cstr, OUT std::wstring wstr);
	static void STR2CSTR(IN std::string& str, OUT CString& cstr);
	static void STR2WSTR(IN std::string& str, OUT std::wstring wstr);
	static void WSTR2CSTR(IN std::wstring& wstr, OUT CString& cstr);
	static void WSTR2STR(IN std::wstring wstr, OUT std::string& str);
};

#include "HeaderPost.h"

#endif // !DEF_STR_CONVERTER