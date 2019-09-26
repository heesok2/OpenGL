#pragma once

#include <vector>
#include "WBFEntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityBody : public CWBFEntityData
{
public:
	CEntityBody();
	virtual ~CEntityBody();

public:
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual const DTYPE GetType() const override { return E_TYPE_BODY; }

public:
	DKEY dbKey;
	std::vector<DKEY> lstSubBody;
};


#include "HeaderPost.h"
