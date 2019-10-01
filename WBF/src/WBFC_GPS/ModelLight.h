#pragma once

#include "..\WBF_BASE\WBFModelData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModelLight : public CWBFModelData
{
public:
	CModelLight();
	virtual ~CModelLight();

	DECLARE_MODEL(CModelLight);

public:
	virtual UINT GetType() override { return E_MODEL_LIGHT; }


	// CWBFModelData을(를) 통해 상속됨
	virtual BOOL IsValidModel() override;

	virtual void GLInitialData() override;

	virtual void GLCreateVBO() override;

	virtual void GLAttachData() override;

	virtual void GLBind() override;

	virtual void GLDraw() override;

	virtual void GLUnbind() override;

	virtual void GLDelete() override;

public:
	UINT uiVAO;

};

#include "HeaderPost.h"