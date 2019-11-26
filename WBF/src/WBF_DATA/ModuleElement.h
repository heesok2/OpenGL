#pragma once

#include "..\WBF_LIB\ModuleData.hpp"

#include "EntityElement.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleElement : public CModuleData<CEntityElement>
{
public:
	CModuleElement(CPackage * pPackage);
	virtual ~CModuleElement();
};

#include "HeaderPost.h"