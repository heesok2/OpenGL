#pragma once

#include "..\WBF_LIB\EntityData.h"
#include "DataBaseDefine.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityBox : public CEntityData
{
public:
	CEntityBox();
	virtual ~CEntityBox();

public:
	virtual const DTYPE GetType() const override { return E_TYPE_BOX; }
	virtual const DKEY GetKey() const override { return dbKey; }

public:
	DKEY dbKey;

	DKEY dbBodyKey;
	glm::vec3 vPos;

};

#include "HeaderPost.h"

