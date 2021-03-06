#pragma once

#include "..\WBF_LIB\EntityData.h"
#include "EntityBody.h"

#include "HeaderPre.h"

enum E_ENT_LIGHT_TYPE
{
	E_ENT_UNKNOWN = 0,
	E_ENT_DIRECTIONAL,
	E_ENT_POINT,
	E_ENT_SUPPORT,

	E_ENT_NUM
};

class __MY_EXT_CLASS__ CEntityLight : public CEntityData
{
public:
	CEntityLight();
	virtual ~CEntityLight();

public:
	virtual const DTYPE GetType() const override { return E_TYPE_LIGHT; }
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual void SetDefaultData() override;

public:
	DKEY dbKey;
	UINT uiType;
	DITER itrBody;
	glm::vec3 vPos;

};

#include "HeaderPost.h"