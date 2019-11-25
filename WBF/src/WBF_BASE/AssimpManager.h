#pragma once

#include "IFileManager.h"

class CAssimpManager : public IFileManager
{
public:
	CAssimpManager();
	virtual ~CAssimpManager();

public:
	virtual BOOL ImportFile(const CString & strFullPath) override;

};