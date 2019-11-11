#include "stdafx.h"
#include "GroundRenderer.h"
#include "RendererType.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_GLCORE\ShaderDefine.h"
#include "..\WBF_GLCORE\ShaderManager.h"
#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_BASE\ViewBase.h"
#include "..\WBF_DATA\EntityDefine.h"
#include "..\WBF_DATA\ModuleGround.h"

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
	m_uiSize = 0;
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
	}

	m_uiVAO = 0;
	m_uiVBO = 0;
	m_uiSize = 0;
}

void CGroundRenderer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	if (uiFlag != 0)
		return;

	SetGroundData(pHelper);
}

void CGroundRenderer::GLDraw(CViewHelper * pHelper)
{
	if (!glIsVertexArray(m_uiVAO))
		return;

	auto pShaderManager = pHelper->GetShaderManager();
	auto& Shader = pShaderManager->GetAt(E_SHADER_GROUND);
	Shader.GLBind();
	{
		auto pView = (CViewBase*)pHelper->GetView();
		auto glModelViewProjectionMatrix = pView->GetModelViewProjectionMatrix();

		Shader.GLSetMatrix4("matModelViewProjection", glModelViewProjectionMatrix);

		glBindVertexArray(m_uiVAO);
		glDrawArrays(GL_QUADS, 0, m_uiSize);
		glBindVertexArray(0);
	}
	Shader.GLUnbind();
}

void CGroundRenderer::SetGroundData(CViewHelper * pHelper)
{
	auto pDocBase = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDocBase->GetPackage();
	auto pModuleGround = (CModuleGround*)pPackage->GetModule(E_TYPE_GROUND);
	
	auto itrGround = pModuleGround->GetDefaultData();
	if (ITR_IS_VALID(itrGround))
	{
		auto tGround = pModuleGround->GetAtNU(itrGround);

		float aBuffer[12] = {0};
		std::copy(glm::value_ptr(tGround.aPos[0]), glm::value_ptr(tGround.aPos[0]) + 3, &aBuffer[0]);
		std::copy(glm::value_ptr(tGround.aPos[1]), glm::value_ptr(tGround.aPos[1]) + 3, &aBuffer[3]);
		std::copy(glm::value_ptr(tGround.aPos[2]), glm::value_ptr(tGround.aPos[2]) + 3, &aBuffer[6]);
		std::copy(glm::value_ptr(tGround.aPos[3]), glm::value_ptr(tGround.aPos[3]) + 3, &aBuffer[9]);

		glGenVertexArrays(1, &m_uiVAO);
		glGenBuffers(1, &m_uiVBO);

		glBindVertexArray(m_uiVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(aBuffer), aBuffer, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);		

		m_uiSize = 4; // Quard
	}
}
