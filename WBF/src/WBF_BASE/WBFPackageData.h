#pragma once

#include <map>
#include "WBFDataDefine.h"

#include "HeaderPre.h"

class CWBFModuleBase;
class __MY_EXT_CLASS__ CWBFPackageData
{
public:
	CWBFPackageData();
	virtual ~CWBFPackageData();

public:
	virtual void OnInitial() = 0;
	virtual void OnDestroy() = 0;

	virtual CWBFModuleBase* GetModule(DTYPE dbType) = 0;

protected:
	std::map<DTYPE, CWBFModuleBase*> m_mModule;

};

#include "HeaderPost.h"
