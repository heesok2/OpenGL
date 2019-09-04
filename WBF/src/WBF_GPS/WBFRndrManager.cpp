#include "stdafx.h"
#include "WBFRndrManager.h"
#include "WBFRndrBase.h"

CWBFRndrManager::CWBFRndrManager()
	: m_pShaderMgr(nullptr)
{
}

CWBFRndrManager::~CWBFRndrManager()
{
}

void CWBFRndrManager::GLDrawScen()
{
	for (auto pRenderer : m_vRenderer)
	{
		pRenderer->GLBind(m_pShaderMgr);
		pRenderer->GLUseShader(m_pShaderMgr);
		pRenderer->GLDraw();
		pRenderer->GLUnBind(m_pShaderMgr);
	}
}