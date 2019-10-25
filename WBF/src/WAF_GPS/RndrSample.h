#pragma once

#include "..\WBF_BASE\RndrData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRndrSample : public CRndrData
{
public:
	CRndrSample();
	virtual ~CRndrSample();

	DECLARE_RENDERER(CRndrSample);

public:
	virtual UINT GetType() override { return E_RNDR_SAMPLE; }

	virtual void OnInitialData();
	virtual void GLDraw();
};

#include "HeaderPost.h"