#pragma once

#include "HeaderPre.h"

class CWBFRndrBaseManager;
class __MY_EXT_CLASS__ CWBFViewBase : public CView
{
public:
	CWBFViewBase();
	virtual ~CWBFViewBase();

public:
	virtual CWBFRndrBaseManager* GetRenderManager() { ASSERT(g_warning); return nullptr; }
	virtual BOOL GetViewMatrix(glm::mat4& matView) { ASSERT(g_warning); return FALSE; }

};

#include "HeaderPost.h"