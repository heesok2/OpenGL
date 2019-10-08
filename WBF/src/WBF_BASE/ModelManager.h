#pragma once

#include "HeaderPre.h"

class CDocBase;
class CViewBase;
class CModelData;
class CVBOManager;
class __MY_EXT_CLASS__ CModelManager
{
public:
	CModelManager(CViewBase* pView);
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
	CDocBase* GetDoc() { return m_pMyDoc; }
	CViewBase* GetView() { return m_pView; }
	CModelData* GetModel(UINT uiType);

protected:
	CDocBase* m_pMyDoc;
	CViewBase* m_pView;
	std::vector<CModelData*> m_vObject;

};

#include "HeaderPost.h"