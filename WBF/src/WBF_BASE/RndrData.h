#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"

#include "RndrDefine.h"
#include "RndrFactory.h"
#include "HeaderPre.h"

class CRndrManager;
class CModelManager;
class __MY_EXT_CLASS__ CRndrData : public CFactoryObjectBase
{
public:
	CRndrData();
	virtual ~CRndrData();

public:
	virtual UINT GetType() override { ASSERT(g_warning); return 0; }
	virtual void OnInitialData() {}
	virtual void GLDraw() = 0;

public:
	void SetHelper(CRndrManager* pRndrMgr, CModelManager* pModelMgr)
	{
		m_pRndrMgr = pRndrMgr;
		m_pModelMgr = pModelMgr;
	}

protected:
	CRndrManager* m_pRndrMgr;
	CModelManager* m_pModelMgr;

};

#include "HeaderPost.h"

#define DECLARE_RENDERER(class_name)\
DECLARE_DYNCREATE(class_name);

#define IMPLEMENT_RENDERER(type, class_name)\
IMPLEMENT_DYNCREATE(class_name, CRndrData);\
BOOL b##class_name = CRndrFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));