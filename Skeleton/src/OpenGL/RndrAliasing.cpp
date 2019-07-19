#include "RndrAliasing.h"
#include "GlutIncludeHeader.h"

GLint g_margin = 16;
GLint g_mini_w_h = 128;
GLint g_world_w_h = 512;

GLint g_win_command = 0;
GLint g_win_mini_map = 0;
GLint g_win_world_map = 0;

GLint g_index = 0;
GLboolean g_blend = false;
GLboolean g_smooth = false;

enum E_MENU_MODE
{
	E_MENU_VIEWPORT = 1,
	E_MENU_NUM
};

int CRndrAliasing::g_menu_mode = E_MENU_VIEWPORT;

int CRndrAliasing::g_win_x = 0;
int CRndrAliasing::g_win_y = 0;
int CRndrAliasing::g_width = g_margin + g_mini_w_h + g_margin + g_world_w_h + g_margin;
int CRndrAliasing::g_height = g_margin + g_mini_w_h + g_margin + g_world_w_h + g_margin;
int CRndrAliasing::g_volumn = 2;
int CRndrAliasing::g_near = 0;
int CRndrAliasing::g_far = 5;
int CRndrAliasing::g_angle = 0;

unsigned char PALETTE[16][3] = {
	{ 255, 255, 255 },      // WHITE
	{   0, 255, 255 },      // CYAN
	{ 255,   0, 255 },      // PURPLE
	{   0,   0, 255 },      // BLUE
	{ 192, 192, 192 },      // LIGHT GRAY
	{ 128, 128, 128 },      // DARK GRAY
	{   0, 128, 128 },      // DARK TEAL
	{ 128,   0, 128 },      // DARK PURPLE
	{   0,   0, 128 },      // DARK BLUE
	{ 255, 255,   0 },      // YELLOW
	{   0, 255,   0 },      // GREEN
	{ 128, 128,   0 },      // DARK YELLOW
	{   0, 128,   0 },      // DARK GREEN
	{ 255,   0,   0 },      // RED
	{ 128,   0,   0 },      // DARK RED
	{   0,   0,   0 },      // BLACK
};

CRndrAliasing::CRndrAliasing()
{
}

CRndrAliasing::~CRndrAliasing()
{
}

bool CRndrAliasing::Run()
{
	int nArgc = 1;
	glutInit(&nArgc, nullptr);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(g_width, g_height);
	glutInitWindowPosition(g_win_x, g_win_y);
	g_win_command = glutCreateWindow("Anti-Aliasing"); // Main Window
	glutDisplayFunc(MyDisplayFunc); // Display Callback

	g_win_mini_map = glutCreateSubWindow(g_win_command, g_margin, g_margin, g_mini_w_h, g_mini_w_h); // Sub Screen Window
	glutDisplayFunc(MyMiniDisplayFunc); // Display Callback

	g_win_world_map = glutCreateSubWindow(g_win_command, g_margin + g_mini_w_h + g_margin, g_margin, g_world_w_h, g_world_w_h); // Sub World Window
	glutDisplayFunc(MyWorldDisplayFunc); // Display Callback

	glutKeyboardFunc(MyKeyboardFunc); // Keyboard Callback
	glutTimerFunc(100, MyTimerFunc, 0); // Timer Callback

	glutMainLoop();

	return true;
}

void CRndrAliasing::DrawInit()
{
	glClearColor(0, 0, 0, 1); // clear color code - opacity black 
}

void CRndrAliasing::DrawRedisplay()
{
	glutSetWindow(g_win_mini_map);
	glutPostRedisplay();

	glutSetWindow(g_win_world_map);
	glutPostRedisplay();
}

void CRndrAliasing::MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // buffer 초기화
	glLoadIdentity(); // matrix 초기화 
	{
		// unknown 
	}
	glutSwapBuffers();
}

void CRndrAliasing::MyMiniDisplayFunc()
{
	GLfloat Red = PALETTE[g_index][0] / 255.0f;
	GLfloat Green = PALETTE[g_index][1] / 255.0f;
	GLfloat Blue = PALETTE[g_index][2] / 255.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // buffer 초기화
	glLoadIdentity(); // matrix 초기화

	if (g_blend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (g_smooth)
	{
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}

	glPushMatrix();
	{
		GLfloat f_angle = (GLfloat)g_index / 16. * 360.;
		glRotatef(f_angle, 0, 1, 0);

		glColor3f(Red, Green, Blue);
		glBegin(GL_LINES);
		{
			glVertex3f(-1.0, 1.0, 0.0);
			glVertex3f(1.0, -1.0, 0.0);
			glVertex3f(-1.0, -1.0, 0.0);
			glVertex3f(1.0, 1.0, 0.0);
		}
		glEnd();
	}
	glPushMatrix();

	if (g_blend)
		glDisable(GL_BLEND);

	if (g_smooth)
		glDisable(GL_LINE_SMOOTH);

	glutSwapBuffers();
}

void CRndrAliasing::MyWorldDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // buffer 초기화
	glLoadIdentity(); // matrix 초기화
	{
		unsigned char* pBuffer = new unsigned char[g_mini_w_h * g_mini_w_h * 4 * 2];
		glutSetWindow(g_win_mini_map);
		glReadPixels(0, 0, g_mini_w_h, g_mini_w_h, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);

		glutSetWindow(g_win_world_map);
		glPixelZoom(4., 4.);
		glDrawPixels(g_mini_w_h, g_mini_w_h, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
		glPixelZoom(0., 0.);
		delete[] pBuffer;
	}
	glutSwapBuffers();
}

void CRndrAliasing::MyKeyboardFunc(unsigned char ch, int x, int y)
{
	if (ch == 'b' || ch == 'B')
	{
		g_blend = !g_blend;
	}
	else if (ch == 's' || ch == 'S')
	{
		g_smooth = !g_smooth;
	}
}

void CRndrAliasing::MyTimerFunc(int value)
{
	g_index++;
	g_index %= 16;

	DrawRedisplay();

	glutTimerFunc(100, MyTimerFunc, 0);
}
