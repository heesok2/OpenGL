#include "stdafx.h"
#include "WBFRndrFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

CWBFRndrBase * CWBFRndrFactory::CreateObject(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr == m_mObject.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	auto pObject = (CWBFRndrBase*)(itr->second->CreateObject());
	return pObject;
}

BOOL CWBFRndrFactory::RegisterObject(CRuntimeClass * pRuntime, UINT uiType)
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

void CWBFRndrFactory::UnRegisterObject()
{
	m_mObject.clear();
}