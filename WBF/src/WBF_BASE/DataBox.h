#pragma once

#include "WBFData.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CDataBox : public CWBFData
{
public:
	CDataBox();
	virtual ~CDataBox();

public:
	virtual const DKEY GetKey() const override { return dbKey; }
	virtual const DTYPE GetType() const override { return D_TYPE_BOX; }

public:
	DKEY dbKey;

};

#include "HeaderPost.h"

