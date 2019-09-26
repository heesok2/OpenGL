#include "stdafx.h"
#include "ModelAppManager.h"

#include "..\WBF_LIB\WBFObserverDefine.h"
#include "..\WBF_BASE\WBFModelFactory.h"
#include "..\WBF_BASE\WBFModelData.h"
#include "..\WBF_BASE\WBFVBOManager.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\WBFPackageData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModelAppManager::CModelAppManager(CWBFDocBase* pDoc)
	: CWBFModelDataManager(pDoc)
{
}


CModelAppManager::~CModelAppManager()
{
}

void CModelAppManager::UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case E_UPDATE_DB_CHANGED:
		{

		}
		break;
	default:
		break;
	}
}

void CModelAppManager::OnInitial()
{
	CWBFModelDataManager::OnInitial();

	m_pMyDoc->GetPackage()->Attached(this);

	for (long indx = gps::E_GPS_SAMPLE; indx < gps::E_GPS_NUM; ++indx)
	{
		auto pObject = CWBFModelFactory::GetInstance().CreateObject(gps::E_GPS_SAMPLE);
		if (pObject == nullptr) continue;
		
		pObject->SetHelper(this);
		m_vObject.push_back(pObject);
	}
}

void CModelAppManager::OnDestroy()
{
	auto pPackage = m_pMyDoc->GetPackage();
	if (pPackage)
		pPackage->Dettached(this);

	for (auto pObject : m_vObject)
	{
		_SAFE_DELETE(pObject);
	}

	m_vObject.clear();

	CWBFModelDataManager::OnDestroy();
}

void CModelAppManager::OnUpdateAll()
{
	for (auto pObject : m_vObject)
		pObject->SetFlag(MODEL_UPDATE);
}

void CModelAppManager::OnUpdateOnly(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			pObject->SetFlag(MODEL_UPDATE);
	}
}

void CModelAppManager::GLInitialData()
{
	for (auto pObject : m_vObject)
	{
		auto uiFlag = pObject->GetFlag();
		if (uiFlag & MODEL_UPDATE)
		{
			pObject->GLInitialData();
			pObject->GLCreateVBO();
		}

		pObject->InitFlag();
	}
}