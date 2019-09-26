#pragma once

#include "HeaderPre.h"

class CWBFViewBase;
class CWBFPackageData;
class __MY_EXT_CLASS__ CWBFDocBase : public CDocument
{
public:
	CWBFDocBase();
	virtual ~CWBFDocBase();

public:
	virtual CWBFViewBase* GetActiveView();
	virtual CWBFPackageData* GetPackage() { return m_pPackage; }

public:
	CWBFPackageData* m_pPackage;

};

#include "HeaderPost.h"
