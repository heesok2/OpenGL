#include "RndrSample.h"
#include "GLIncludeHeader.h"

CRndrSample::CRndrSample()
{
}

CRndrSample::~CRndrSample()
{
}

bool CRndrSample::Run()
{
	int nArgc = 1;
	glutInit(&nArgc, nullptr);
	glutCreateWindow("OpenGL Skeleton");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return true;
}

void CRndrSample::MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	}
	glEnd();
	glFlush();
}
