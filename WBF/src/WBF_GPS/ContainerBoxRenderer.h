#pragma once

#include "..\WBF_GLCORE\DataRenderer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CContainerBoxRenderer : public CDataRenderer
{
	typedef struct tagContainerBox
	{
		UINT uiVAO;
		UINT uiSize;
		glm::mat4 glModelMatrix;

	} TContainerBox, *LPTContainerBox;

public:
	CContainerBoxRenderer();
	virtual ~CContainerBoxRenderer();

	DECLARE_DYNAMIC_RENDERER(CContainerBoxRenderer);

public:
	virtual void GLRelease() override;
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) override;
	virtual void GLDraw(CViewHelper * pHelper) override;

protected:
	void SetLightData(CViewHelper * pHelper);
	void SetContainerData(CViewHelper * pHelper);
	void GLSetContainerTexture(CViewHelper * pHelper);

protected:	
	UINT m_uiSmaileTex2D;
	UINT m_uiContainerTex2D;		
	glm::vec3 m_aLightPos;
	std::vector<TContainerBox> m_aData;

};

#include "HeaderPost.h"
