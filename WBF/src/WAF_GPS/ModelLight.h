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
	virtual void Release() override;
	virtual void Build() override;
	virtual void Draw(CShader* pShader) override;

};

#include "HeaderPost.h"