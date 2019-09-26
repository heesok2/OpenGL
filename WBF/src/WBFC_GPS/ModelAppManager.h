#pragma once

#include "..\WBF_LIB\WBFObserver.h"
#include "..\WBF_BASE\WBFModelDataManager.h"

#include "HeaderPre.h"

class CWBFVBOManager;
class __MY_EXT_CLASS__ CModelAppManager : public CWBFModelDataManager, public CWBFObserver
{
public:
	CModelAppManager(CWBFViewBase* pView);
	virtual ~CModelAppManager();

public:
	virtual void UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam) override;
	virtual CWBFVBOManager* GetVBOManager() { return m_pVBOMgr; }

public:
	virtual void OnInitial();
	virtual void OnDestroy();
	virtual void OnUpdateAll();
	virtual void OnUpdateOnly(UINT uiType);

	virtual void GLInitialData();

protected:
	CWBFVBOManager* m_pVBOMgr;

};

#include "HeaderPost.h"
