#pragma once

#include "ModuleData.hpp"
#include "EntityBox.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleBox : public CModuleData<CEntityBox>
{
public:
	CModuleBox(CPackageData * pPackage);
	virtual ~CModuleBox();


};

#include "HeaderPost.h"

