#pragma once

#include <vector>
#include "HeaderPre.h"

class CWBFViewBase;
class CWBFRndrBase;
class CWBFShaderManager;
class __MY_EXT_CLASS__ CWBFRndrBaseManager
{
public:
	CWBFRndrBaseManager(CWBFViewBase* pView);
	virtual ~CWBFRndrBaseManager();

public:
	virtual void OnInitialUpdate() = 0;
	virtual void OnDestroy() = 0;
	virtual void GLDrawScene() = 0;

protected:
	CWBFViewBase* m_pView;
	std::vector<CWBFRndrBase*> m_vObject;
};

#include "HeaderPost.h"