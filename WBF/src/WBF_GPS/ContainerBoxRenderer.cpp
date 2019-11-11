#include "stdafx.h"
#include "ContainerBoxRenderer.h"
#include "RendererType.h"
#include "BufferType.h"
#include "GeometryBuffer.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_LIB\ImageLoader.h"
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
	m_uiSmaileTex2D = 0;
	m_uiContainerTex2D = 0;
	m_aLightPos = glm::vec3(0);
	m_aData.clear();
}

CContainerBoxRenderer::~CContainerBoxRenderer()
{
}

void CContainerBoxRenderer::GLRelease()
{
	if(glIsTexture(m_uiSmaileTex2D))
		glDeleteTextures(1, &m_uiSmaileTex2D);
	if(glIsTexture(m_uiContainerTex2D))
		glDeleteTextures(1, &m_uiContainerTex2D);

	m_uiSmaileTex2D = 0;
	m_uiContainerTex2D = 0;
	m_aLightPos = glm::vec3(0);
	m_aData.clear();
}

void CContainerBoxRenderer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	if(uiFlag == 0)
	{
		SetLightData(pHelper);

		SetContainerData(pHelper);

		GLSetContainerTexture(pHelper);
	}
}

void CContainerBoxRenderer::GLDraw(CViewHelper * pHelper)
{
	if (m_aData.empty())
		return;
	
	auto pShaderManager = pHelper->GetShaderManager();
	auto& Shader = pShaderManager->GetAt(E_SHADER_CONTAINER_BOX);
	Shader.GLBind();
	{
		auto pView = (CViewBase*)pHelper->GetView();
		auto matViewMatrix = pView->GetViewMatrix();
		auto matProjectionMatrix = pView->GetProjectionMatrix();

		glm::vec3 aLightPos = glm::vec3(matViewMatrix * glm::vec4(m_aLightPos, 1.f));
		glm::vec3 aLightColor(1.f, 1.f, 1.f);

		for (auto& tData : m_aData)
		{
			glm::mat4 matNormalMatrix = glm::transpose(glm::inverse(matViewMatrix * tData.matModelMatrix));

			Shader.GLSetMatrix4("tMatrix.matModel", tData.matModelMatrix);
			Shader.GLSetMatrix4("tMatrix.matView", matViewMatrix);
			Shader.GLSetMatrix4("tMatrix.matProjection", matProjectionMatrix);
			Shader.GLSetMatrix4("tMatrix.matNormal", matNormalMatrix);
			Shader.GLSetVector3("tLight.aLightPos", aLightPos);
			Shader.GLSetVector3("tLight.aLightColor", aLightColor);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_uiContainerTex2D);

			glBindVertexArray(tData.uiVAO);
			glDrawElements(GL_TRIANGLES, tData.uiSize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	Shader.GLUnbind();
}

void CContainerBoxRenderer::SetLightData(CViewHelper * pHelper)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();

	auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);
	auto itrLight = pModuleLight->GetDefaultData();
	if (!ITR_IS_VALID(itrLight)) return;

	auto tLight = pModuleLight->GetAtNU(itrLight);
	m_aLightPos = tLight.vPos;
}

void CContainerBoxRenderer::SetContainerData(CViewHelper * pHelper)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleBox = (CModuleBox*)pPackage->GetModule(E_TYPE_BOX);

	auto pView = (CViewBase*)pHelper->GetView();
	auto pObjectBufferManager = pHelper->GetObjectBufferManager();
	auto pGeomBuffer = pObjectBufferManager->LookUp(E_BUFFER_GEOMETRY);

	std::map<UINT, TObjectBuffer> mObjectBuffer;
	auto szObjectBufferNum = pGeomBuffer->GetObjectBuffer(mObjectBuffer);
	if (szObjectBufferNum == 0) return;

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
		tData.uiVAO = itrFind->second.uiVAO;
		tData.uiSize = itrFind->second.uiSize;
		tData.matModelMatrix = ModelMatrix;

		m_aData.push_back(std::move(tData));
	}
}

void CContainerBoxRenderer::GLSetContainerTexture(CViewHelper * pHelper)
{
	TCHAR aPath[MAX_PATH + 1] = {0};
	GetModuleFileName(nullptr, aPath, MAX_PATH);

	CString strExe;
	CString strPath = aPath;
	auto item = strPath.ReverseFind('\\');
	if (item != -1) strExe = strPath.Left(item) + _T("\\");

	CString csSmaile = strExe + _T("\\Image\\awesomeface.png");
	CString csContainer = strExe + _T("\\Image\\container.jpg");

	CImageLoader imgSmaile;
	imgSmaile.InitialData(csSmaile);

	glGenTextures(1, &m_uiSmaileTex2D);
	glBindTexture(GL_TEXTURE_2D, m_uiSmaileTex2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSmaile.GetWidth(), imgSmaile.GetHeight(), 0, imgSmaile.GetByte() == WBFIMG_RGBA ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imgSmaile.GetBuffer());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	CImageLoader imgContainer;
	imgContainer.InitialData(csContainer);

	glGenTextures(1, &m_uiContainerTex2D);
	glBindTexture(GL_TEXTURE_2D, m_uiContainerTex2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgContainer.GetWidth(), imgContainer.GetHeight(), 0, imgContainer.GetByte() == WBFIMG_RGBA ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imgContainer.GetBuffer());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	auto pShaderManager = pHelper->GetShaderManager();
	auto& Shader = pShaderManager->GetAt(E_SHADER_CONTAINER_BOX);
	Shader.GLBind();
	{
		Shader.GLSetInt("aContainerTex2D", 0); // Texture Unit Index(GL_TEXTURE0 + 0)
	}
	Shader.GLUnbind();
}