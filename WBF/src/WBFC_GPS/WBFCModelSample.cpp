#include "stdafx.h"
#include "resource.h"
#include "WBFCModelSample.h"

#include "..\WBF_GPS\WBFImage.h"

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

	CString strFilePath;
	{
		TCHAR aPath[MAX_PATH + 1] = { 0 };
		auto dwSize = GetModuleFileName(nullptr, aPath, MAX_PATH);
		CString strPath = aPath;
		auto item = strPath.ReverseFind('\\');
		if (item != -1)
		{
			strFilePath = strPath.Left(item);
			strFilePath += _T("\\Image\\awesomeface.png");
		}
	}

	CWBFImage img;
	img.InitialData(strFilePath);


	//glGenTextures(1, &m_uiTex);
	//glBindTexture(GL_TEXTURE_2D, m_uiTex);
	//{
	//	CWBFImage img;
	//	img.InitialData(_T("WBFC_GPS"), _T("PNG"), IDB_PNG1);

	//	TCHAR aPath[MAX_PATH + 1] = { 0 };
	//	auto dwSize = GetModuleFileName(nullptr, aPath, MAX_PATH);
	//	GetCurrentDirectory(MAX_PATH, aPath);

	//	CImage img;
	//	auto hRes = img.LoadFromResource(((_T("Image\\awesomeface.png"));
	//	int width = img.GetWidth();
	//	int height = img.GetHeight();
	//	int nrChannels = img.GetBPP() / 4;
	//	void* data = img.GetBits();

	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void CWBFCModelSample::GLAttachData()
{
	int nProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);
	if (!glIsProgram(nProg)) return;
	
	auto ourColor = glGetUniformLocation(nProg, "ourColor");
	glUniform4f(ourColor, 0.5f, 0.5f, 0.5f, 1.f);

	//auto ourTexture = glGetUniformLocation(nProg, "ourTexture");
	//glUniform1i(ourTexture);
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