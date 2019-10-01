#pragma once

#include "..\WBF_BASE\WBFRndrData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRndrLight : public CWBFRndrData
{
	DECLARE_RENDERER(CRndrLight);

public:
	CRndrLight();
	virtual ~CRndrLight();

public:
	virtual UINT GetType() override { return E_RNDR_SAMPLE; }

	virtual void OnInitialData();
	virtual void GLDraw();
};

#include "HeaderPost.h"