#include "stdafx.h"
#include "WBFModelFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

CWBFModelData * CWBFModelFactory::CreateObject(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr == m_mObject.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	auto pObject = (CWBFModelData*)(itr->second->CreateObject());
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
