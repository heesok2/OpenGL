#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CFileCtrl
{
public:
	CFileCtrl();
	CFileCtrl(const CString& strFilePath);
	virtual ~CFileCtrl();

public:
	void SetFilePath(const CString& strFilePath);
	BOOL Exist();

public:
	static BOOL Exist(const CString& strFullPath);
	static CString Absolute2Relative(const CString& src, const CString& trg);

protected:
	CString m_strFullPath;

};

#include "HeaderPost.h"