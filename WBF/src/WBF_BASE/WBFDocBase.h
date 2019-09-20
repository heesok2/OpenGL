#pragma once

#include "HeaderPre.h"

class CWBFViewBase;
class CWBFModelBaseManager;
class __MY_EXT_CLASS__ CWBFDocBase : public CDocument
{
public:
	CWBFDocBase();
	virtual ~CWBFDocBase();

public:
	virtual CWBFModelBaseManager* GetModelManager() { ASSERT(g_warning); return nullptr; }
	virtual CWBFViewBase* GetActiveView();

};

#include "HeaderPost.h"
