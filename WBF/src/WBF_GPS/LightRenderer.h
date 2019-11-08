#pragma once

#include "..\WBF_GLCORE\DataRenderer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CLightRenderer : public CDataRenderer
{
	typedef struct tagLightBox
	{
		UINT uiVAO;
		UINT uiSize;
		glm::mat4 glModelMatrix;

	} TLight, *LPTLight;

public:
	CLightRenderer();
	virtual ~CLightRenderer();

	DECLARE_DYNAMIC_RENDERER(CLightRenderer);

public:
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) override;
	virtual void GLDraw(CViewHelper * pHelper) override;

protected:
	void SetLightData(CViewHelper* pHelper);

protected:
	std::vector<TLight> m_aData;
};

#include "HeaderPost.h"