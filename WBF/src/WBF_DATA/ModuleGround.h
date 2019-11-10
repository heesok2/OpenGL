#pragma once

#include "..\WBF_LIB\ModuleData.hpp"
#include "EntityGround.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleGround : public CModuleData<CEntityGround>
{
public:
	CModuleGround(CPackage * pPackage);
	virtual ~CModuleGround();

public:
	virtual DITER GetDefaultData() override;
	virtual void SetDefaultData() override;

protected:
	DKEY m_dbDefaultKey;
};

#include "HeaderPost.h"

