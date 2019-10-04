#pragma once

#include "EntityData.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityGeom : public CEntityData
{
public:
	CEntityGeom();
	virtual ~CEntityGeom();

public:
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual const DTYPE GetType() const override { return E_TYPE_GEOM; }
	
public:
	DKEY dbKey;
};

#include "HeaderPost.h"
