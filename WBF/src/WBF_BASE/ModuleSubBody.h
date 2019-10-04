#pragma once

#include "..\WBF_LIB\ModuleData.hpp"
#include "EntitySubBody.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleSubBody : public CModuleData<CEntitySubBody>
{
public:
	CModuleSubBody(CPackage * pPackage);
	virtual ~CModuleSubBody();

public:
	virtual void SetDefaultData();
};

#include "HeaderPost.h"