#pragma once

#include "WBFDataDefine.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFData
{
public:
	CWBFData();
	virtual ~CWBFData();

public:
	virtual const DKEY GetKey() const = 0;
	virtual const DTYPE GetType() const = 0;

};

#include "HeaderPost.h"