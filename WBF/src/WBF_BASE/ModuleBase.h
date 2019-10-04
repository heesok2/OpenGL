#pragma once

#include "HeaderPre.h"

class CPackageData;
class __MY_EXT_CLASS__ CModuleBase
{
public:
	CModuleBase(CPackageData* pPackage);
	virtual ~CModuleBase();

public:
	virtual void Clear() = 0;

	virtual DKEY GetNewKey() = 0;
	virtual DTYPE GetDataType() = 0;

	virtual void SetDefaultData() = 0;

protected:
	CPackageData* m_pPackage;

};

#include "HeaderPost.h"