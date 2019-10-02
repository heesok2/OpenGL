#pragma once

#include <vector>

#include "HeaderPre.h"

class CWBFDocBase;
class CVBOData;
class __MY_EXT_CLASS__ CVBOManager
{
public:
	CVBOManager(CWBFDocBase* pDoc);
	virtual ~CVBOManager();

public:
	virtual BOOL Exist(UINT eType);
	virtual CVBOData* Lookup(UINT eType);
	virtual void RebuildVBO();

public:
	void OnInitial();
	void OnDestroy();

protected:
	CWBFDocBase* m_pMyDoc;
	std::vector<CVBOData*> m_lstVBO;
};

#include "HeaderPost.h"