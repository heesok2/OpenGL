#include "RndrGlut.h"
#include "GLIncludeHeader.h"
#include <cassert>

enum E_MENU_MODE
{
	E_MENU_POLYGON = 1,
	E_MENU_WIRE_SPHERE,
	E_MENU_MOUSE_MOVE,
	E_MENU_IDLE,
	E_MENU_NUM
};

int CRndrGlut::g_menu_mode = E_MENU_IDLE;

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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
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
	glutIdleFunc(MyIdleFunc);

	enum E_SUB_MENU { E_SUB_1 = 1, E_SUB_2 };
	auto subID = glutCreateMenu(MySubMenu);
	glutAddMenuEntry("Sub Menu 1", E_SUB_1);
	glutAddMenuEntry("Sub Menu 2", E_SUB_2);
	auto mainID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Polygon", E_MENU_POLYGON);
	glutAddMenuEntry("Sphere", E_MENU_WIRE_SPHERE);
	glutAddMenuEntry("Mouse move", E_MENU_MOUSE_MOVE);
	glutAddMenuEntry("Idle", E_MENU_IDLE);
	glutAddSubMenu("Sub menu", subID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return true;
}

void CRndrGlut::MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT); // COLOR BUFFER 초기화

	switch (g_menu_mode)
	{
	case E_MENU_POLYGON:
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
	case E_MENU_WIRE_SPHERE:
	{
		glutWireSphere(0.5, 12, 20);
	}
	break;
	case E_MENU_MOUSE_MOVE:
	{
		glPointSize(3.f);
		glBegin(GL_POINTS);
		{
			glVertex3f(g_view_x, g_view_y, 0.);
		}
		glEnd();
		glPointSize(1.f);
	}
	break;
	case E_MENU_IDLE:
	{
		glPointSize(3.f);
		glBegin(GL_POINTS);
		{
			glVertex3f(g_view_x, g_view_y, 0.);
		}
		glEnd();
		glPointSize(1.f);
	}
	break;
	}

	glutSwapBuffers();
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
	switch (g_menu_mode)
	{
	case E_MENU_MOUSE_MOVE:
	{
		auto width = glutGet(GLUT_WINDOW_WIDTH);
		auto height = glutGet(GLUT_WINDOW_HEIGHT);

		auto f_factor_w = (float)width / (float)g_width;
		auto f_factor_h = (float)height / (float)g_height;
		auto f_facotr_x = (float)g_volumn * 2.f / (float)width;
		auto f_factor_y = (float)g_volumn * 2.f / (float)height;

		g_view_x = (float)x * f_facotr_x - g_volumn; g_view_x *= f_factor_w;
		g_view_y = (float)(height - y) * f_factor_y - g_volumn; g_view_y *= f_factor_h;
	}
	break;
	default:
		break;
	}

	glutPostRedisplay();

}

void CRndrGlut::MyPassiveMotionFunc(int x, int y)
{
	switch (g_menu_mode)
	{
	case E_MENU_MOUSE_MOVE:
	{
		auto width = glutGet(GLUT_WINDOW_WIDTH);
		auto height = glutGet(GLUT_WINDOW_HEIGHT);

		auto f_factor_w = (float)width / (float)g_width;
		auto f_factor_h = (float)height / (float)g_height;
		auto f_facotr_x = (float)g_volumn * 2.f / (float)width;
		auto f_factor_y = (float)g_volumn * 2.f / (float)height;

		g_view_x = (float)x * f_facotr_x - g_volumn; g_view_x *= f_factor_w;
		g_view_y = (float)(height - y) * f_factor_y - g_volumn; g_view_y *= f_factor_h;
	}
	break;
	default:
		break;
	}

	glutPostRedisplay();
}

void CRndrGlut::MyMainMenu(int entryID)
{
	g_menu_mode = entryID;
	glutPostRedisplay();
}

void CRndrGlut::MySubMenu(int entryID)
{
	glutPostRedisplay();
}

void CRndrGlut::MyIdleFunc()
{
	static auto f_idle = 0.01f;
	static auto f_idle_x = f_idle;
	static auto f_idle_y = f_idle;

	if (g_view_x < -g_volumn) f_idle_x = f_idle;
	if (g_view_x > g_volumn) f_idle_x = -f_idle;
	if (g_view_y < -g_volumn) f_idle_y = f_idle;
	if (g_view_y > g_volumn) f_idle_y = -f_idle;

	g_view_x += f_idle_x;
	g_view_y += f_idle_y;

	glutPostRedisplay();
}
