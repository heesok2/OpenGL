#include "stdafx.h"
#include "LightRenderer.h"
#include "RendererType.h"
#include "GeometryBuffer.h"
#include "BufferType.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_GLCORE\ShaderDefine.h"
#include "..\WBF_GLCORE\ObjectBufferManager.h"
#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_BASE\ViewBase.h"
#include "..\WBF_DATA\ModuleLight.h"
#include "..\WBF_DATA\ModuleBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_RENDERER(CLightRenderer, E_RENDERER_LIGHT);

CLightRenderer::CLightRenderer()
{
	m_aData.clear();
}

CLightRenderer::~CLightRenderer()
{
}

void CLightRenderer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	if (uiFlag != 0)
		return;

	SetLightData(pHelper);
}

void CLightRenderer::GLDraw(CViewHelper * pHelper)
{
	if (m_aData.empty()) return;

	auto pShaderManager = pHelper->GetShaderManager();
	auto& Shader = pShaderManager->GetAt(E_SHADER_LIGHT);
	Shader.GLBind();
	{
		int nProg;
		glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);

		auto pView = (CViewBase*)pHelper->GetView();
		auto aEyePos = pView->GetEyePosition();
		glm::vec3 glLightColor(1.f, 1.f, 1.f);
		glm::vec3 glModelColor(0.8f, 0.8f, 0.8f);
		auto glModelViewProjectionMatrix = pView->GetModelViewProjectionMatrix();

		for (auto& tData : m_aData)
		{
			auto glAllMatrix = glModelViewProjectionMatrix * tData.glModelMatrix;

			Shader.GLSetMatrix4("matModelViewProjection", glAllMatrix);

			glBindVertexArray(tData.uiVAO);
			glDrawElements(GL_TRIANGLES, tData.uiSize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	Shader.GLUnbind();
}

void CLightRenderer::SetLightData(CViewHelper * pHelper)
{
	auto pDocBase = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDocBase->GetPackage();
	auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);

	auto pObjectBufferManager = pHelper->GetObjectBufferManager();
	auto pGeomBuffer = pObjectBufferManager->LookUp(E_BUFFER_GEOMETRY);

	std::map<UINT, TObjectBuffer> mObjectBuffer;
	auto szObjectBufferNum = pGeomBuffer->GetObjectBuffer(mObjectBuffer);
	if (szObjectBufferNum == 0) 
		return;

	auto itrLight = pModuleLight->GetDefaultData();
	if (ITR_IS_VALID(itrLight))
	{
		auto tLight = pModuleLight->GetAtNU(itrLight);
		auto BodyKey = ITR_TO_KEY(tLight.itrBody);

		auto itrFind = mObjectBuffer.find(BodyKey);
		if (itrFind == mObjectBuffer.end())
			return;

		glm::mat4 ModelMatrix(1.f);
		ModelMatrix = glm::translate(ModelMatrix, tLight.vPos);
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f));

		TLight tData;

		tData.uiVAO = itrFind->second.uiVAO;
		tData.uiSize = itrFind->second.uiSize;
		tData.glModelMatrix = ModelMatrix;

		m_aData.push_back(std::move(tData));
	}
}