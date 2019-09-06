#include "stdafx.h"
#include "WBFCModelManager.h"

#include "..\WBF_BASE\WBFModelFactory.h"
#include "..\WBF_BASE\WBFModelBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFCModelManager::CWBFCModelManager(CWBFDocBase* pDoc)
	: CWBFModelBaseManager(pDoc)
{
}


CWBFCModelManager::~CWBFCModelManager()
{
}

void CWBFCModelManager::OnInitialUpdate()
{
	for (long indx = gps::E_GPS_SAMPLE; indx < gps::E_GPS_NUM; ++indx)
	{
		auto pObject = CWBFModelFactory::GetInstance().CreateObject(gps::E_GPS_SAMPLE);
		if (pObject != nullptr) m_vObject.push_back(pObject);
	}
}

void CWBFCModelManager::OnDestroy()
{
	for (auto pObject : m_vObject)
	{
		_SAFE_DELETE(pObject);
	}

	m_vObject.clear();
}

void CWBFCModelManager::OnUpdateAll()
{
	for (auto pObject : m_vObject)
	{
		pObject->CreateData();
	}
}

void CWBFCModelManager::OnUpdateOnly(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (uiType)
		{
			pObject->CreateData();
		}
	}
}

void CWBFCModelManager::OnDeleteAll()
{
	for (auto pObject : m_vObject)
	{
		pObject->InitialData();
	}
}

void CWBFCModelManager::OnDeleteOnly(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (uiType)
		{
			pObject->InitialData();
		}
	}
}