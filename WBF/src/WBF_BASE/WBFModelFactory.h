#pragma once

#include <map>
#include "HeaderPre.h"

class CWBFModelBase;
class __MY_EXT_CLASS__ CWBFModelFactory
{
public:
	static CWBFModelFactory& GetInstance();

	CWBFModelFactory();
	virtual ~CWBFModelFactory();

public:
	CWBFModelBase* CreateObject(UINT uiType);

	BOOL RegisterObject(CRuntimeClass* pClass, UINT uiType);
	void UnRegisterObject();

private:
	std::map<UINT, CRuntimeClass*> m_mObject;
};

#include "HeaderPost.h"

