#pragma once

#include "..\WBF_LIB\ModuleData.hpp"

#include "EntityMesh.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleMesh : public CModuleData<CEntityMesh>
{
public:
	CModuleMesh(CPackage * pPackage);
	virtual ~CModuleMesh();
};

#include "HeaderPost.h"
