#include "stdafx.h"
#include "MeshRenderer.h"
#include "RendererType.h"
#include "BufferType.h"
#include "MeshBuffer.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_LIB\ImageLoader.h"
#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_GLCORE\ShaderDefine.h"
#include "..\WBF_GLCORE\ShaderManager.h"
#include "..\WBF_GLCORE\ObjectBufferManager.h"
#include "..\WBF_DATA\EntityDefine.h"
#include "..\WBF_DATA\ModuleMesh.h"
#include "..\WBF_DATA\ModuleTexture.h"
#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_BASE\ViewBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_RENDERER(CMeshRenderer, E_RENDERER_MESH);

CMeshRenderer::CMeshRenderer()
{
}


CMeshRenderer::~CMeshRenderer()
{
}

void CMeshRenderer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	if (uiFlag == 0)
	{
		SetMeshData(pHelper);

		GLSetTexture(pHelper);
	}
}

void CMeshRenderer::GLDraw(CViewHelper * pHelper)
{
	if (m_aData.empty())
		return;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	auto pShaderManager = pHelper->GetShaderManager();
	auto& Shader = pShaderManager->GetAt(E_SHADER_MESH);
	Shader.GLBind();
	{
		auto pView = (CViewBase*)pHelper->GetView();
		auto matViewMatrix = pView->GetViewMatrix();
		auto matProjectionMatrix = pView->GetProjectionMatrix();

		glm::mat4 matModelMatrix(1.f);

		for (auto& tData : m_aData)
		{
			Shader.GLSetMatrix4("tMatrix.matModel", matModelMatrix);
			Shader.GLSetMatrix4("tMatrix.matView", matViewMatrix);
			Shader.GLSetMatrix4("tMatrix.matProjection", matProjectionMatrix);
			
			Shader.GLSetInt("texture_diffuse", 0); // Texture Unit Index(GL_TEXTURE0 + 0)

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_mTexIndex[tData.uiDiff]);


			glBindVertexArray(tData.uiVAO);
			glDrawElements(GL_TRIANGLES, tData.uiSize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	Shader.GLUnbind();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CMeshRenderer::SetMeshData(CViewHelper * pHelper)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleMesh = (CModuleMesh*)pPackage->GetModule(E_TYPE_MESH);
	auto pModuleTexture = (CModuleTexture*)pPackage->GetModule(E_TYPE_TEXTURE);

	auto pObjectBufferManager = pHelper->GetObjectBufferManager();
	auto pMeshBuffer = pObjectBufferManager->LookUp(E_BUFFER_MESH);

	std::map<UINT, TObjectBuffer> mObjectBuffer;
	auto szObjectBufferNum = pMeshBuffer->GetObjectBuffer(mObjectBuffer);
	if (szObjectBufferNum == 0) return;

	std::vector<DITER> aItrMesh;
	auto lMeshSize = pModuleMesh->GetIterList(aItrMesh);
	for (auto indx = 0; indx < lMeshSize; ++indx)
	{
		auto& tMesh = pModuleMesh->GetAtNU(aItrMesh[indx]);
		auto itrFind = mObjectBuffer.find(tMesh.dbKey);
		if (itrFind == mObjectBuffer.end()) 
			continue;
		
		DKEY dbKey;
		for (auto itrTex : tMesh.aItrTexture)
		{
			auto tTex = pModuleTexture->GetAtNU(itrTex);
			if (tTex.uiType == E_TEX_DIFFUSE)
				dbKey = tTex.dbKey;
		}

		TMesh tData;
		tData.uiVAO = itrFind->second.uiVAO;
		tData.uiSize = itrFind->second.uiSize;
		tData.uiDiff = dbKey;		

		m_aData.push_back(std::move(tData));
	}
}

void CMeshRenderer::GLSetTexture(CViewHelper * pHelper)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleMesh = (CModuleMesh*)pPackage->GetModule(E_TYPE_MESH);
	auto pModuleTexture = (CModuleTexture*)pPackage->GetModule(E_TYPE_TEXTURE);

	auto pObjectBufferManager = pHelper->GetObjectBufferManager();
	auto pMeshBuffer = pObjectBufferManager->LookUp(E_BUFFER_MESH);

	std::map<UINT, TObjectBuffer> mObjectBuffer;
	auto szObjectBufferNum = pMeshBuffer->GetObjectBuffer(mObjectBuffer);
	if (szObjectBufferNum == 0) return;

	auto lambda_tex2D = [](CString& csPath)
	{
		CImageLoader imgLoader;
		imgLoader.Import(csPath);

		int nFormat = GL_RED;
		if (imgLoader.GetByte() == WBFIMG_RGBA)
			nFormat = GL_RGBA;
		else if (imgLoader.GetByte() == WBFIMG_RGB)
			nFormat = GL_RGB;

		UINT uiTex2D = 0;
		glGenTextures(1, &uiTex2D);
		glBindTexture(GL_TEXTURE_2D, uiTex2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgLoader.GetWidth(), imgLoader.GetHeight(), 0, nFormat, GL_UNSIGNED_BYTE, imgLoader.GetBuffer());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return uiTex2D;
	};

	std::vector<DITER> aItrTex;
	auto lTexSize = pModuleTexture->GetIterList(aItrTex);
	for (auto indx = 0; indx < lTexSize; ++indx)
	{
		auto& tData = pModuleTexture->GetAtNU(aItrTex[indx]);
		if (tData.uiType != E_TEX_DIFFUSE)
			continue;
	
		CString strFilePath = (tData.strPath + tData.strTexture);
		m_mTexIndex[tData.dbKey] = lambda_tex2D(strFilePath);
	}
}
