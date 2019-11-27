#pragma once

#include "..\WBF_GLCORE\DataRenderer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CMeshRenderer : public CDataRenderer
{
	typedef struct tagMesh
	{
		UINT uiVAO;
		UINT uiSize;
		UINT uiDiff;

	} TMesh, *LPTMesh;

public:
	CMeshRenderer();
	virtual ~CMeshRenderer();

	DECLARE_DYNAMIC_RENDERER(CMeshRenderer);

public:
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) override;
	virtual void GLDraw(CViewHelper * pHelper) override;

protected:
	void SetMeshData(CViewHelper* pHelper);
	void GLSetTexture(CViewHelper* pHelper);

protected:
	std::vector<TMesh> m_aData;
	std::map<DKEY, UINT> m_mTexIndex;
};

#include "HeaderPost.h"
