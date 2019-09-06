#pragma once

#include "..\WBF_BASE\WBFModelBaseManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCModelManager : public CWBFModelBaseManager
{
public:
	CWBFCModelManager(CWBFDocBase* pDoc);
	virtual ~CWBFCModelManager();

public:
	virtual void OnInitialUpdate();
	virtual void OnDestroy();
	virtual void OnUpdateAll();
	virtual void OnUpdateOnly(UINT uiType);
	virtual void OnDeleteAll();
	virtual void OnDeleteOnly(UINT uiType);

};

#include "HeaderPost.h"
