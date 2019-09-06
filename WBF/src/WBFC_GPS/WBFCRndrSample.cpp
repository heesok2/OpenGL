#include "stdafx.h"
#include "WBFCRndrSample.h"

#include "..\WBF_GPS\WBFShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_RENDERER(CWBFCRndrSample, gps::E_GPS_SAMPLE);

CWBFCRndrSample::CWBFCRndrSample() : CWBFRndrBase()
{
}

CWBFCRndrSample::~CWBFCRndrSample()
{
}

void CWBFCRndrSample::GLInit(CWBFShaderManager* pShaderMgr)
{
	pShaderMgr->GLCreateShader(gps::E_GPS_SAMPLE);
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