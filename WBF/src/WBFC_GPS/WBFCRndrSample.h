#pragma once

#include "..\WBF_GPS\WBFRndrBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrSample : public IWBFRndrBase
{
public:
	CWBFCRndrSample();
	virtual ~CWBFCRndrSample();

public:
	virtual void GLInit();
	virtual void GLDraw();
};

#include "HeaderPost.h"