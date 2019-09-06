#pragma once

#include "WBFGraphicDef.h"
#include "WBFRndrFactory.h"
#include "HeaderPre.h"

class CWBFShaderManager;
class __MY_EXT_CLASS__ CWBFRndrBase : public CObject
{
public:
	CWBFRndrBase();
	virtual ~CWBFRndrBase();

public:
	virtual void GLInit(CWBFShaderManager* pShaderMgr) = 0;
	virtual void GLDraw() = 0;
};

#include "HeaderPost.h"

#define DECLARE_RENDERER(class_name)\
DECLARE_DYNCREATE(class_name);

#define IMPLEMENT_RENDERER(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CWBFRndrBase);\
BOOL bRegRndr = CWBFRndrFactory::GetInstance().RegisterObject(RUNTIME_CLASS(class_name), type);
