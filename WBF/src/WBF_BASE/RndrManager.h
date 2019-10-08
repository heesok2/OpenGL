#pragma once

#include "HeaderPre.h"

class CViewBase;
class CRndrData;
class CShaderManager;
class __MY_EXT_CLASS__ CRndrManager
{
public:
	CRndrManager(CViewBase* pView);
	virtual ~CRndrManager();

public:
	virtual void OnInitial() = 0;
	virtual void OnDestroy() = 0;
	virtual void GLDrawScene() = 0;

public:
	CViewBase* GetView() { return m_pView; }
	CRndrData* GetRender(UINT uiType);

protected:
	CViewBase* m_pView;
	std::vector<CRndrData*> m_vObject;
};

#include "HeaderPost.h"