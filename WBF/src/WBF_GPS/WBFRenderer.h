#pragma once

#include "HeaderPre.h"
class __MY_EXT_CLASS__ IWBFRenderer
{
public:
	IWBFRenderer() {}
	virtual ~IWBFRenderer() {}

public:
	virtual void GLDraw() = 0;

};
#include "HeaderPost.h"