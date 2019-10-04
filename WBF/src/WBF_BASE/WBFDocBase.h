#pragma once

#include "HeaderPre.h"

class CPackage;
class CWBFViewBase;
class __MY_EXT_CLASS__ CWBFDocBase : public CDocument
{
public:
	CWBFDocBase();
	virtual ~CWBFDocBase();

public:
	virtual CPackage* GetPackage() = 0;

public:
	virtual CWBFViewBase* GetActiveView();

};

#include "HeaderPost.h"
