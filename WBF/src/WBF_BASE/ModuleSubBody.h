#pragma once

#include "WBFModuleData.hpp"
#include "EntitySubBody.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleSubBody : public CWBFModuleData<CEntitySubBody>
{
public:
	CModuleSubBody(CWBFPackageData * pPackage);
	virtual ~CModuleSubBody();

public:
	virtual void SetDefaultData();
};

#include "HeaderPost.h"