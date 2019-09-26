#pragma once

#include "WBFGraphicDef.h"
#include "WBFRndrFactory.h"
#include "HeaderPre.h"

class CWBFRndrDataManager;
class CWBFModelDataManager;
class __MY_EXT_CLASS__ CWBFRndrData : public CObject
{
public:
	CWBFRndrData();
	virtual ~CWBFRndrData();

public:
	virtual UINT GetType() { ASSERT(g_warning); return gps::E_GPS_UNKNOWN; }
	virtual void OnInitialData() {}
	virtual void GLDraw() = 0;

public:
	void SetHelper(CWBFRndrDataManager* pRndrMgr, CWBFModelDataManager* pModelMgr)
	{
		m_pRndrMgr = pRndrMgr;
		m_pModelMgr = pModelMgr;
	}

protected:
	CWBFRndrDataManager* m_pRndrMgr;
	CWBFModelDataManager* m_pModelMgr;

};

#include "HeaderPost.h"

#define DECLARE_RENDERER(class_name)\
DECLARE_DYNCREATE(class_name);\
virtual UINT GetType();

#define IMPLEMENT_RENDERER(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CWBFRndrData);\
BOOL bReg##class_name = CWBFRndrFactory::GetInstance().RegisterObject(RUNTIME_CLASS(class_name), type);\
UINT class_name::GetType() { return type; }
