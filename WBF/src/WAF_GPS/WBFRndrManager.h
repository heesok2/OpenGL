#pragma once

#include "..\WBF_BASE\RndrManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFRndrManager : public CRndrManager
{
public:
	CWBFRndrManager(CViewBase* pView);
	virtual ~CWBFRndrManager();

public:
	virtual void OnInitial();
	virtual void OnDestroy();
	virtual void GLDrawScene();

public:
	CShaderManager* GetShaderManager();
	
};

#include "HeaderPost.h"