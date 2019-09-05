#include "stdafx.h"
#include "WBFCRndrSample.h"

#include "..\WBF_GPS\WBFShaderManager.h"

IMPLEMENT_RENDERER(CWBFCRndrSample, E_RNDR_SAMPLE);

CWBFCRndrSample::CWBFCRndrSample() : IWBFRndrBase()
{
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