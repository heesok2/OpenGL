#pragma once

#include <vector>
#include "..\WBF_LIB\WBFObserver.h"

#include "HeaderPre.h"

class CWBFDocBase;
class CWBFVBOData;
class __MY_EXT_CLASS__ CWBFVBOManager : public CWBFObserver
{
public:
	CWBFVBOManager(CWBFDocBase* pDoc);
	virtual ~CWBFVBOManager();

public:
	// CWBFObserver을(를) 통해 상속됨
	virtual void UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void OnInitial();
	void OnDestroy();

protected:
	CWBFDocBase* m_pMyDoc;
	std::vector<CWBFVBOData*> m_lstVBO;
};

#include "HeaderPost.h"