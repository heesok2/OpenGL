#include "stdafx.h"
#include "WBFVBOFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFVBOFactory& CWBFVBOFactory::GetInstance()
{
	static CWBFVBOFactory inst;
	return inst;
}

CWBFVBOFactory::CWBFVBOFactory()
{
}


CWBFVBOFactory::~CWBFVBOFactory()
{
}

BOOL CWBFVBOFactory::Register(UINT uiType, CRuntimeClass * pRuntime)
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

void CWBFVBOFactory::Unregister(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
		m_mObject.erase(itr);
}

CFactoryObjectBase * CWBFVBOFactory::CreateObject(UINT uiType)
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