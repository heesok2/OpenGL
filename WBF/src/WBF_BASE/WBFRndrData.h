#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"

#include "WBFRndrDefine.h"
#include "WBFRndrFactory.h"
#include "HeaderPre.h"

class CWBFRndrDataManager;
class CWBFModelDataManager;
class __MY_EXT_CLASS__ CWBFRndrData : public CFactoryObjectBase
{
public:
	CWBFRndrData();
	virtual ~CWBFRndrData();

public:
	virtual UINT GetType() override { ASSERT(g_warning); return 0; }
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

#define IMPLEMENT_RENDERER(type, class_name)\
IMPLEMENT_DYNCREATE(class_name, CWBFRndrData);\
BOOL b##class_name = CWBFRndrFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));