#include "stdafx.h"
#include "WBFCRndrManager.h"
#include "WBFCRndrSample.h"

CWBFCRndrManager::CWBFCRndrManager()
{
}


CWBFCRndrManager::~CWBFCRndrManager()
{
}

void CWBFCRndrManager::CreateRndr(E_RNDR_D eType)
{
	switch (eType)
	{
	case IWBFRndrManager::E_RNDR_SAMPLE:
		{
			m_pRndr = new CWBFCRndrSample;
		}
		break;
	default:
		break;
	}
}

void CWBFCRndrManager::GLInit()
{
	m_pRndr->GLInit();
}

void CWBFCRndrManager::GLDraw()
{
	m_pRndr->GLDraw();
}