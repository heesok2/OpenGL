#include "stdafx.h"
#include "RndrFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRndrFactory& CRndrFactory::GetInstance()
{
	static CRndrFactory inst;
	return inst;
}

CRndrFactory::CRndrFactory()
{
}

CRndrFactory::~CRndrFactory()
{
}

BOOL CRndrFactory::Register(UINT uiType, CRuntimeClass * pRuntime)
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

void CRndrFactory::Unregister(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
		m_mObject.erase(itr);
}

CFactoryObjectBase * CRndrFactory::CreateObject(UINT uiType)
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