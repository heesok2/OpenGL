#pragma once

#include <vector>
#include "HeaderPre.h"

class IWBFRndrBase;
class CWBFShaderManager;
class __MY_EXT_CLASS__ IWBFRndrManager
{
public:
	enum E_RNDR_TYPE 
	{ 
		E_RNDR_UNKNOWN = 0, 
		E_RNDR_SAMPLE,

		E_RNDR_NUM 
	};

public:
	IWBFRndrManager(CWBFShaderManager* pShaderMgr);
	virtual ~IWBFRndrManager();

public:
	virtual void GLCreate(E_RNDR_TYPE eType) {};
	virtual void GLDraw();

protected:
	CWBFShaderManager* m_pShaderMgr;
	std::vector<IWBFRndrBase*> m_vRenderer;
};

#include "HeaderPost.h"