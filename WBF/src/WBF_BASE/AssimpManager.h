#pragma once

#include "IFileManager.h"
#include "IFileLoader.h"

class CAssimpManager : public IFileManager
{
public:
	CAssimpManager();
	virtual ~CAssimpManager();

public:
	virtual BOOL ImportFile(const CString & strFullPath) override;

protected:
	std::vector<IFileLoader*> m_aFileLoader;

};