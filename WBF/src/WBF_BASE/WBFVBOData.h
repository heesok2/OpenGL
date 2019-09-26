#pragma once

#include "HeaderPre.h"

class CWBFDocBase;
class __MY_EXT_CLASS__ CWBFVBOData
{
public:
	CWBFVBOData();
	virtual ~CWBFVBOData();

public:
	virtual void ProcessData(CWBFDocBase* pDoc) = 0;

};

#include "HeaderPost.h"