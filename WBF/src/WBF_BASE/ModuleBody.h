#pragma once

#include "ModuleData.hpp"
#include "EntityBody.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleBody : public CModuleData<CEntityBody>
{
public:
	CModuleBody(CPackage * pPackage);
	virtual ~CModuleBody();

public:
	virtual void SetDefaultData();

};

#include "HeaderPost.h"
