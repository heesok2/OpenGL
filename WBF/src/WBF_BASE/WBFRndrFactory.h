#pragma once

#include <map>
#include "HeaderPre.h"

class CWBFRndrData;
class __MY_EXT_CLASS__ CWBFRndrFactory
{
public:
	static CWBFRndrFactory& GetInstance();

	CWBFRndrFactory();
	~CWBFRndrFactory();

public:
	CWBFRndrData* CreateObject(UINT uiType);

	BOOL RegisterObject(CRuntimeClass* pClass, UINT uiType);
	void UnRegisterObject();

private:
	std::map<UINT, CRuntimeClass*> m_mObject;
};

#include "HeaderPost.h"
