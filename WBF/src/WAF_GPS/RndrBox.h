#pragma once

#include "..\WBF_BASE\RndrData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRndrBox : public CRndrData
{
	DECLARE_RENDERER(CRndrBox);

public:
	CRndrBox();
	virtual ~CRndrBox();

public:
	virtual UINT GetType() override { return E_RNDR_BOX; }
	virtual void OnInitialData() override;
	virtual void GLDraw() override;

};

#include "HeaderPost.h"