#include "stdafx.h"
#include "resource.h"
#include "WBFCModelSample.h"

#include "..\WBF_LIB\WBFImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GLfloat g_vertices[] =
{
	// 0
	-0.5f, -0.5f, 0.f,	// vertex
	1.f, 0.f, 0.f,		// color
	0.f, 0.f,			// texture

	// 1
	0.5f, -0.5f, 0.f,	// vertex 
	0.f, 1.f, 0.f,		// color
	1.f, 0.f,			// texture

	// 2
	0.5f, 0.5f, 0.f,	// vertex
	0.f, 0.f, 1.f,		// color
	1.f, 1.f,			// texture

	// 3
	-0.5f, 0.5f, 0.f,	// vertex
	0.f, 1.f, 0.f,		// color
	0.f, 1.f,			// texture
};

GLuint g_indexes[] = 
{
	0, 1, 2,
	0, 2, 3,
};

IMPLEMENT_MODEL(CWBFCModelSample, gps::E_GPS_SAMPLE);

CWBFCModelSample::CWBFCModelSample() :
	m_uiVAO(0), m_uiVBO(0), m_uiEBO(0), 
	m_uiTex(0)
{
	CString strExe;

	TCHAR aPath[MAX_PATH + 1] = { 0 };
	auto dwSize = GetModuleFileName(nullptr, aPath, MAX_PATH);
	CString strPath = aPath;
	auto item = strPath.ReverseFind('\\');
	if (item != -1) strExe = strPath.Left(item) + _T("\\");

	m_cstrPNG = strExe + _T("\\Image\\awesomeface.png");
	m_cstrJPG = strExe + _T("\\Image\\container.jpg");
}

CWBFCModelSample::~CWBFCModelSample()
{
}

void CWBFCModelSample::GLInitialData()
{
	if (IsValidModel())
		GLDelete();
}

void CWBFCModelSample::GLCreateVBO()
{
	glGenVertexArrays(1, &m_uiVAO);
	glBindVertexArray(m_uiVAO);
	{
		glGenBuffers(1, &m_uiVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_uiEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indexes), g_indexes, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (void*)(sizeof(GL_FLOAT) * 3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (void*)(sizeof(GL_FLOAT) * 6));
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);

	glGenTextures(1, &m_uiTex);
	glBindTexture(GL_TEXTURE_2D, m_uiTex);
	{
		CWBFImage imgPNG;
		imgPNG.InitialData(m_cstrPNG);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgPNG.GetWidth(), imgPNG.GetHeight(), 0, imgPNG.GetBytes() == WBFIMG_RGBA ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imgPNG.GetBuffer());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CWBFCModelSample::GLAttachData()
{
	int nProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);
	if (!glIsProgram(nProg)) return;
	
	auto ourColor = glGetUniformLocation(nProg, "ourColor");
	glUniform4f(ourColor, 0.5f, 0.5f, 0.5f, 1.f);

	//auto ourTexture = glGetUniformLocation(nProg, "ourTexture");
	//glUniform1i(ourTexture, 0);
}

void CWBFCModelSample::GLBind()
{
	glBindTexture(GL_TEXTURE_2D, m_uiTex);
	glBindVertexArray(m_uiVAO);
}

void CWBFCModelSample::GLDraw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void CWBFCModelSample::GLUnbind()
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CWBFCModelSample::GLDelete()
{
	glDeleteVertexArrays(1, &m_uiVAO); 
	glDeleteBuffers(1, &m_uiEBO);
	glDeleteBuffers(1, &m_uiVBO);

	m_uiVAO = m_uiVBO = m_uiEBO = 0;
}