#pragma once

#include "WBFModuleData.hpp"
#include "EntityBox.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleBox : public CWBFModuleData<CEntityBox>
{
public:
	CModuleBox(CWBFPackageData * pPackage);
	virtual ~CModuleBox();


};

#include "HeaderPost.h"

