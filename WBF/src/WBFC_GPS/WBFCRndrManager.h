#pragma once

#include "..\WBF_BASE\WBFRndrBaseManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrManager : public CWBFRndrBaseManager
{
public:
	CWBFCRndrManager(CWBFViewBase* pView);
	virtual ~CWBFCRndrManager();

public:
	virtual void OnInitialUpdate();
	virtual void OnDestroy();
	virtual void GLDrawScene();

};

#include "HeaderPost.h"