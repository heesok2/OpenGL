#pragma once

#include "..\WBF_BASE\WBFModelBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCModelSample : public CWBFModelBase
{
	DECLARE_MODEL(CWBFCModelSample);

public:
	CWBFCModelSample();
	virtual ~CWBFCModelSample();

public:
	virtual void InitialData();
	virtual void CreateData();
	virtual void DeleteData();
	virtual void ModifyData();

};

#include "HeaderPost.h"

