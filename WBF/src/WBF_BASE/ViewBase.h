#pragma once

#include "..\WBF_GLCORE\GLCtrlView.h"

#include "HeaderPre.h"

class CModelManager;
class CRndrManager;
class __MY_EXT_CLASS__ CViewBase : public CGLCtrlView
{
public:
	CViewBase();
	virtual ~CViewBase();

public:
	virtual CModelManager* GetModelManager() = 0;
	virtual CRndrManager* GetRndrManager() = 0;

};

#include "HeaderPost.h"