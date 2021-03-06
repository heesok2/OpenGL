#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityVertex : public CEntityData
{
public:
	CEntityVertex();
	virtual ~CEntityVertex();

public:
	virtual const DTYPE GetType() const override;
	virtual const DKEY GetKey() const override;

public:
	DKEY dbKey;

	glm::vec3 vPos;
	glm::vec3 vNormal;
	glm::vec2 vTexcord;
};

#include "HeaderPost.h"