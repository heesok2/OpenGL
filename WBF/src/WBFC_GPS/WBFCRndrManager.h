#pragma once

#include "..\WBF_GPS\WBFRndrManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrManager : public IWBFRndrManager
{
public:
	CWBFCRndrManager();
	virtual ~CWBFCRndrManager();

public:
	virtual void CreateRndr(E_RNDR_D eType);
	virtual void GLInit();
	virtual void GLDraw();

};

#include "HeaderPost.h"