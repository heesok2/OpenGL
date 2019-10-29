#pragma once

#include "..\WBF_GLCORE\DataRenderer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CContainerBoxRenderer : public CDataRenderer
{
public:
	CContainerBoxRenderer();
	virtual ~CContainerBoxRenderer();

	DECLARE_DYNAMIC_RENDERER(CContainerBoxRenderer);

public:
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) override;
	virtual void GLDraw() override;
};

#include "HeaderPost.h"
