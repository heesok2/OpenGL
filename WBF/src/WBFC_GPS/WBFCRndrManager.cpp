#include "stdafx.h"
#include "WBFCRndrManager.h"

#include "..\WBF_GPS\WBFRndrBase.h"
#include "..\WBF_GPS\WBFRndrFactory.h"

CWBFCRndrManager::CWBFCRndrManager()
{
}

CWBFCRndrManager::~CWBFCRndrManager()
{
}

void CWBFCRndrManager::OnInitialUpdate()
{
	for (long indx = E_RNDR_SAMPLE; indx < E_RNDR_NUM; ++indx)
	{
		auto pObject = CWBFRndrFactory::GetInstance().CreateObject(E_RNDR_SAMPLE);
		if (pObject != nullptr) 
			m_vObject.push_back(pObject);
	}

}

void CWBFCRndrManager::OnDestroy()
{
	for (auto pObject : m_vObject)
	{
		_SAFE_DELETE(pObject);
	}

	m_vObject.clear();
}

void CWBFCRndrManager::GLDrawScen()
{
	for (auto pObject : m_vObject)
		pObject->GLDraw();
}