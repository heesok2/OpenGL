#pragma once

#include "..\WBF_LIB\ModuleData.hpp"
#include "EntityLight.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleLight : public CModuleData<CEntityLight>
{
public:
	CModuleLight(CPackage * pPackage);
	virtual ~CModuleLight();

public:
	virtual void SetDefaultData();
};

#include "HeaderPost.h"