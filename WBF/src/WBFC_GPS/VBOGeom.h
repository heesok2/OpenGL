#pragma once

#include "..\WBF_BASE\WBFVBOData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CVBOGeom : public CWBFVBOData
{
public:
	CVBOGeom();
	virtual ~CVBOGeom();

	DECLARE_VBO(CVBOGeom);

public:
	// CWBFDataVBO을(를) 통해 상속됨
	virtual void ProcessData(CWBFDocBase * pDoc) override;

public:
	UINT uiVBO;
	UINT uiEBO;

	UINT uiVertexNum;
};

#include "HeaderPost.h"