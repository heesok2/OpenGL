#pragma once

#include "WBFEntityData.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityVertex : public CWBFEntityData
{
public:
	CEntityVertex();
	virtual ~CEntityVertex();

public:
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual const DTYPE GetType() const override { return E_TYPE_VERTEX; }

public:
	DKEY dbKey;

	glm::vec3 vPos;
	glm::vec3 vNormal;
	glm::vec2 vTexcord;
};

#include "HeaderPost.h"