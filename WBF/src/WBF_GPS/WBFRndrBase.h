#pragma once

#include "HeaderPre.h"

class CWBFShaderManager;
class __MY_EXT_CLASS__ IWBFRndrBase
{
public:
	IWBFRndrBase() {}
	virtual ~IWBFRndrBase() {}

public:
	virtual void GLInit(CWBFShaderManager* pShaderMgr) = 0;
	virtual void GLDraw() = 0;

	virtual void GLBind(CWBFShaderManager* pShaderMgr) {}
	virtual void GLUseShader(CWBFShaderManager* pShaderMgr) {}
	virtual void GLUnBind(CWBFShaderManager* pShaderMgr) {}
};
#include "HeaderPost.h"