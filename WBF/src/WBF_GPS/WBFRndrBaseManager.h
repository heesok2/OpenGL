#pragma once

#include <vector>
#include "HeaderPre.h"

class IWBFRndrBase;
class CWBFShaderManager;
class __MY_EXT_CLASS__ CWBFRndrBaseManager
{
public:
	CWBFRndrBaseManager();
	virtual ~CWBFRndrBaseManager();

public:
	virtual void OnInitialUpdate() = 0;
	virtual void OnDestroy() = 0;
	virtual void GLDrawScen() = 0;

protected:
	CWBFShaderManager* m_pShaderMgr;
	std::vector<IWBFRndrBase*> m_vObject;
};

#include "HeaderPost.h"