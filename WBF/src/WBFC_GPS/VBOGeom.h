#pragma once

#include <map>
#include "..\WBF_BASE\WBFVBOData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CVBOGeom : public CVBOData
{
public:
	CVBOGeom();
	virtual ~CVBOGeom();

	DECLARE_DYNAMIC_VBO(CVBOGeom);

public:
	virtual UINT GetType() override { return E_VBO_GEOM; }
	virtual void Release() override;
	virtual void Build(CWBFDocBase * pDoc) override;
	virtual void Draw() override;

private:
	std::map<UINT, TEntityVBO> m_mVAO; // Body key to VAO

};

#include "HeaderPost.h"