#pragma once

#include "EntityDefine.h"
#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityVertex : public CEntityData
{
public:
	CEntityVertex();
	virtual ~CEntityVertex();

public:
	virtual const DTYPE GetType() const override { return E_TYPE_VERTEX; }
	virtual const DKEY GetKey() const override { return dbKey; }

public:
	void Init();

public:
	DKEY dbKey;

	glm::vec3 vPos;
	glm::vec3 vNormal;
	glm::vec2 vTexcord;
};

#include "HeaderPost.h"