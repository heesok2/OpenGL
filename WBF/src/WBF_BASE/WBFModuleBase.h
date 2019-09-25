#pragma once

#include "WBFDataDefine.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFModuleBase
{
public:
	CWBFModuleBase();
	virtual ~CWBFModuleBase();

public:
	virtual void Clear() = 0;

	virtual DKEY GetNewKey() = 0;
	virtual DTYPE GetDataType() = 0;
};

#include "HeaderPost.h"