#pragma once

#include "..\WBF_GPS\WBFRndrFactory.h"
#include "HeaderPre.h"

enum E_RNDR_TYPE
{
	E_RNDR_UNKNOWN = 0,
	E_RNDR_SAMPLE,
	E_RNDR_NUM
};

class CWBFShaderManager;
class __MY_EXT_CLASS__ IWBFRndrBase : public CObject
{
public:
	IWBFRndrBase();
	virtual ~IWBFRndrBase();

public:
	virtual void GLInit(CWBFShaderManager* pShaderMgr) = 0;
	virtual void GLDraw() = 0;
};

#include "HeaderPost.h"

#define DECLARE_RENDERER(class_name)\
DECLARE_DYNCREATE(class_name);

#define IMPLEMENT_RENDERER(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, IWBFRndrBase);\
BOOL bRegister = CWBFRndrFactory::GetInstance().RegisterObject(RUNTIME_CLASS(class_name), type);
