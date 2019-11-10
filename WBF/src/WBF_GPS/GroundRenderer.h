#pragma once

#include "..\WBF_GLCORE\DataRenderer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CGroundRenderer : public CDataRenderer
{
	typedef struct tagGround
	{
		UINT uiVAO;
		UINT uiSize;

	} TGround, *LPTGround;

public:
	CGroundRenderer();
	virtual ~CGroundRenderer();

	DECLARE_DYNAMIC_RENDERER(CGroundRenderer);

public:
	virtual void GLRelease() override;
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) override;
	virtual void GLDraw(CViewHelper * pHelper) override;

protected:
	UINT m_uiVAO;
	UINT m_uiVBO;
	UINT m_uiEBO;

	TGround m_tData;

};

#include "HeaderPost.h"