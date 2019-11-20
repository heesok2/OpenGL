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
	static void CSTR2STR(IN const CString& cstr, OUT std::string& str);
	static void CSTR2WSTR(IN const CString& cstr, OUT std::wstring wstr);
	static void STR2CSTR(IN const std::string& str, OUT CString& cstr);
	static void STR2WSTR(IN const std::string& str, OUT std::wstring wstr);
	static void WSTR2CSTR(IN const std::wstring& wstr, OUT CString& cstr);
	static void WSTR2STR(IN const std::wstring wstr, OUT std::string& str);
	
	static std::string CSTR2STR(IN const CString& cstr);
	static std::wstring CSTR2WSTR(IN const CString& cstr);
	static CString STR2CSTR(IN const std::string& str);
	static std::wstring STR2WSTR(IN const std::string& str);
	static CString WSTR2CSTR(IN const std::wstring& wstr);
	static std::string WSTR2STR(IN const std::wstring wstr);
};

#include "HeaderPost.h"

#endif // !DEF_STR_CONVERTER