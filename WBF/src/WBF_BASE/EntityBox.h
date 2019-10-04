#pragma once

#include "EntityData.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityBox : public CEntityData
{
public:
	CEntityBox();
	virtual ~CEntityBox();

public:
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual const DTYPE GetType() const override { return E_TYPE_BOX; }

public:
	DKEY dbKey;

};

#include "HeaderPost.h"

