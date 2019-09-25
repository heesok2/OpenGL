#pragma once

#include "..\WBF_BASE\WBFRndrBaseManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrManager : public CWBFRndrBaseManager
{
public:
	CWBFCRndrManager(CWBFViewBase* pView);
	virtual ~CWBFCRndrManager();

public:
	virtual void OnInitial();
	virtual void OnDestroy();
	virtual void GLDrawScene();

public:
	CWBFShaderManager* GetShaderManager() { return m_pShaderMgr; }

public:
	CWBFShaderManager* m_pShaderMgr;

};

#include "HeaderPost.h"