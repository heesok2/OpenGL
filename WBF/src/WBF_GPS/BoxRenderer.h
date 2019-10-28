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


	// CDataRenderer을(를) 통해 상속됨
	virtual void GLDraw() override;


	// CDataRenderer을(를) 통해 상속됨
	virtual void GLBuild() override;

};

#include "HeaderPost.h"
