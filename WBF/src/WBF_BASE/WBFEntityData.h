#pragma once

#include "WBFDataDefine.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFEntityData
{
public:
	CWBFEntityData();
	virtual ~CWBFEntityData();

public:
	virtual const DKEY GetKey() const = 0;
	virtual const DTYPE GetType() const { ASSERT(g_warning); return E_TYPE_UNKNOWN; }
	virtual const CString GetName() const { ASSERT(g_warning); return _T(""); }

};

#include "HeaderPost.h"