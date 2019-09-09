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
	virtual CWBFModelBase* GetModel(UINT uiType);

	virtual void OnInitialUpdate() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnUpdateAll() = 0;
	virtual void OnUpdateOnly(UINT uiType) = 0;

	virtual void GLInitialData() = 0;	
	
protected:
	CWBFDocBase* m_pDoc;
	std::vector<CWBFModelBase*> m_vObject;

};

#include "HeaderPost.h"