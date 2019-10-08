#pragma once

#include "HeaderPre.h"

class CWBFDocBase;
class CWBFViewBase;
class CModelData;
class CVBOManager;
class __MY_EXT_CLASS__ CModelManager
{
public:
	CModelManager(CWBFViewBase* pView);
	virtual ~CModelManager();

public:
	virtual CVBOManager* GetVBOManager() = 0;

public:
	virtual void OnInitial();
	virtual void OnDestroy();
	virtual void OnUpdateAll() = 0;
	virtual void OnUpdateOnly(UINT uiType) = 0;

	virtual void GLInitialData() = 0;

public:
	CWBFDocBase* GetDoc() { return m_pMyDoc; }
	CWBFViewBase* GetView() { return m_pView; }
	CModelData* GetModel(UINT uiType);

protected:
	CWBFDocBase* m_pMyDoc;
	CWBFViewBase* m_pView;
	std::vector<CModelData*> m_vObject;

};

#include "HeaderPost.h"