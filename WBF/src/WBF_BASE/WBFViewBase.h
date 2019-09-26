#pragma once

#include "HeaderPre.h"

class CWBFModelDataManager;
class CWBFRndrDataManager;
class __MY_EXT_CLASS__ CWBFViewBase : public CView
{
public:
	CWBFViewBase();
	virtual ~CWBFViewBase();

public:
	virtual CWBFRndrDataManager* GetRenderManager() { ASSERT(g_warning); return nullptr; }
	virtual BOOL GetViewMatrix(glm::mat4& matView) { ASSERT(g_warning); return FALSE; }

public:
	virtual CWBFModelDataManager* GetModelManager() { ASSERT(m_pModelMgr); return m_pModelMgr; }
	virtual CWBFRndrDataManager* GetRndrManager() { ASSERT(m_pRndrMgr); return m_pRndrMgr; }

protected:
	CWBFModelDataManager* m_pModelMgr;
	CWBFRndrDataManager* m_pRndrMgr;

};

#include "HeaderPost.h"