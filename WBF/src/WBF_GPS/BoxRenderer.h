#pragma once

#include "..\WBF_GLCORE\DataRenderer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CBoxRenderer : public CDataRenderer
{
public:
	CBoxRenderer();
	virtual ~CBoxRenderer();

	DECLARE_DYNAMIC_RENDERER(CBoxRenderer);

public:
	virtual void GLBuild(CDocument * pDoc, UINT uiFlag) override;
	virtual void GLDraw() override;
};

#include "HeaderPost.h"
