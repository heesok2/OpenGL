#include "stdafx.h"
#include "WBFRndrFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFRndrFactory& CWBFRndrFactory::GetInstance()
{
	static CWBFRndrFactory inst;
	return inst;
}

CWBFRndrFactory::CWBFRndrFactory()
{
}

CWBFRndrFactory::~CWBFRndrFactory()
{
}

BOOL CWBFRndrFactory::Register(UINT uiType, CRuntimeClass * pRuntime)
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

void CWBFRndrFactory::Unregister(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
		m_mObject.erase(itr);
}

CFactoryObjectBase * CWBFRndrFactory::CreateObject(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr == m_mObject.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	auto pObject = itr->second->CreateObject();
	return (CFactoryObjectBase*)pObject;
}