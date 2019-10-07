#pragma once

#include <vector>
#include "HeaderPre.h"

class CWBFViewBase;
class CRndrData;
class CShaderManager;
class __MY_EXT_CLASS__ CRndrManager
{
public:
	CRndrManager(CWBFViewBase* pView);
	virtual ~CRndrManager();

public:
	virtual void OnInitial() = 0;
	virtual void OnDestroy() = 0;
	virtual void GLDrawScene() = 0;

public:
	CWBFViewBase* GetView() { return m_pView; }
	CRndrData* GetRender(UINT uiType);

protected:
	CWBFViewBase* m_pView;
	std::vector<CRndrData*> m_vObject;
};

#include "HeaderPost.h"