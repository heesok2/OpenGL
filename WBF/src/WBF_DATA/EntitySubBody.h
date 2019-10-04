#pragma once

#include <vector>
#include "DataBaseDefine.h"
#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntitySubBody : public CEntityData
{
public:
	CEntitySubBody();
	virtual ~CEntitySubBody();

public:
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual const DTYPE GetType() const override { return E_TYPE_SUBBODY; }

public:
	void Init();

public:
	DKEY dbKey;

	UINT uiSubType;
	std::vector<DKEY> lstVertex;
};

#include "HeaderPost.h"