#pragma once

#include "..\WBF_BASE\RndrData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRndrLight : public CRndrData
{
	DECLARE_RENDERER(CRndrLight);

public:
	CRndrLight();
	virtual ~CRndrLight();

public:
	virtual UINT GetType() override { return E_RNDR_LIGHT; }
	virtual void OnInitialData();
	virtual void GLDraw();

};

#include "HeaderPost.h"