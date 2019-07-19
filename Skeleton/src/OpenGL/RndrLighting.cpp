#include "RndrLighting.h"
#include "GlutIncludeHeader.h"

int CRndrLighting::g_win_x = 0;
int CRndrLighting::g_win_y = 0;
int CRndrLighting::g_width = 500;
int CRndrLighting::g_height = 500;

int CRndrLighting::g_volumn = 2;
int CRndrLighting::g_near = 0;
int CRndrLighting::g_far = 2;

int CRndrLighting::g_win_command = 0;
int CRndrLighting::g_angle = 0;


CRndrLighting::CRndrLighting()
{
}

CRndrLighting::~CRndrLighting()
{
}

bool CRndrLighting::Run()
{
	int nArgc = 1;
	glutInit(&nArgc, nullptr);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(g_width, g_height);
	glutInitWindowPosition(g_win_x, g_win_y);
	g_win_command = glutCreateWindow("Lighting");

	DrawInit();
	DrawLighting();

	glutDisplayFunc(MyDisplayFunc);
	glutReshapeFunc(MyReshapeFunc);
	glutTimerFunc(100, MyTimerFunc, 0);
	glutMainLoop();

	return false;
}

void CRndrLighting::DrawInit()
{
	glClearColor(0, 0, 0, 1.); // Opacity Black
}

void CRndrLighting::DrawLighting()
{
	GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };     //���� �ֺ��ݻ�

	GLfloat light0_ambient[] = { 0.5f, 0.4f, 0.3f, 1.0f };     //0�� ���� Ư��
	GLfloat light0_diffuse[] = { 0.5f, 0.4f, 0.3f, 1.0f };
	GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat light1_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };     //1�� ���� Ư��
	GLfloat light1_diffuse[] = { 0.5f, 0.2f, 0.3f, 1.0f };
	GLfloat light1_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat material_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };  //��ü Ư��
	GLfloat material_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat material_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat material_shininess[] = { 25.0f };


	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	// Light Source - ����
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); // �ֺ���
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // Ȯ�걤
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular); // ��鱤

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient); // �ֺ���
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_diffuse); // Ȯ�걤
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_specular); // ��鱤

	// Material - ����
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	// global 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // global ambient - ���� �ֺ���
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // local, ��������
}

void CRndrLighting::MyDisplayFunc()
{
	GLfloat LightPosition0[] = { 0.0, 0.0, 2.0, 1.0 };     //0�� ������ġ
	GLfloat LightPosition1[] = { 1.0, 1.0, 1.0, 1.0 };     //1�� ������ġ
	GLfloat LightDirection1[] = { -0.5, -1.0, -1.0 };       //1�� ���� ����
	GLfloat SpotAngle1[] = { 20.0 };                        //1�� ���� ����

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // buffer clear

	glMatrixMode(GL_MODELVIEW); // model-view matrix
	glLoadIdentity(); // matrix clear 
	gluLookAt(1, 1, 1, 0, 0, -1, 0, 1, 0);
	{
		glPushMatrix();
		{
			glRotatef((GLfloat)g_angle, 1, 0, 0);
			glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0); // ��ġ�� ����
			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.);
			glTranslatef(0, 0, 2.);
			glutSolidSphere(0.1, 10, 10);
		}
		glPopMatrix();
		
		glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1); // ����Ʈ����Ʈ ����
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection1); // ����
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1); // ����
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.); // �ڻ����� �¼�

		glutSolidSphere(1, 200, 200);
	}
	glutSwapBuffers(); // swap buffer
}

void CRndrLighting::MyReshapeFunc(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); // projection matrix 
	glLoadIdentity();
	glOrtho(-g_volumn, g_volumn, -g_volumn, g_volumn, g_near, g_far);
}

void CRndrLighting::MyTimerFunc(int val)
{
	g_angle += 30;
	g_angle = g_angle % 360;

	glutPostRedisplay();
	
	glutTimerFunc(100, MyTimerFunc, 0);
}
