#pragma once

#include <string>

class CWBFString
{
public:
	CWBFString();
	virtual ~CWBFString();

public:
	static void CSTR2STR(IN CString& cstr, OUT std::string& str);
	static void CSTR2WSTR(IN CString& cstr, OUT std::wstring wstr);
	static void STR2CSTR(IN std::string& str, OUT CString& cstr);
	static void STR2WSTR(IN std::string& str, OUT std::wstring wstr);
	static void WSTR2CSTR(IN std::wstring& wstr, OUT CString& cstr);
	static void WSTR2STR(IN std::wstring wstr, OUT std::string& str);
};

