#pragma once

#include <vector>
#include "HeaderPre.h"

class CWBFDocBase;
class CWBFModelBase;
class __MY_EXT_CLASS__ CWBFModelBaseManager
{
public:
	CWBFModelBaseManager(CWBFDocBase* pDoc);
	virtual ~CWBFModelBaseManager();

public:
	virtual void OnInitialUpdate() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnUpdateAll() = 0;
	virtual void OnUpdateOnly(UINT uiType) = 0;

	virtual void GLInitialData() = 0;	
	
public:
	CWBFModelBase* GetModel(UINT uiType);
	CWBFDocBase* GetDoc() { return m_pDoc; }

protected:
	CWBFDocBase* m_pDoc;
	std::vector<CWBFModelBase*> m_vObject;
};

#include "HeaderPost.h"