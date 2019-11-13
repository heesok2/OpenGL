#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityElement : public CEntityData
{
public:
	CEntityElement();
	virtual ~CEntityElement();

public:
	virtual const DTYPE GetType() const override;
	virtual const DKEY GetKey() const override;

public:
	DKEY dbKey;

	UINT uiType;
	std::vector<DITER> aItrNode;

};

#include "HeaderPost.h"