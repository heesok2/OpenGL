#include "stdafx.h"
#include "GroundRenderer.h"
#include "RendererType.h"

#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_GLCORE\ShaderDefine.h"
#include "..\WBF_GLCORE\ShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_RENDERER(CGroundRenderer, E_RENDERER_GROUND);

CGroundRenderer::CGroundRenderer()
{
	m_uiVAO = 0;
	m_uiVBO = 0;
	m_uiEBO = 0;

	m_tData.uiVAO = 0;
	m_tData.uiSize = 0;
}

CGroundRenderer::~CGroundRenderer()
{
}

void CGroundRenderer::GLRelease()
{
	if (glIsVertexArray(m_uiVAO))
	{
		glDeleteVertexArrays(1, &m_uiVAO);
		glDeleteBuffers(1, &m_uiVBO);
		glDeleteBuffers(1, &m_uiEBO);
	}

	m_uiVAO = 0;
	m_uiVBO = 0;
	m_uiEBO = 0;

	m_tData.uiVAO = 0;
	m_tData.uiSize = 0;
}

void CGroundRenderer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	//float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
 //  // positions   // texCoords
 //  -1.0f,  1.0f,  0.0f, 1.0f,
 //  -1.0f, -1.0f,  0.0f, 0.0f,
	//1.0f, -1.0f,  1.0f, 0.0f,

 //  -1.0f,  1.0f,  0.0f, 1.0f,
	//1.0f, -1.0f,  1.0f, 0.0f,
	//1.0f,  1.0f,  1.0f, 1.0f
	//};

	//auto pShaderManager = pHelper->GetShaderManager();
	//auto& Shader = pShaderManager->GetAt(E_SHADER_GROUND);

	//glGenVertexArrays(1, &m_uiVAO);
	//glGenBuffers(1, &m_uiVBO);

	//glBindVertexArray(m_uiVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	//{
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
	//	glEnableVertexAttribArray(1);
	//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	//	ShaderScreen.GLSetInt("ScreenTex2D", 0);
	//}
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CGroundRenderer::GLDraw(CViewHelper * pHelper)
{
	if (!glIsVertexArray(m_tData.uiVAO))
		return;

	auto pShaderManager = pHelper->GetShaderManager();
	auto& Shader = pShaderManager->GetAt(E_SHADER_GROUND);
	Shader.GLBind();
	{
		glBindVertexArray(m_tData.uiVAO);
		glDrawArrays(GL_QUADS, 0, m_tData.uiSize);
		glBindVertexArray(0);
	}
	Shader.GLUnbind();
}
