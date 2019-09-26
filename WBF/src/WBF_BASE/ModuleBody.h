#pragma once

#include "WBFModuleData.hpp"
#include "EntityBody.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleBody : public CWBFModuleData<CEntityBody>
{
public:
	CModuleBody();
	virtual ~CModuleBody();

public:
	virtual void SetDefaultData();

};

#include "HeaderPost.h"
