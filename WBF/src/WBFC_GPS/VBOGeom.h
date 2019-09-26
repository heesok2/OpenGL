#pragma once

#include "..\WBF_BASE\WBFVBOData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CVBOGeom : public CWBFVBOData
{
public:
	CVBOGeom();
	virtual ~CVBOGeom();

public:
	// CWBFDataVBO을(를) 통해 상속됨
	virtual void ProcessData(CWBFDocBase * pDoc) override;

};

#include "HeaderPost.h"