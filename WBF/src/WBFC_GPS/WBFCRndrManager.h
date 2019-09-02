#pragma once

#include "..\WBF_GPS\WBFRndrManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrManager : public IWBFRndrManager
{
public:
	CWBFCRndrManager(CWBFShaderManager* pShaderMgr);
	virtual ~CWBFCRndrManager();

public:
	virtual void GLCreate(E_RNDR_TYPE eType);

protected:

};

#include "HeaderPost.h"