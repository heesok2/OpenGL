#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CFileCtrl
{
public:
	CFileCtrl();
	virtual ~CFileCtrl();

public:
	static BOOL Exist(const CString csFilePath);
	static CString Absolute2Relative(const CString& src, const CString& trg);

};

#include "HeaderPost.h"