#include "stdafx.h"
#include "ContainerBoxRenderer.h"
#include "RendererType.h"
#include "BufferType.h"
#include "GeometryBuffer.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_DATA\ModuleBox.h"
#include "..\WBF_DATA\ModuleLight.h"
#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_GLCORE\ObjectBufferManager.h"

IMPLEMENT_DYNAMIC_RENDERER(CContainerBoxRenderer, E_RENDERER_CONTAINER_BOX);

CContainerBoxRenderer::CContainerBoxRenderer()
{
}


CContainerBoxRenderer::~CContainerBoxRenderer()
{
}

void CContainerBoxRenderer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleBox = (CModuleBox*)pPackage->GetModule(E_TYPE_BOX);
	auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);

	auto pShaderManager = pHelper->GetShaderManager();
	auto pObjectBufferManager = pHelper->GetObjectBufferManager();
	auto pGeomBuffer = pObjectBufferManager->LookUp(E_BUFFER_GEOMETRY);

	std::vector<TObjectBuffer> lstObjectBuffer;
	auto lBufferSize = pGeomBuffer->GetObjectBuffer(lstObjectBuffer);
	if (lBufferSize == 0) return;

	for (auto& obj : lstObjectBuffer)
	{


	}


	/*
		auto pManager = m_pModelMgr->GetVBOManager();
		auto pGeom = (CVBOGeom*)pManager->Lookup(E_VBO_GEOM);

		std::vector<CEntityLight> lstLight;
		auto lLightNum = pModuleLight->GetDataList(lstLight);

		glm::vec3 aLightPos;
		if (lLightNum > 0) aLightPos = lstLight.front().vPos;
		else aLightPos = glm::vec3(1.f, 1.f, 1.f);


		std::vector<CEntityBox> lstBox;
		auto lBoxNum = pModuleBox->GetDataList(lstBox);

		for (auto lbox = 0; lbox < lBoxNum; ++lbox)
		{
			auto itr = lstBox[lbox].itrBody;
			auto key = ITR_TO_KEY(itr);

			TEntityVBO tVBO;
			if (!pGeom->GetVBO(key, tVBO))
				continue;

			TModelBox box;
			box.uiVAO = tVBO.VAO;
			box.uiDataNum = tVBO.DataNum;
			box.ModelPos = lstBox[lbox].vPos;
			box.LightPos = aLightPos;

			m_lstBox.push_back(std::move(box));
		}
	*/


	//auto pDocBase = (CDocBase*)pDoc;
	//auto pPackage = pDocBase->GetPackage();
	//auto pModuleBox = (CModuleBox*)pPackage->GetModule(E_TYPE_BOX);
	//auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);
/*
	auto p

	auto pManager = m_pModelMgr->GetVBOManager();
	auto pGeom = (CVBOGeom*)pManager->Lookup(E_VBO_GEOM);

	std::vector<CEntityLight> lstLight;
	auto lLightNum = pModuleLight->GetDataList(lstLight);

	glm::vec3 aLightPos;
	if (lLightNum > 0) aLightPos = lstLight.front().vPos;
	else aLightPos = glm::vec3(1.f, 1.f, 1.f);


	std::vector<CEntityBox> lstBox;
	auto lBoxNum = pModuleBox->GetDataList(lstBox);

	for (auto lbox = 0; lbox < lBoxNum; ++lbox)
	{
		auto itr = lstBox[lbox].itrBody;
		auto key = ITR_TO_KEY(itr);

		TEntityVBO tVBO;
		if (!pGeom->GetVBO(key, tVBO))
			continue;

		TModelBox box;
		box.uiVAO = tVBO.VAO;
		box.uiDataNum = tVBO.DataNum;
		box.ModelPos = lstBox[lbox].vPos;
		box.LightPos = aLightPos;

		m_lstBox.push_back(std::move(box));
	}*/
}

void CContainerBoxRenderer::GLDraw()
{
}
