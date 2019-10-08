#pragma once

#include "..\WBF_LIB\EntityData.h"
#include "EntityDefine.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityBody : public CEntityData
{
public:
	CEntityBody();
	virtual ~CEntityBody();

public:
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual const DTYPE GetType() const override { return E_TYPE_BODY; }

public:
	void Init();

public:
	DKEY dbKey;
	std::vector<DITER> aItrSubBody;
};


#include "HeaderPost.h"
