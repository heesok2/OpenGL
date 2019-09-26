#pragma once

#include "..\WBF_BASE\WBFRndrDataManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRndrAppManager : public CWBFRndrDataManager
{
public:
	CRndrAppManager(CWBFViewBase* pView);
	virtual ~CRndrAppManager();

public:
	virtual void OnInitial();
	virtual void OnDestroy();
	virtual void GLDrawScene();

public:
	CWBFShaderManager* GetShaderManager() { return m_pShaderManager; }

protected:
	CWBFShaderManager* m_pShaderManager;

};

#include "HeaderPost.h"