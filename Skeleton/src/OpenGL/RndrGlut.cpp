#include "RndrGlut.h"
#include "GLIncludeHeader.h"

CRndrGlut::CRndrGlut()
{
}


CRndrGlut::~CRndrGlut()
{
}

bool CRndrGlut::Run()
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
	glutDisplayFunc(MyDisplayFunc);
	glutReshapeFunc(MyReshapeFunc);
	glutKeyboardFunc(MyKeyboardFunc);
	glutSpecialFunc(MySpecialFunc);
	glutMainLoop();

	return true;
}

void CRndrGlut::MyDisplayFunc()
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

void CRndrGlut::MyReshapeFunc(int width, int height)
{
}

void CRndrGlut::MyKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
	{
		exit(0);
	}
	break;
	default:
		break;
	}
}

void CRndrGlut::MySpecialFunc(int key, int x, int y)
{
}