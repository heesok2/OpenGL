#include "stdafx.h"
#include "WBFCRndrManager.h"

#include "..\WBF_BASE\WBFRndrFactory.h"
#include "..\WBF_BASE\WBFRndrBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFCRndrManager::CWBFCRndrManager(CWBFViewBase* pView)
	: CWBFRndrBaseManager(pView)
{
}

CWBFCRndrManager::~CWBFCRndrManager()
{
}

void CWBFCRndrManager::OnInitialUpdate()
{
	for (long indx = gps::E_GPS_SAMPLE; indx < gps::E_GPS_NUM; ++indx)
	{
		auto pObject = CWBFRndrFactory::GetInstance().CreateObject(gps::E_GPS_SAMPLE);
		if (pObject != nullptr) m_vObject.push_back(pObject);
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

void CWBFCRndrManager::GLDrawScene()
{
	for (auto pObject : m_vObject)
		pObject->GLDraw();
}