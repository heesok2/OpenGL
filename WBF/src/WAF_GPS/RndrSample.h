#pragma once

#include "..\WBF_BASE\RndrData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRndrSample : public CRndrData
{
	DECLARE_RENDERER(CRndrSample);

public:
	CRndrSample();
	virtual ~CRndrSample();

public:
	virtual UINT GetType() override { return E_RNDR_SAMPLE; }

	virtual void OnInitialData();
	virtual void GLDraw();
};

#include "HeaderPost.h"