#include "RndrGlut.h"
#include "GlutIncludeHeader.h"
#include <cassert>

enum E_MENU_MODE
{
	E_MENU_POLYGON = 1,
	E_MENU_WIRE_SPHERE,
	E_MENU_MOUSE_MOVE,
	E_MENU_IDLE,
	E_MENU_TIME,
	E_MENU_MODEL,
	E_MENU_DISP_LIST,
	E_MENU_NUM
};

int CRndrGlut::g_menu_mode = E_MENU_POLYGON;

int CRndrGlut::g_width = 300;
int CRndrGlut::g_height = 300;
int CRndrGlut::g_volumn = 2;

float CRndrGlut::g_view_x = 0;
float CRndrGlut::g_view_y = 0;

int CRndrGlut::g_disp_id = 0;

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
	// glutIdleFunc(MyIdleFunc); // [임시] ldle callback 으로 인해 막아두었음
	// glutTimerFunc(40, MyTimeFunc, 1); // [임시] time callback 으로 인해 막아두었음

	enum E_SUB_MENU { E_SUB_1 = 1, E_SUB_2 };
	auto subID = glutCreateMenu(MySubMenu);
	glutAddMenuEntry("Sub Menu 1", E_SUB_1);
	glutAddMenuEntry("Sub Menu 2", E_SUB_2);
	auto mainID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Polygon", E_MENU_POLYGON);
	glutAddMenuEntry("Sphere", E_MENU_WIRE_SPHERE);
	glutAddMenuEntry("Mouse move", E_MENU_MOUSE_MOVE);
	glutAddMenuEntry("Idle", E_MENU_IDLE);
	glutAddMenuEntry("Time", E_MENU_TIME);
	glutAddMenuEntry("Model", E_MENU_MODEL);
	glutAddMenuEntry("Display List", E_MENU_DISP_LIST);
	glutAddSubMenu("Sub menu", subID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	MyDispList(); // Display List 

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
	case E_MENU_TIME:
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
	case E_MENU_MODEL:
	{
		GLfloat arrVec[][3] =
		{
			{-0.25f, -0.25f,  0.25f},
			{-0.25f,  0.25f,  0.25f},
			{ 0.25f,  0.25f,  0.25f},
			{ 0.25f, -0.25f,  0.25f},
			{-0.25f, -0.25f, -0.25f},
			{-0.25f,  0.25f, -0.25f},
			{ 0.25f,  0.25f, -0.25f},
			{ 0.25f, -0.25f, -0.25f}
		};

		GLfloat arrCol[][3] =
		{
			{0.2f, 0.2f, 0.2f},
			{1.0f, 0.0f, 0.0f},
			{1.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 1.0f},
			{0.0f, 1.0f, 1.0f}
		};

		GLubyte arrIndx[] =
		{
			0, 3, 2, 1,
			2, 3, 7, 6,
			0, 4, 7, 3,
			1, 2, 6, 5,
			4, 5, 6, 7,
			0, 1, 5, 4
		};

		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, arrCol);
		glVertexPointer(3, GL_FLOAT, 0, arrVec);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(30.f, 1.f, 1.f, 1.f);

		for(auto indx=0; indx<6; ++indx)
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &arrIndx[4 * indx]);	

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_CULL_FACE);
	}
	break;
	case E_MENU_DISP_LIST:
	{
		glRotatef(30., 1., 1., 1.);
		glCallList(g_disp_id);
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

void CRndrGlut::MyTimeFunc(int value)
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

	if (value < 20)
		glutTimerFunc(40, MyTimeFunc, value + 1);

	glutPostRedisplay();
}

void CRndrGlut::MyDispList()
{
	g_disp_id = glGenLists(1);

	glNewList(g_disp_id, GL_COMPILE);
	glBegin(GL_POLYGON);
	{
		//glColor3f(0.5, 0.5, 0.5);
		glColor3f(1, 0, 0);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	}
	glEnd();
	glEndList();
}
