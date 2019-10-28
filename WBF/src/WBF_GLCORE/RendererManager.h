#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRendererManager
{
public:
	CRendererManager();
	virtual ~CRendererManager();
	
public:
	void InitialData(CView* pView);
	void CreateRenderer();

};

#include "HeaderPost.h"

