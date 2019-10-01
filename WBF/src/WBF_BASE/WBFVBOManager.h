#pragma once

#include <vector>
#include "..\WBF_LIB\WBFObserver.h"

#include "HeaderPre.h"

class CWBFDocBase;
class CWBFVBOData;
class __MY_EXT_CLASS__ CWBFVBOManager
{
public:
	CWBFVBOManager(CWBFDocBase* pDoc);
	virtual ~CWBFVBOManager();

public:
	void UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam);
	CWBFVBOData* GetVBO(UINT uiType);

public:
	void OnInitial();
	void OnDestroy();

protected:
	CWBFDocBase* m_pMyDoc;
	std::vector<CWBFVBOData*> m_lstVBO;
};

#include "HeaderPost.h"