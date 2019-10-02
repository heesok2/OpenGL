#pragma once

#include <vector>
#include "HeaderPre.h"

class CWBFViewBase;
class CWBFRndrData;
class CShaderManager;
class __MY_EXT_CLASS__ CWBFRndrDataManager
{
public:
	CWBFRndrDataManager(CWBFViewBase* pView);
	virtual ~CWBFRndrDataManager();

public:
	virtual void OnInitial() = 0;
	virtual void OnDestroy() = 0;
	virtual void GLDrawScene() = 0;

public:
	CWBFRndrData* GetRender(UINT uiType);
	CWBFViewBase* GetView() { return m_pView; }

protected:
	CWBFViewBase* m_pView;
	std::vector<CWBFRndrData*> m_vObject;
};

#include "HeaderPost.h"