#pragma once

#include "..\WBF_GPS\WBFRndrBaseManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrManager : public CWBFRndrBaseManager
{
public:
	CWBFCRndrManager();
	virtual ~CWBFCRndrManager();

public:
	virtual void OnInitialUpdate();
	virtual void OnDestroy();
	virtual void GLDrawScene();

};

#include "HeaderPost.h"