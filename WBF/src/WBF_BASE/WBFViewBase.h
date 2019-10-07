#pragma once

#include "HeaderPre.h"

class CModelManager;
class CRndrManager;
class __MY_EXT_CLASS__ CWBFViewBase : public CView
{
public:
	CWBFViewBase();
	virtual ~CWBFViewBase();

public:
	virtual CModelManager* GetModelManager() = 0;
	virtual CRndrManager* GetRndrManager() = 0;

public:
	virtual void BeginwglCurrent() = 0;
	virtual void EndwglCurrent() = 0;
	virtual void SwapBuffers() = 0;

public:
	virtual BOOL GetViewMatrix(glm::mat4& mat) { ASSERT(g_warning); return FALSE; }
	virtual BOOL GetProjectionMatrix(glm::mat4& mat) { ASSERT(g_warning); return FALSE; }
	virtual BOOL GetCameraPos(glm::vec3& CamPos) { ASSERT(g_warning); return FALSE; }

};

#include "HeaderPost.h"