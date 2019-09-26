#pragma once

#include "..\WBF_LIB\WBFObserver.h"
#include "..\WBF_BASE\WBFModelDataManager.h"

#include "HeaderPre.h"

class CWBFVBOManager;
class __MY_EXT_CLASS__ CModelAppManager : public CWBFModelDataManager, public CWBFObserver
{
public:
	CModelAppManager(CWBFDocBase* pDoc);
	virtual ~CModelAppManager();

public:
	// CWBFObserver을(를) 통해 상속됨
	virtual void UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam) override;

public:
	virtual void OnInitial();
	virtual void OnDestroy();
	virtual void OnUpdateAll();
	virtual void OnUpdateOnly(UINT uiType);

	virtual void GLInitialData();


};

#include "HeaderPost.h"
