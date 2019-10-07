#pragma once

#include <vector>
#include "..\WBF_BASE\ModelData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModelLight : public CModelData
{
	struct TModelLight
	{
		DKEY BodyKey;
		glm::vec3 Pos;
	};

public:
	CModelLight();
	virtual ~CModelLight();

	DECLARE_MODEL(CModelLight);

public:
	virtual UINT GetType() override { return E_MODEL_LIGHT; }
	virtual void Release() override;
	virtual void Build() override;
	virtual void Draw(CShader* pShader) override;

protected:
	std::vector<TModelLight> m_lstLight;

};

#include "HeaderPost.h"