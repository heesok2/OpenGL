#include "stdafx.h"
#include "WBFRndrFactory.h"

CWBFRndrFactory& CWBFRndrFactory::GetInstance()
{
	static CWBFRndrFactory obj;
	return obj;
}

CWBFRndrFactory::CWBFRndrFactory()
{
}

CWBFRndrFactory::~CWBFRndrFactory()
{
}

IWBFRndrBase * CWBFRndrFactory::CreateObject(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr == m_mObject.end())
	{
		ASSERT(0);
		return nullptr;
	}

	auto pObject = (IWBFRndrBase*)(itr->second->CreateObject());
	return pObject;
}

BOOL CWBFRndrFactory::RegisterObject(CRuntimeClass * pRuntime, UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
	{
		ASSERT(0);
		m_mObject.erase(itr);
	}

	m_mObject[uiType] = pRuntime;

	return TRUE;
}

void CWBFRndrFactory::UnRegisterObject()
{
	m_mObject.clear();
}