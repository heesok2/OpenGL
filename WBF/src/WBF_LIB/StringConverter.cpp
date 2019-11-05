#include "stdafx.h"
#include "StringConverter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStringConverter::CStringConverter()
{
}


CStringConverter::~CStringConverter()
{
}

void CStringConverter::CSTR2STR(IN CString & cstr, OUT std::string & str)
{
	str = std::string(CT2CA(cstr.operator LPCWSTR()));
}

void CStringConverter::CSTR2WSTR(IN CString & cstr, OUT std::wstring wstr)
{
	wstr = std::wstring(cstr.operator LPCWSTR());
}

void CStringConverter::STR2CSTR(IN std::string & str, OUT CString & cstr)
{
	cstr = CString::CStringT(CA2CT(str.c_str()));
}

void CStringConverter::STR2WSTR(IN std::string & str, OUT std::wstring wstr)
{
	wstr = std::wstring(CA2CT(str.c_str()));
}

void CStringConverter::WSTR2CSTR(IN std::wstring & wstr, OUT CString & cstr)
{
	cstr = CString::CStringT(wstr.c_str());
}

void CStringConverter::WSTR2STR(IN std::wstring wstr, OUT std::string & str)
{
	str = std::string(CT2CA(wstr.c_str()));
}