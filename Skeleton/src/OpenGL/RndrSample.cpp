#include "RndrSample.h"
#include "GlutIncludeHeader.h"

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
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("OpenGL Sample Display");
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200, 200, -200, 200, -200, 200);
	glutDisplayFunc(MyDisplay);
	//glutReshapeFunc(MyReShape);
	glutMainLoop();

	return true;
}

void CRndrSample::MyDisplay()
{
	enum DISP_MODE { DISP_POLYGON, DISP_WIRE_SPHERE, DISP_NUM };

	auto eType = DISP_POLYGON;

	glClear(GL_COLOR_BUFFER_BIT); // COLOR BUFFER 초기화
	glViewport(0, 0, 300, 300);

	switch (eType)
	{
	case DISP_POLYGON:
	{
		glBegin(GL_POLYGON); // POLYGON 그리기 모드 셋팅
		{
			glVertex3f(-10.5, -10.5, 0.0);
			glVertex3f(10.5, -10.5, 0.0);
			glVertex3f(10.5, 10.5, 0.0);
			glVertex3f(-10.5, 10.5, 0.0);
		}
		glEnd();
	}
	break;
	case DISP_WIRE_SPHERE:
	{
		glutWireSphere(0.5, 12, 20);
	}
	break;
	}

	glFlush();
}

void CRndrSample::MyReShape(int nWidth, int nHeight)
{
	glClear(GL_COLOR_BUFFER_BIT); // COLOR BUFFER 초기화
	glViewport(0, 0, 150, 150);
	glBegin(GL_POLYGON); // POLYGON 그리기 모드 셋팅
	{
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	}
	glEnd();
	glFlush();
}