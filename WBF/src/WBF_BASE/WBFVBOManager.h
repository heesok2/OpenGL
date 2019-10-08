#pragma once

#include "HeaderPre.h"

class CDocBase;
class CVBOData;
class __MY_EXT_CLASS__ CVBOManager
{
public:
	CVBOManager(CDocBase* pDoc);
	virtual ~CVBOManager();

public:
	virtual BOOL Exist(UINT eType);
	virtual CVBOData* Lookup(UINT eType);
	virtual void RebuildVBO();

public:
	void OnInitial();
	void OnDestroy();

protected:
	CDocBase* m_pMyDoc;
	std::vector<CVBOData*> m_lstVBO;
};

#include "HeaderPost.h"