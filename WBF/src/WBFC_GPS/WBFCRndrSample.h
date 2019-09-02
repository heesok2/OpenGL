#pragma once

#include "..\WBF_GPS\WBFRndrBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrSample : public IWBFRndrBase
{
public:
	CWBFCRndrSample();
	virtual ~CWBFCRndrSample();

public:
	virtual void GLInit(CWBFShaderManager* pShaderMgr);
	virtual void GLDraw();

	virtual void GLBind(CWBFShaderManager* pShaderMgr);
	virtual void GLUseShader(CWBFShaderManager* pShaderMgr);
	virtual void GLUnBind(CWBFShaderManager* pShaderMgr);

protected:
	unsigned int m_nVBO;
	unsigned int m_nVAO;
	unsigned int m_nEBO;
};

#include "HeaderPost.h"