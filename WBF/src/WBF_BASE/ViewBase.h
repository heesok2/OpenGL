#pragma once

#include "HeaderPre.h"

class CModelManager;
class CRndrManager;
class __MY_EXT_CLASS__ CViewBase : public CView
{
public:
	CViewBase();
	virtual ~CViewBase();

public:
	virtual void BeginwglCurrent() = 0;
	virtual void EndwglCurrent() = 0;
	virtual void SwapBuffers() = 0;

	virtual BOOL GetEyePosition(glm::vec3& CamPos) = 0;
	virtual BOOL GetViewMatrix(glm::mat4& mat) = 0;
	virtual BOOL GetProjectionMatrix(glm::mat4& mat) = 0;

public:
	virtual CModelManager* GetModelManager() = 0;
	virtual CRndrManager* GetRndrManager() = 0;

};

#include "HeaderPost.h"