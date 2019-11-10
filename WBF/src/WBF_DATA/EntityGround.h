#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityGround : public CEntityData
{
public:
	CEntityGround();
	virtual ~CEntityGround();

public:
	virtual const DTYPE GetType() const override;
	virtual const DKEY GetKey() const override;

public:
	DKEY dbKey;
	glm::vec3 aPos[4];
};

#include "HeaderPost.h"


