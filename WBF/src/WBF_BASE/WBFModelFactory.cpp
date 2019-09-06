#include "stdafx.h"
#include "WBFModelFactory.h"

CWBFModelFactory & CWBFModelFactory::GetInstance()
{
	static CWBFModelFactory obj;
	return obj;
}

CWBFModelFactory::CWBFModelFactory()
{
}


CWBFModelFactory::~CWBFModelFactory()
{
	UnRegisterObject();
}

CWBFModelBase * CWBFModelFactory::CreateObject(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr == m_mObject.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	auto pObject = (CWBFModelBase*)(itr->second->CreateObject());
	return pObject;
}

BOOL CWBFModelFactory::RegisterObject(CRuntimeClass * pRuntime, UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
	{
		ASSERT(g_warning);
		m_mObject.erase(itr);
	}

	m_mObject[uiType] = pRuntime;

	return TRUE;
}

void CWBFModelFactory::UnRegisterObject()
{
	m_mObject.clear();
}
