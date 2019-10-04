#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityData
{
public:
	CEntityData();
	virtual ~CEntityData();

public:
	virtual const DKEY GetKey() const = 0;
	virtual const DTYPE GetType() const { ASSERT(g_warning); return 0; }
	virtual const CString GetName() const { ASSERT(g_warning); return _T(""); }

};

#include "HeaderPost.h"