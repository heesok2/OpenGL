#pragma once

#include <vector>

#include "HeaderPre.h"

class CWBFDocBase;
class CWBFModelData;
class CWBFVBOManager;
class __MY_EXT_CLASS__ CWBFModelDataManager
{
public:
	CWBFModelDataManager(CWBFDocBase* pDoc);
	virtual ~CWBFModelDataManager();
	
public:
	virtual void OnInitial();
	virtual void OnDestroy();

	virtual void OnUpdateAll() = 0;
	virtual void OnUpdateOnly(UINT uiType) = 0;

	virtual void GLInitialData() = 0;	
	
public:
	CWBFDocBase* GetDoc() { return m_pMyDoc; }
	CWBFModelData* GetModel(UINT uiType);

protected:
	CWBFDocBase* m_pMyDoc;
	CWBFVBOManager* m_pVBOMgr;

	std::vector<CWBFModelData*> m_vObject;

};

#include "HeaderPost.h"