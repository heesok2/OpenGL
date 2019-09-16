#include "stdafx.h"
#include "WBFString.h"


CWBFString::CWBFString()
{
}


CWBFString::~CWBFString()
{
}

void CWBFString::CSTR2STR(IN CString & cstr, OUT std::string & str)
{
	str = std::string(CT2CA(cstr.operator LPCWSTR()));
}

void CWBFString::CSTR2WSTR(IN CString & cstr, OUT std::wstring wstr)
{
	wstr = std::wstring(cstr.operator LPCWSTR());
}

void CWBFString::STR2CSTR(IN std::string & str, OUT CString & cstr)
{
	cstr = CString::CStringT(CA2CT(str.c_str()));
}

void CWBFString::STR2WSTR(IN std::string & str, OUT std::wstring wstr)
{
	wstr = std::wstring(CA2CT(str.c_str()));
}

void CWBFString::WSTR2CSTR(IN std::wstring & wstr, OUT CString & cstr)
{
	cstr = CString::CStringT(wstr.c_str());
}

void CWBFString::WSTR2STR(IN std::wstring wstr, OUT std::string & str)
{
	str = std::string(CT2CA(wstr.c_str()));
}