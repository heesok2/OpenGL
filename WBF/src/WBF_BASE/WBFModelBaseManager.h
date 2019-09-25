#pragma once

#include <vector>

#include "..\WBF_LIB\WBFObserver.h"

#include "HeaderPre.h"

class CWBFDocBase;
class CWBFModelBase;
class __MY_EXT_CLASS__ CWBFModelBaseManager : public CWBFObserver
{
public:
	CWBFModelBaseManager(CWBFDocBase* pDoc);
	virtual ~CWBFModelBaseManager();

public:
	// CWBFObserver을(를) 통해 상속됨
	virtual void UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam) override;

public:
	virtual void OnInitial();
	virtual void OnDestroy();

	virtual void OnUpdateAll() = 0;
	virtual void OnUpdateOnly(UINT uiType) = 0;

	virtual void GLInitialData() = 0;	
	
public:
	CWBFModelBase* GetModel(UINT uiType);
	CWBFDocBase* GetDoc() { return m_pMyDoc; }

protected:
	CWBFDocBase* m_pMyDoc;
	std::vector<CWBFModelBase*> m_vObject;

};

#include "HeaderPost.h"