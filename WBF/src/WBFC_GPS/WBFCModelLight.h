#pragma once

#include "..\WBF_BASE\WBFModelBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCModelLight : public CWBFModelBase
{
	DECLARE_MODEL(CWBFCModelLight);

public:
	CWBFCModelLight();
	virtual ~CWBFCModelLight();

public:
	// CWBFModelBase을(를) 통해 상속됨
	virtual BOOL IsValidModel() override;
	virtual void GLInitialData() override;
	virtual void GLCreateVBO() override;
	virtual void GLAttachData() override;
	virtual void GLBind() override;
	virtual void GLDraw() override;
	virtual void GLUnbind() override;
	virtual void GLDelete() override;
};

#include "HeaderPost.h"