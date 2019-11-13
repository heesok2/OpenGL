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
	str = CSTR2STR(cstr);
}

void CStringConverter::CSTR2WSTR(IN CString & cstr, OUT std::wstring wstr)
{
	wstr = CSTR2WSTR(cstr);
}

void CStringConverter::STR2CSTR(IN std::string & str, OUT CString & cstr)
{
	cstr = STR2CSTR(str);
}

void CStringConverter::STR2WSTR(IN std::string & str, OUT std::wstring wstr)
{
	wstr = STR2WSTR(str);
}

void CStringConverter::WSTR2CSTR(IN std::wstring & wstr, OUT CString & cstr)
{
	cstr = WSTR2CSTR(wstr);
}

void CStringConverter::WSTR2STR(IN std::wstring wstr, OUT std::string & str)
{
	str = WSTR2STR(wstr);
}

std::string CStringConverter::CSTR2STR(IN CString & cstr)
{
	return std::string(CT2CA(cstr.operator LPCWSTR()));
}

std::wstring CStringConverter::CSTR2WSTR(IN CString & cstr)
{
	return std::wstring(cstr.operator LPCWSTR());
}

CString CStringConverter::STR2CSTR(IN std::string & str)
{
	return CString::CStringT(CA2CT(str.c_str()));
}

std::wstring CStringConverter::STR2WSTR(IN std::string & str)
{
	return std::wstring(CA2CT(str.c_str()));
}

CString CStringConverter::WSTR2CSTR(IN std::wstring & wstr)
{
	return CString::CStringT(wstr.c_str());
}

std::string CStringConverter::WSTR2STR(IN std::wstring wstr)
{
	return std::string(CT2CA(wstr.c_str()));
}
