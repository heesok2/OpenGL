#include "stdafx.h"
#include "WBFCRndrSample.h"

#include "..\WBF_BASE\WBFShaderManager.h"

CWBFCRndrSample::CWBFCRndrSample()
{
	m_nVBO = 0;
	m_nVAO = 0;
	m_nEBO = 0;
}

CWBFCRndrSample::~CWBFCRndrSample()
{
}

void CWBFCRndrSample::GLInit(CWBFShaderManager* pShaderMgr)
{
	pShaderMgr->GLCreateShader(CWBFShaderManager::E_SHADER_SAMPLE);
}

void CWBFCRndrSample::GLDraw()
{
	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_TRIANGLES);

	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glVertex3f(0.f, 0.5f, 0.f);

	glEnd();
}

void CWBFCRndrSample::GLBind(CWBFShaderManager * pShaderMgr)
{
}

void CWBFCRndrSample::GLUseShader(CWBFShaderManager * pShaderMgr)
{
}

void CWBFCRndrSample::GLUnBind(CWBFShaderManager * pShaderMgr)
{
}
