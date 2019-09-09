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
	virtual UINT GetType() { ASSERT(g_warning); return gps::E_GPS_UNKNOWN; }
	virtual void InitFlag() { m_uiFlag = MODEL_UNKNOWN; }
	virtual void SetFlag(UINT uiFlag) { m_uiFlag |= uiFlag; }	
	virtual UINT GetFlag() { return m_uiFlag; }	

	virtual void GLInitialData() = 0;
	virtual void GLCreateVBO() = 0;

protected:
	UINT m_uiFlag;
};

#include "HeaderPost.h"

#define DECLARE_MODEL(class_name)\
DECLARE_DYNCREATE(class_name);\
virtual UINT GetType();

#define IMPLEMENT_MODEL(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CWBFModelBase);\
BOOL bRegModel = CWBFModelFactory::GetInstance().RegisterObject(RUNTIME_CLASS(class_name), type);\
UINT class_name::GetType() { return type; }