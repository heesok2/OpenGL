#pragma once

#include "..\WBF_BASE\WBFOption.h"

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFGPSOption : public CWBFOption
{
public:
	CWBFGPSOption();
	virtual ~CWBFGPSOption();
	
public:
	UINT uiPolygonFace;
	UINT uiPolygonMode;

};
#include "HeaderPost.h"

