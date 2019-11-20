#include "stdafx.h"
#include "FileCtrl.h"


CFileCtrl::CFileCtrl()
{
}


CFileCtrl::~CFileCtrl()
{
}

BOOL CFileCtrl::Exist(const CString csFilePath)
{
	CFileStatus FileStatus;
	return CFile::GetStatus(csFilePath, FileStatus);
}

CString CFileCtrl::AbsolutePath2RelativePath(const CString & src, const CString & trg)
{
	if (src.CompareNoCase(trg) == 0)
		return _T(".\\");

	CString strSrcUpper = src;
	CString strTrgUpper = trg;

	strSrcUpper.MakeUpper();
	strTrgUpper.MakeUpper();

	std::vector<CString> aTrgSplit;
	{
		int nSub = 0;
		CString strSub(_T(""));
		while (AfxExtractSubString(strSub, strTrgUpper, nSub++, '\\'))
			aTrgSplit.push_back(strSub);
	}

	CString strSame(_T(""));
	for (auto strSplit : aTrgSplit)
	{
		auto strDiff = strSame + strSplit;
		auto item = strSrcUpper.Find(strDiff);

		if (item != 0)
			break;

		strSame += strSplit;
	}

	CString strRelative(_T(""));
	{
		auto revItem = trg.ReverseFind('\\');
		auto strTrgPath = trg.Left(revItem);
		auto strTrgName = trg.Right(trg.GetLength() - revItem);

		int nSub = 0;
		CString strSub(_T(""));
		CString strCompare(_T(""));
		while (AfxExtractSubString(strSub, strTrgPath, nSub++, '\\'))
		{
			auto strDiff = strCompare + strSub;
			auto item = strSame.CompareNoCase(strDiff);

			if (item != 0)
				strRelative += _T("..\\");

			strCompare += strSub;
		}
	}

	{
		auto strSrcPath = src;

		int nSub = 0;
		CString strSub(_T(""));
		CString strCompare(_T(""));
		while (AfxExtractSubString(strSub, strSrcPath, nSub++, '\\'))
		{
			auto strDiff = strCompare + strSub;
			auto item = strSame.CompareNoCase(strDiff);

			if (item != 0)
				strRelative += strSub + _T("\\");

			strCompare += strSub;
		}
	}

	return strRelative;
}