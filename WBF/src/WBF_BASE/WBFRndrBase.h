#pragma once

#include "WBFGraphicDef.h"
#include "WBFRndrFactory.h"
#include "HeaderPre.h"

class CWBFRndrBaseManager;
class CWBFModelBaseManager;
class __MY_EXT_CLASS__ CWBFRndrBase : public CObject
{
public:
	CWBFRndrBase();
	virtual ~CWBFRndrBase();

public:
	virtual UINT GetType() { ASSERT(g_warning); return gps::E_GPS_UNKNOWN; }
	virtual void OnInitialData() {}
	virtual void GLDraw() = 0;

public:
	void SetHelper(CWBFRndrBaseManager* pRndrMgr, CWBFModelBaseManager* pModelMgr)
	{
		m_pRndrMgr = pRndrMgr;
		m_pModelMgr = pModelMgr;
	}

protected:
	CWBFRndrBaseManager* m_pRndrMgr;
	CWBFModelBaseManager* m_pModelMgr;

};

#include "HeaderPost.h"

#define DECLARE_RENDERER(class_name)\
DECLARE_DYNCREATE(class_name);\
virtual UINT GetType();

#define IMPLEMENT_RENDERER(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CWBFRndrBase);\
BOOL bRegRndr = CWBFRndrFactory::GetInstance().RegisterObject(RUNTIME_CLASS(class_name), type);\
UINT class_name::GetType() { return type; }
