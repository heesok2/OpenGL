#pragma once

#include "..\WBF_BASE\WBFOption.h"

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFGPSOption : public opt::IWBFOption
{
public:
	CWBFGPSOption();
	virtual ~CWBFGPSOption();

public:
	UINT uiPolygonFace;
	UINT uiPolygonMode;

	float fRatio;

};
#include "HeaderPost.h"

