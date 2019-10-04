#pragma once

#include "ModuleData.hpp"
#include "EntityGeom.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleGeom : public CModuleData<CEntityGeom>
{
public:
	CModuleGeom(CPackageData * pPackage);
	virtual ~CModuleGeom();

public:
	virtual void SetDefaultData();

};

#include "HeaderPost.h"