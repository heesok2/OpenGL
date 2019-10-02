#pragma once

#include "..\WBF_LIB\WBFObserver.h"
#include "..\WBF_BASE\WBFModelDataManager.h"
#include "..\WBF_BASE\DocListener.h"

#include "HeaderPre.h"

class CVBOManager;
class __MY_EXT_CLASS__ CWBFModelManager : public CModelManager, public CDocListener
{
public:
	CWBFModelManager(CWBFViewBase* pView);
	virtual ~CWBFModelManager();

public:
	virtual void OnNotifyMsg(CWBFDocBase* pDoc, WPARAM wParam, LPARAM lParam) override;

protected:
	void ReleaseModel();
	void BuildModel();


public:
	virtual CVBOManager* GetVBOManager() { return m_pVBOMgr; }

public:
	virtual void OnInitial();
	virtual void OnDestroy();
	virtual void OnUpdateAll();
	virtual void OnUpdateOnly(UINT uiType);

	virtual void GLInitialData();

protected:
	CVBOManager* m_pVBOMgr;

};

#include "HeaderPost.h"
