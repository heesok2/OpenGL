#include "RndrTexture.h"
#include "GlutIncludeHeader.h"

int CRndrTexture::g_x = 0;
int CRndrTexture::g_y = 0;
int CRndrTexture::g_width = 500;
int CRndrTexture::g_height = 500;
int CRndrTexture::g_volumn = 5;
int CRndrTexture::g_near = 0;
int CRndrTexture::g_far = 5;

int CRndrTexture::g_win_command = 0;
int CRndrTexture::g_angle = 30;

#define TEX_WIDTH 4
#define TEX_HEIGHT 4
unsigned char g_texture_2d[TEX_WIDTH][TEX_HEIGHT][4] = { 0 };

CRndrTexture::CRndrTexture()
{
}

CRndrTexture::~CRndrTexture()
{
}

bool CRndrTexture::Run()
{
	int nArgc = 1;
	glutInit(&nArgc, nullptr);
	glutInitWindowSize(g_width, g_height);
	glutInitWindowPosition(g_x, g_y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	g_win_command = glutCreateWindow("Texture");

	DrawInit();
	//DrawLighting();

	glutDisplayFunc(MyDisplayFunc);
	glutReshapeFunc(MyReshapeFunc);
	glutMainLoop();

	return true;
}

void CRndrTexture::DrawInit()
{
	for (auto s = 0; s < TEX_WIDTH; ++s)
	{
		for (auto t = 0; t < TEX_HEIGHT; ++t)
		{
			GLubyte color = ((s + t) % 2) * 255;
			g_texture_2d[s][t][0] = color;
			g_texture_2d[s][t][1] = color;
			g_texture_2d[s][t][2] = color;
			g_texture_2d[s][t][3] = 255;
		}
	}

	glClearColor(0, 0, 0, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, TEX_WIDTH, TEX_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &g_texture_2d[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
}

void CRndrTexture::DrawLighting()
{
	GLfloat global_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };     //전역 주변반사

	GLfloat light0_ambient[] = { 0.5f, 0.4f, 0.3f, 1.0f };     //0번 광원 특성
	GLfloat light0_diffuse[] = { 0.5f, 0.4f, 0.3f, 1.0f };
	GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat light1_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };     //1번 광원 특성
	GLfloat light1_diffuse[] = { 0.5f, 0.2f, 0.3f, 1.0f };
	GLfloat light1_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat material_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };  //물체 특성
	GLfloat material_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat material_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat material_shininess[] = { 25.0f };

	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	
	// global 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // global ambient - 광역 주변광
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // local, 근접시점
}

void CRndrTexture::MyDisplayFunc()
{
	GLfloat LightPosition0[] = { 2.0, 2.0, 2.0, 1.0 };     //0번 광원위치
	GLfloat LightPosition1[] = { 1.0, 1.0, 1.0, 1.0 };     //1번 광원위치
	GLfloat LightDirection1[] = { -0.5, -1.0, -1.0 };      //1번 광원 방향
	GLfloat SpotAngle1[] = { 20.0 };                       //1번 광원 각도

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0, 0, g_volumn, 0, 0, -1, 0, 1, 0);

	//{
	//	glPushMatrix();
	//	{
	//		//glRotatef(g_angle, 0, 1, 1);
	//		//glTranslatef(1, 0, 0);
	//		glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
	//		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
	//		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.);
	//		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.);
	//	}
	//	glPopMatrix();

	//	glColor3f(0.2f, 0.2f, 0.2f);
	//	glutSolidSphere(2, 200, 200);
	//}

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(0.0, 3.0); glVertex3f(-1.0, 1.0, 0.0);
		glTexCoord2f(3.0, 3.0); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(3.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
	}
	glEnd();

	glutSwapBuffers();
}

void CRndrTexture::MyReshapeFunc(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-g_volumn, g_volumn, -g_volumn, g_volumn, g_near, g_far);
}