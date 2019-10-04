#pragma once

#include "ModuleData.hpp"
#include "EntitySubBody.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleSubBody : public CModuleData<CEntitySubBody>
{
public:
	CModuleSubBody(CPackageData * pPackage);
	virtual ~CModuleSubBody();

public:
	virtual void SetDefaultData();
};

#include "HeaderPost.h"