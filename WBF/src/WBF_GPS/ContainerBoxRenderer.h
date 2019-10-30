#pragma once

#include "..\WBF_GLCORE\DataRenderer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CContainerBoxRenderer : public CDataRenderer
{
	typedef struct tagContainerBox
	{
		glm::mat4 glModelViewProjectionMatrix; // Position translation
		glm::mat4 glModelMatrix;

		glm::vec3 CameraPos;
		glm::vec3 LightPos;

		glm::vec3 glModelColor;
		glm::vec3 glLightColor;

		UINT uiVAO;
		UINT uiSize;

	} TContainerBox, *LPTContainerBox;

public:
	CContainerBoxRenderer();
	virtual ~CContainerBoxRenderer();

	DECLARE_DYNAMIC_RENDERER(CContainerBoxRenderer);

public:
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) override;
	virtual void GLDraw() override;

public:
	std::vector<TContainerBox> m_lstData;
};

#include "HeaderPost.h"
