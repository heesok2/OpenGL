#pragma once

#include "WBFDataDefine.h"
#include "HeaderPre.h"

class CWBFPackageData;
class __MY_EXT_CLASS__ CWBFModuleBase
{
public:
	CWBFModuleBase(CWBFPackageData* pPackage);
	virtual ~CWBFModuleBase();

public:
	virtual void Clear() = 0;

	virtual DKEY GetNewKey() = 0;
	virtual DTYPE GetDataType() = 0;

	virtual void SetDefaultData() = 0;

protected:
	CWBFPackageData* m_pPackage;

};

#include "HeaderPost.h"