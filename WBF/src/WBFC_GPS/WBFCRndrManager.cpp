#include "stdafx.h"
#include "WBFCRndrManager.h"
#include "WBFCRndrSample.h"
#include "..\WBF_BASE\WBFShaderManager.h"

CWBFCRndrManager::CWBFCRndrManager(CWBFShaderManager * pShaderMgr)
	: IWBFRndrManager(pShaderMgr)
{
}

CWBFCRndrManager::~CWBFCRndrManager()
{
}

void CWBFCRndrManager::GLCreate(E_RNDR_TYPE eType)
{
	m_pShaderMgr->GLShaderVersion();

	IWBFRndrBase* pRenderer = nullptr;
	
	switch (eType)
	{
	case IWBFRndrManager::E_RNDR_SAMPLE:
		{
			pRenderer = new CWBFCRndrSample;
		}
		break;
	default:
		break;
	}

	if (pRenderer != nullptr)
	{
		pRenderer->GLInit(m_pShaderMgr);
		m_vRenderer.push_back(pRenderer);
	}
}