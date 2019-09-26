#pragma once

#include "..\WBF_BASE\WBFVBOData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CVBOGeom : CWBFVBOData
{
public:
	CVBOGeom();
	virtual ~CVBOGeom();

public:
	// CWBFDataVBO을(를) 통해 상속됨
	virtual void ProcessData(CWBFDocBase * pDocBase) override;

};

#include "HeaderPost.h"