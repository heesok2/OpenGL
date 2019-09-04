#pragma once

#include <vector>
#include "HeaderPre.h"

class IWBFRndrBase;
class CWBFShaderManager;
class __MY_EXT_CLASS__ CWBFRndrManager
{
public:
	enum E_RNDR_TYPE 
	{ 
		E_RNDR_UNKNOWN = 0, 
		E_RNDR_SAMPLE,

		E_RNDR_NUM 
	};

public:
	CWBFRndrManager();
	virtual ~CWBFRndrManager();

public:
	void OnInitialUpdate() {}
	void OnDestroy() {}

	void GLDrawScen();

protected:
	CWBFShaderManager* m_pShaderMgr;
	std::vector<IWBFRndrBase*> m_vRenderer;
};

#include "HeaderPost.h"