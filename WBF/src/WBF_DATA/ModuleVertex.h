#pragma once

#include "..\WBF_LIB\ModuleData.hpp"

#include "EntityVertex.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleVertex : public CModuleData<CEntityVertex>
{
public:
	CModuleVertex(CPackage * pPackage);
	virtual ~CModuleVertex();

public:
	virtual void SetDefaultData();
};

#include "HeaderPost.h"
