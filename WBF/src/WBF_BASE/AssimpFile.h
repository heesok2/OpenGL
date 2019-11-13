#pragma once

#include "..\WBF_LIB\AssimpLoader.h"

#include "HeaderPre.h"

class __MY_EXT_API__ CAssimpFile
{
public:
	CAssimpFile();
	virtual ~CAssimpFile();

public:
	void Scan(CString strFilePath);

protected:
	CAssimpLoader m_tLoader;

};

#include "HeaderPost.h"