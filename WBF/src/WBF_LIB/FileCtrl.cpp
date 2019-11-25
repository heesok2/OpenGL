#include "stdafx.h"
#include "FileCtrl.h"

#define D_EMPTY _T("")
#define D_BACKSLASH _T("\\")
#define D_CURRENT _T(".\\")
#define D_PARENT _T("..\\")

CFileCtrl::CFileCtrl()
{
	m_strFullPath = _T("");
}

CFileCtrl::CFileCtrl(const CString & strFilePath)
{
	m_strFullPath = strFilePath;
}

CFileCtrl::~CFileCtrl()
{
}

void CFileCtrl::SetFilePath(const CString & strFullPath)
{
	if (strFullPath.IsEmpty())
	{
		ASSERT(g_warning);
		return;
	}

	m_strFullPath = strFullPath;
}

BOOL CFileCtrl::Exist()
{
	CFileStatus FileStatus;
	return CFile::GetStatus(m_strFullPath, FileStatus);
}

BOOL CFileCtrl::Exist(const CString& strFullPath)
{
	CFileStatus FileStatus;
	return CFile::GetStatus(strFullPath, FileStatus);
}

CString CFileCtrl::Absolute2Relative(const CString & src, const CString & trg)
{
	if (src.IsEmpty() || trg.IsEmpty())
	{
		ASSERT(g_warning);
		return D_CURRENT;
	}
	else if (src.CompareNoCase(trg) == 0)
		return D_CURRENT;

	std::vector<CString> aSrcSplit;
	std::vector<CString> aTrgSplit;

	auto lambda_split = [](const CString& strPath, std::vector<CString>& aSplit)
	{
		int nSub = 0;
		CString strSub = D_EMPTY;
		while (AfxExtractSubString(strSub, strPath, nSub++, '\\'))
		{
			if (!strSub.IsEmpty())
				aSplit.push_back(strSub);
		}
	};
	lambda_split(src, aSrcSplit);
	lambda_split(trg, aTrgSplit);

	CString strSame = D_EMPTY;

	CString strSrcUpper = src;
	strSrcUpper.MakeUpper();
	for (auto strSplit : aTrgSplit)
	{
		strSplit.MakeUpper();

		auto strDiff = strSame + strSplit;
		auto item = strSrcUpper.Find(strDiff);
		if (item != 0)
			break;

		strSame += strSplit + D_BACKSLASH;
	}

	if (strSame.IsEmpty()) // Different Directory 
	{
		ASSERT(g_warning);
		return src;
	}

	CString strRelative = D_EMPTY;

	CString strCompTrg = D_EMPTY;
	for (auto strSplit : aTrgSplit)
	{
		auto strUpper = strSplit;
		strUpper.MakeUpper();

		auto strDiff = strCompTrg + strUpper;
		auto item = strSame.Find(strDiff);
		if (item != 0)
			strRelative += D_PARENT;

		strCompTrg += strUpper + D_BACKSLASH;
	}
	CString strCompSrc = D_EMPTY;
	for (auto strSplit : aSrcSplit)
	{
		auto strUpper = strSplit;
		strUpper.MakeUpper();

		auto strDiff = strCompSrc + strUpper;
		auto item = strSame.Find(strDiff);
		if (item != 0)
			strRelative += strSplit + D_BACKSLASH;

		strCompSrc += strUpper + D_BACKSLASH;
	}

	return strRelative;
}