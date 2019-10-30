#include "stdafx.h"
#include "ContainerBoxRenderer.h"
#include "RendererType.h"
#include "BufferType.h"
#include "GeometryBuffer.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_BASE\ViewBase.h"
#include "..\WBF_DATA\ModuleBody.h"
#include "..\WBF_DATA\ModuleBox.h"
#include "..\WBF_DATA\ModuleLight.h"
#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_GLCORE\ShaderDefine.h"
#include "..\WBF_GLCORE\ObjectBufferManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_RENDERER(CContainerBoxRenderer, E_RENDERER_CONTAINER_BOX);

CContainerBoxRenderer::CContainerBoxRenderer()
{
}


CContainerBoxRenderer::~CContainerBoxRenderer()
{
}

void CContainerBoxRenderer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	m_aData.clear();

	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleBox = (CModuleBox*)pPackage->GetModule(E_TYPE_BOX);
	auto pModuleBody = (CModuleBody*)pPackage->GetModule(E_TYPE_BODY);
	auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);

	auto pView = (CViewBase*)pHelper->GetView();
	auto pObjectBufferManager = pHelper->GetObjectBufferManager();
	auto pGeomBuffer = pObjectBufferManager->LookUp(E_BUFFER_GEOMETRY);

	std::map<UINT, TObjectBuffer> mObjectBuffer;
	auto szObjectBufferNum = pGeomBuffer->GetObjectBuffer(mObjectBuffer);
	if (szObjectBufferNum == 0) return;

	auto itrLight = pModuleLight->GetDefaultLight();
	if (!ITR_IS_VALID(itrLight)) return;

	auto tLight = pModuleLight->GetAtNU(itrLight);

	auto LightPos = tLight.vPos;
	auto EyePos = pView->GetEyePosition();
	glm::vec3 glLightColor(1.f, 1.f, 1.f);
	glm::vec3 glModelColor(0.8f, 0.8f, 0.8f);
	auto glModelViewProjectionMatrix = pView->GetModelViewProjectionMatrix();

	std::vector<DITER> aItrBox;
	auto szBoxNum = pModuleBox->GetIterList(aItrBox);
	for (auto indx = 0; indx < szBoxNum; ++indx)
	{
		auto& tContainer = pModuleBox->GetAtNU(aItrBox[indx]);
		auto BodyKey = ITR_TO_KEY(tContainer.itrBody);

		auto itrFind = mObjectBuffer.find(BodyKey);
		if (itrFind == mObjectBuffer.end()) continue;

		TContainerBox tData;
		
		glm::mat4 ModelMatrix(1.f);
		ModelMatrix = glm::translate(ModelMatrix, tContainer.vPos);
		tData.glModelMatrix = ModelMatrix;
		tData.glModelViewProjectionMatrix = glModelViewProjectionMatrix * ModelMatrix;
		tData.EyePos = EyePos;
		tData.LightPos = LightPos;
		tData.glModelColor = glModelColor;
		tData.glLightColor = glLightColor;
		tData.uiVAO = itrFind->second.uiVAO;
		tData.uiSize = itrFind->second.uiSize;

		m_aData.push_back(std::move(tData));
	}
}

void CContainerBoxRenderer::GLDraw(CViewHelper * pHelper)
{
	if (m_aData.empty()) return;

	auto pShaderManager = pHelper->GetShaderManager();
	auto& Shader = pShaderManager->GetShader(E_SHADER_CONTAINER_BOX);
	Shader.GLBind();
	{
		for (auto& tData : m_aData)
		{
			Shader.GLSetMatrix4("matModel", tData.glModelMatrix);
			Shader.GLSetMatrix4("matModelViewProjection", tData.glModelViewProjectionMatrix);

			Shader.GLSetVector3("aEyePos", tData.EyePos);
			Shader.GLSetVector3("aLightPos", tData.LightPos);
			Shader.GLSetVector3("aModelColor", tData.glModelColor);
			Shader.GLSetVector3("aLightColor", tData.glLightColor);

			glBindVertexArray(tData.uiVAO);
			glDrawElements(GL_TRIANGLES, tData.uiSize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	Shader.GLUnbind();
}
