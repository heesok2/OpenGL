#pragma once

#include "WBFModuleData.hpp"
#include "EntityVertex.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleVertex : public CWBFModuleData<CEntityVertex>
{
public:
	CModuleVertex();
	virtual ~CModuleVertex();

public:
	virtual void SetDefaultData();
};

#include "HeaderPost.h"
