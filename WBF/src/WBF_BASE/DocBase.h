#pragma once

#include "HeaderPre.h"

class CPackage;
class CViewBase;
class __MY_EXT_CLASS__ CDocBase : public CDocument
{
public:
	CDocBase();
	virtual ~CDocBase();

public:
	virtual CPackage* GetPackage() = 0;

public:
	virtual CViewBase* GetActiveView();

};

#include "HeaderPost.h"
