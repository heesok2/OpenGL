#pragma once

#include "WBFGraphicDef.h"
#include "WBFModelFactory.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFModelBase : public CObject
{
public:
	CWBFModelBase();
	virtual ~CWBFModelBase();

public:
	virtual void InitialData() = 0;
	virtual void CreateData() = 0;
	virtual void DeleteData() = 0;
	virtual void ModifyData() = 0;
};

#include "HeaderPost.h"

#define DECLARE_MODEL(class_name)\
DECLARE_DYNCREATE(class_name);

#define IMPLEMENT_MODEL(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CWBFModelBase);\
BOOL bRegModel = CWBFModelFactory::GetInstance().RegisterObject(RUNTIME_CLASS(class_name), type);