#pragma once

#include "HeaderPre.h"

class CWBFViewBase;
class CWBFModelBaseManager;
class CWBFPackageData;
class __MY_EXT_CLASS__ CWBFDocBase : public CDocument
{
public:
	CWBFDocBase();
	virtual ~CWBFDocBase();

public:
	virtual CWBFViewBase* GetActiveView();

	virtual CWBFPackageData* GetDataPackage() { ASSERT(g_warning); return nullptr; }
	virtual CWBFModelBaseManager* GetModelManager() { ASSERT(g_warning); return nullptr; }

};

#include "HeaderPost.h"
