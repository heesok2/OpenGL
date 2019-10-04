#pragma once

#include "HeaderPre.h"

class CWBFViewBase;
class CPackageData;
class __MY_EXT_CLASS__ CWBFDocBase : public CDocument
{
public:
	CWBFDocBase();
	virtual ~CWBFDocBase();

public:
	virtual CWBFViewBase* GetActiveView();
	virtual CPackageData* GetPackage() = 0;

};

#include "HeaderPost.h"
