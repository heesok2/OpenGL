#include "RndrProjection.h"
#include "GLIncludeHeader.h"
#include <cassert>

enum E_MENU_MODE
{
	E_MENU_VIEWPORT = 1,
	E_MENU_NUM
};

int CRndrProjection::g_menu_mode = E_MENU_VIEWPORT;

int CRndrProjection::g_width = 400;
int CRndrProjection::g_height = 400;
int CRndrProjection::g_volumn = 2;
int CRndrProjection::g_near = 0;
int CRndrProjection::g_far = 5;
int CRndrProjection::g_angle = 0;

CRndrProjection::CRndrProjection()
{
}

CRndrProjection::~CRndrProjection()
{
}

bool CRndrProjection::Run()
{
	int nArgc = 1;
	glutInit(&nArgc, nullptr);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(g_width, g_height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("OpenGL Sample Display");

	DrawInit();

	glutDisplayFunc(MyDisplayFunc);
	glutTimerFunc(100, MyTimeFunc, 0);
	glutMainLoop();

	return true;
}

void CRndrProjection::MyDisplayFunc()
{
	glEnable(GL_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Color Buffer & Depth Buffer √ ±‚»≠
	
	switch (g_menu_mode)
	{
	case E_MENU_VIEWPORT:
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glViewport(0, 0, g_width*0.5, g_height*0.5);
			glPushMatrix();
			{
				gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
				glRotatef(g_angle, 0, 1, 0);
				DrawCoodinate();
				DrawScene();
			}
			glPopMatrix();

			glViewport(g_width*0.5, 0, g_width*0.5, g_height*0.5);
			glPushMatrix();
			{
				gluLookAt(0, 0, 0, -1, 0, 0, 0, 1, 0);
				glRotatef(g_angle, 0, 1, 0);
				DrawCoodinate();
				DrawScene();
			}
			glPopMatrix();

			glViewport(g_width*0.5, g_height*0.5, g_width*0.5, g_height*0.5);
			glPushMatrix();
			{
				gluLookAt(0, 0, 0, 0, -1, 0, 0, 0, 1);
				glRotatef(g_angle, 0, 1, 0);
				DrawCoodinate();
				DrawScene();
			}
			glPopMatrix();

			glViewport(0, g_height*0.5, g_width*0.5, g_height*0.5);
			glPushMatrix();
			{
				gluLookAt(0, 0, 0, 0, 1, 0, 0, 0, 1);
				glRotatef(g_angle, 0, 1, 0);
				DrawCoodinate();
				DrawScene();
			}
			glPopMatrix();

		}
		break;
	default:
		break;
	}

	glutSwapBuffers();
}

void CRndrProjection::MyTimeFunc(int value)
{
	g_angle += 10;
	g_angle = g_angle % 360;

	glutTimerFunc(100, MyTimeFunc, 0);
	glutPostRedisplay();
}

void CRndrProjection::DrawInit()
{
	glClearColor(0, 0, 0, 1);

	// view volumn
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-g_volumn, g_volumn, -g_volumn, g_volumn, g_near, g_far);
	gluPerspective(100, 1, g_near, g_far);
	// model-view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CRndrProjection::DrawScene()
{
	glColor3f(0.5, 0.5, 0.5);
	glutWireTeapot(1);
}

void CRndrProjection::DrawCoodinate()
{
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, 1, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, -1);
		glVertex3f(0, 0, 1);
	}
	glEnd();
}