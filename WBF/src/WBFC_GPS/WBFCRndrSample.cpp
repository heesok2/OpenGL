#include "stdafx.h"
#include "WBFCRndrSample.h"

CWBFCRndrSample::CWBFCRndrSample()
{
}


CWBFCRndrSample::~CWBFCRndrSample()
{
}

void CWBFCRndrSample::GLInit()
{
	glClearColor(1.f, 0.f, 0.f, 1.f);
}

void CWBFCRndrSample::GLDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_TRIANGLES);

	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glVertex3f(0.f, 0.5f, 0.f);

	glEnd();
}
