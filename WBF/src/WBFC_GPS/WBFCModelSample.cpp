#include "stdafx.h"
#include "resource.h"
#include "WBFCModelSample.h"

#include "..\WBF_LIB\WBFImage.h"
#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\WBFViewBase.h"
#include "..\WBF_BASE\WBFModelBaseManager.h"


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
	m_uiTexJPG(0), m_uiTexPNG(0), m_bOnlyOne(FALSE)
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

	m_bOnlyOne = FALSE;
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

	glGenTextures(1, &m_uiTexJPG);
	glBindTexture(GL_TEXTURE_2D, m_uiTexJPG);
	{
		CWBFImage imgJPG;
		imgJPG.InitialData(m_cstrJPG);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgJPG.GetWidth(), imgJPG.GetHeight(), 0, imgJPG.GetBytes() == WBFIMG_RGBA ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imgJPG.GetBuffer());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &m_uiTexPNG);
	glBindTexture(GL_TEXTURE_2D, m_uiTexPNG);
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
	///////////////////////////////////////////////////////////////////////////
	// Data 

	auto pDoc = m_pModelMgr->GetDoc();
	auto pView = pDoc->GetActiveView();

	auto pOption = (CWBFGPSOption*)GetOption();

	int nProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);
	if (!glIsProgram(nProg)) return;

	auto ourColor = glGetUniformLocation(nProg, "ourColor");
	glUniform4f(ourColor, 0.8f, 0.8f, 0.8f, 1.f);

	auto ourTexture1 = glGetUniformLocation(nProg, "ourTexture1");
	if(!m_bOnlyOne) glUniform1i(ourTexture1, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ourTexture1);

	auto ourTexture2 = glGetUniformLocation(nProg, "ourTexture2");
	if (!m_bOnlyOne) glUniform1i(ourTexture1, 1); // 최초 한번만 하면 되는 함수
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ourTexture2);

	auto ratio = glGetUniformLocation(nProg, "fRatio");
	glUniform1f(ratio, pOption->fRatio);
	
	///////////////////////////////////////////////////////////////////////////
	// View 

	int aViewPort[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, aViewPort);

	glm::mat4 model(1.f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view(1.f);
	//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
	//view = glm::lookAt(glm::vec3(3.f, 0.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	pView->GetViewMatrix(view);

	glm::mat4 proj(1.f);
	glm::ortho(0.f, 800.f, 0.f, 600.f, 0.1f, 100.f); // left, right, bottom, top, near, far
	proj = glm::perspective(glm::radians(45.f), (float)(aViewPort[2]-aViewPort[0]) / (float)(aViewPort[3]-aViewPort[1]), 0.1f, 100.f);

	auto modelLoc = glGetUniformLocation(nProg, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	auto viewLoc = glGetUniformLocation(nProg, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	auto projLoc = glGetUniformLocation(nProg, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	if (!m_bOnlyOne) m_bOnlyOne = TRUE;
}

void CWBFCModelSample::GLBind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTexJPG);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_uiTexPNG);
	glBindVertexArray(m_uiVAO);
}

void CWBFCModelSample::GLDraw()
{
	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	int nProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);
	if (!glIsProgram(nProg)) return;

	for (auto indx = 0; indx < 10; ++indx)
	{
		auto modelLoc = glGetUniformLocation(nProg, "model");

		glm::mat4 model(1.f);
		float angle = 20.0f * indx;
		model = glm::translate(model, cubePositions[indx]);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
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
	glDeleteTextures(1, &m_uiTexJPG);
	glDeleteTextures(1, &m_uiTexPNG);

	m_uiVAO = m_uiVBO = m_uiEBO = 0;
	m_uiTexJPG = m_uiTexPNG = 0;
}