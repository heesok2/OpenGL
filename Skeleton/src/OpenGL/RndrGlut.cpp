#include "RndrGlut.h"
#include "GLIncludeHeader.h"
#include <cassert>

int CRndrGlut::g_width = 300;
int CRndrGlut::g_height = 300;
int CRndrGlut::g_volumn = 2;
float CRndrGlut::g_view_x = 0;
float CRndrGlut::g_view_y = 0;

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
	glutInitWindowSize(g_width, g_height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("OpenGL Sample Display");
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-g_volumn, g_volumn, -g_volumn, g_volumn, -g_volumn, g_volumn);
	glutDisplayFunc(MyDisplayFunc);
	glutReshapeFunc(MyReshapeFunc);
	glutKeyboardFunc(MyKeyboardFunc);
	glutSpecialFunc(MySpecialFunc);
	glutMouseFunc(MyMouseFunc);
	glutMotionFunc(MyMotionFunc);
	glutPassiveMotionFunc(MyPassiveMotionFunc);
	glutMainLoop();

	return true;
}

void CRndrGlut::MyDisplayFunc()
{
	enum DISP_MODE { DISP_POLYGON, DISP_WIRE_SPHERE, DISP_MOUSE_MOVE, DISP_NUM };

	glClear(GL_COLOR_BUFFER_BIT); // COLOR BUFFER 초기화

	auto eType = DISP_MOUSE_MOVE;
	switch (eType)
	{
	case DISP_POLYGON:
	{
		glBegin(GL_POLYGON); // POLYGON 그리기 모드 셋팅
		{
			glVertex3f(-1.5, -1.5, 0.0);
			glVertex3f(1.5, -1.5, 0.0);
			glVertex3f(1.5, 1.5, 0.0);
			glVertex3f(-1.5, 1.5, 0.0);
		}
		glEnd();
	}
	break;
	case DISP_WIRE_SPHERE:
	{
		glutWireSphere(0.5, 12, 20);
	}
	break;
	case DISP_MOUSE_MOVE:
	{
		glPointSize(3.f);
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
		{
			glVertex3f(g_view_x, g_view_y, 0.);
		}
		glEnd();
		glPointSize(1.f);
	}
	break;
	}

	glFlush();
}

void CRndrGlut::MyReshapeFunc(int width, int height)
{
	auto f_factor_w = (float)width / (float)g_width;
	auto f_factor_h = (float)height / (float)g_height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-g_volumn * f_factor_w, g_volumn * f_factor_w,
		-g_volumn * f_factor_h, g_volumn * f_factor_h,
		-g_volumn, g_volumn);
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
	switch (key)
	{
	case GLUT_KEY_F1:
	{
		exit(0);
	}
	break;
	default:
		break;
	}
}

void CRndrGlut::MyMouseFunc(int button, int status, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
	case GLUT_RIGHT_BUTTON:
	case GLUT_MIDDLE_BUTTON:
	{
		if (status == GLUT_DOWN)
		{
		}
		else if (status == GLUT_UP)
		{
			//exit(0);
		}
	}
	break;
	}
}

void CRndrGlut::MyMotionFunc(int x, int y)
{
	auto width = glutGet(GLUT_WINDOW_WIDTH);
	auto height = glutGet(GLUT_WINDOW_HEIGHT);

	auto f_factor_w = (float)width / (float)g_width;
	auto f_factor_h = (float)height / (float)g_height;
	auto f_facotr_x = (float)g_volumn * 2.f / (float)width;
	auto f_factor_y = (float)g_volumn * 2.f / (float)height;

	g_view_x = (float)x * f_facotr_x - g_volumn; g_view_x *= f_factor_w;
	g_view_y = (float)(height - y) * f_factor_y - g_volumn; g_view_y *= f_factor_h;

	glutPostRedisplay();
}

void CRndrGlut::MyPassiveMotionFunc(int x, int y)
{
	auto width = glutGet(GLUT_WINDOW_WIDTH);
	auto height = glutGet(GLUT_WINDOW_HEIGHT);

	auto f_factor_w = (float)width / (float)g_width;
	auto f_factor_h = (float)height / (float)g_height;
	auto f_facotr_x = (float)g_volumn * 2.f / (float)width;
	auto f_factor_y = (float)g_volumn * 2.f / (float)height;
	
	g_view_x = (float)x * f_facotr_x - g_volumn; g_view_x *= f_factor_w;
	g_view_y = (float)(height - y) * f_factor_y - g_volumn; g_view_y *= f_factor_h;

	glutPostRedisplay();
}
