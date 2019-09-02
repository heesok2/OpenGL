#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ IWBFRndrBase
{
public:
	IWBFRndrBase() {}
	virtual ~IWBFRndrBase() {}

public:
	virtual void GLInit() = 0;
	virtual void GLDraw() = 0;

};
#include "HeaderPost.h"