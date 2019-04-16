#include "RndrModeling.h"
#include "GLIncludeHeader.h"
#include <cassert>

enum E_MENU_MODE
{
	E_MENU_MATRIX = 1,
	E_MENU_SOLAR_SYS,
	E_MENU_NUM
};

int CRndrModeling::g_menu_mode = E_MENU_SOLAR_SYS;

int CRndrModeling::g_width = 300;
int CRndrModeling::g_height = 300;
int CRndrModeling::g_volumn = 30;

int CRndrModeling::g_hour = 0;
int CRndrModeling::g_day = 0;
int CRndrModeling::g_month = 0;

CRndrModeling::CRndrModeling()
{
}

CRndrModeling::~CRndrModeling()
{
}

bool CRndrModeling::Run()
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
	glutKeyboardFunc(MyKeyboardFunc);
	glutMainLoop();

	return true;
}

void CRndrModeling::MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT); // COLOR BUFFER √ ±‚»≠

	switch (g_menu_mode)
	{
	case E_MENU_MATRIX:
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1.f, 0.f, 0.f);
		glPointSize(3.f);
		glBegin(GL_POINTS);
		{
			glVertex3f(0.f, 0.f, 0.f);
		}
		glEnd();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(0.f, 1.f, 0.f);
		glRotatef(45.f, 1.f, 1.f, 1.f);
		glTranslatef(0.6f, 0.f, 0.f);
		{
			glutSolidCube(0.3);
		}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(0.f, 0.f, 1.f);
		glTranslatef(0.6f, 0.f, 0.f);
		glRotatef(45.f, 1.f, 1.f, 1.f);
		{
			glutSolidCube(0.3);
		}
	}
	break;
	case E_MENU_SOLAR_SYS:
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glutWireSphere(5, 10, 2);

		glPushMatrix();
		{
			auto f_earth = ((float)g_month + (float)g_day/30) / 12.f * 360.f;
			glRotatef(f_earth, 0, 0, 1);

			glTranslatef(20, 0, 0);
			glutWireSphere(2, 10, 2);

			glPushMatrix();
			{
				auto f_moon = (float)g_hour / 24.f * 360.f;
				glRotatef(f_moon, 0, 0, 1);

				glTranslatef(8, 0, 0);
				glutWireSphere(1, 10, 2);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	break;
	default:
		break;
	}

	glutSwapBuffers();
}

void CRndrModeling::MyKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'h':
	case 'H':
	{
		g_hour += 2;
	}
	break;
	case 'd':
	case 'D':
	{
		g_day += 2;
	}
	break;
	case 'm':
	case 'M':
	{
		g_month += 1;
	}
	default:
		break;
	}

	g_day += g_hour / 24;
	g_hour = g_hour % 24;

	g_month += g_day / 30;
	g_day = g_day % 30;

	g_month = g_month % 12;

	glutPostRedisplay();
}
