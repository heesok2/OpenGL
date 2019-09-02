#pragma once

#include <vector>
#include "HeaderPre.h"

class IWBFRndrBase;
class __MY_EXT_CLASS__ IWBFRndrManager
{
public:
	enum E_RNDR_D { 
		E_RNDR_DEF = 0, 
		E_RNDR_SAMPLE, 
		E_RNDR_NUM };

public:
	IWBFRndrManager();
	virtual ~IWBFRndrManager();

public:
	virtual void CreateRndr(E_RNDR_D eType) {};
	virtual void GLInit();
	virtual void GLDraw();

protected:
	IWBFRndrBase* m_pRndr;
};

#include "HeaderPost.h"