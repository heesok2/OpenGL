#include "stdafx.h"
#include "ModelFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModelFactory & CModelFactory::GetInstance()
{
	static CModelFactory inst;
	return inst;
}

CModelFactory::CModelFactory()
{
}


CModelFactory::~CModelFactory()
{
}

BOOL CModelFactory::Register(UINT uiType, CRuntimeClass * pRuntime)
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

void CModelFactory::Unregister(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
		m_mObject.erase(itr);
}

CFactoryObjectBase * CModelFactory::CreateObject(UINT uiType)
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