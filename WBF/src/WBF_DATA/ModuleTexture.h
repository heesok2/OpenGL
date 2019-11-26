#pragma once

#include "..\WBF_LIB\ModuleData.hpp"

#include "EntityTexture.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleTexture : public CModuleData<CEntityTexture>
{
public:
	CModuleTexture(CPackage * pPackage);
	virtual ~CModuleTexture();
};

#include "HeaderPost.h"