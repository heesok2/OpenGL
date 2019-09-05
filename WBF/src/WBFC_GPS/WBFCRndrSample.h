#pragma once

#include "..\WBF_GPS\WBFRndrBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrSample : public CWBFRndrBase
{
	DECLARE_RENDERER(CWBFCRndrSample);

public:
	CWBFCRndrSample();
	virtual ~CWBFCRndrSample();

public:
	virtual void GLInit(CWBFShaderManager* pShaderMgr);
	virtual void GLDraw();

};

#include "HeaderPost.h"