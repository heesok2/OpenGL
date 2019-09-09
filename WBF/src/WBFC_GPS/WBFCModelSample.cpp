#include "stdafx.h"
#include "WBFCModelSample.h"

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

CWBFCModelSample::CWBFCModelSample()
	: m_uiVAO(0), m_uiVBO(0), m_uiEBO(0)
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
	}

	glBindVertexArray(0);
}

void CWBFCModelSample::GLBind()
{
	glBindVertexArray(m_uiVAO);
}

void CWBFCModelSample::GLDraw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void CWBFCModelSample::GLUnbind()
{
	glBindVertexArray(0);
}

void CWBFCModelSample::GLDelete()
{
	glDeleteVertexArrays(1, &m_uiVAO); 
	glDeleteBuffers(1, &m_uiEBO);
	glDeleteBuffers(1, &m_uiVBO);

	m_uiVAO = m_uiVBO = m_uiEBO = 0;
}