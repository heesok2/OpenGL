#include "stdafx.h"
#include "WBFRndrManager.h"
#include "WBFRndrBase.h"

IWBFRndrManager::IWBFRndrManager(CWBFShaderManager * pShaderMgr)
	: m_pShaderMgr(pShaderMgr)
{
}

IWBFRndrManager::~IWBFRndrManager()
{
}

void IWBFRndrManager::GLDraw()
{
	for (auto pRenderer : m_vRenderer)
	{
		pRenderer->GLBind(m_pShaderMgr);
		pRenderer->GLUseShader(m_pShaderMgr);
		pRenderer->GLDraw();
		pRenderer->GLUnBind(m_pShaderMgr);
	}
}