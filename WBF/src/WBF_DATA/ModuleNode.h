#pragma once

#include "..\WBF_LIB\ModuleData.hpp"

#include "EntityNode.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleNode : public CModuleData<CEntityNode>
{
public:
	CModuleNode(CPackage * pPackage);
	virtual ~CModuleNode();
};

#include "HeaderPost.h"