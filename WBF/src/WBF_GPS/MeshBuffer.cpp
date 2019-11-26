#include "stdafx.h"
#include "MeshBuffer.h"
#include "BufferType.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_DATA\EntityDefine.h"
#include "..\WBF_DATA\ModuleTexture.h"
#include "..\WBF_DATA\ModuleNode.h"
#include "..\WBF_DATA\ModuleElement.h"
#include "..\WBF_DATA\ModuleMesh.h"
#include "..\WBF_DATA\ElementType.h"
#include "..\WBF_BASE\DocBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_BUFFER(CMeshBuffer, E_BUFFER_MESH);

CMeshBuffer::CMeshBuffer()
{
}

CMeshBuffer::~CMeshBuffer()
{
}

void CMeshBuffer::GLRelease()
{
	auto itr = m_mObjectBuffer.begin();
	while (itr != m_mObjectBuffer.end())
	{
		auto& tObjectBuffer = itr->second;

		glDeleteVertexArrays(1, &tObjectBuffer.uiVAO);
		glDeleteBuffers(1, &tObjectBuffer.uiVBO);
		glDeleteBuffers(1, &tObjectBuffer.uiEBO);

		itr++;
	}

	m_mObjectBuffer.clear();
}

void CMeshBuffer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleNode = (CModuleNode*)pPackage->GetModule(E_TYPE_NODE);
	auto pModuleElem = (CModuleElement*)pPackage->GetModule(E_TYPE_ELEMENT);
	auto pModuleMesh = (CModuleMesh*)pPackage->GetModule(E_TYPE_MESH);

	std::vector<DITER> aItrMesh;
	auto lMeshSize = pModuleMesh->GetIterList(aItrMesh);
	for (auto lmesh = 0; lmesh < lMeshSize; ++lMeshSize)
	{
		std::map<DKEY, UINT> mNodeIndx;
		auto uiVBO = GLCreateBuffer(pHelper, aItrMesh[lmesh], mNodeIndx);
		if (uiVBO == 0)
		{
			ASSERT(g_warning);
			continue;
		}

	}
}

long CMeshBuffer::GetObjectBuffer(std::map<UINT, TObjectBuffer>& mObjectBuffer)
{
	mObjectBuffer.insert(m_mObjectBuffer.begin(), m_mObjectBuffer.end());

	return (long)mObjectBuffer.size();
}

UINT CMeshBuffer::GLCreateBuffer(CViewHelper * pHelper, DITER itrMesh, std::map<DKEY, UINT>& mNodeIndx)
{
	auto lambda_glm_copy = [](const float* pSrc, UINT uiSize, float* pDest)
	{
		std::copy(pSrc, pSrc + uiSize, pDest);
		return uiSize;
	};

	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleNode = (CModuleNode*)pPackage->GetModule(E_TYPE_NODE);
	auto pModuleElem = (CModuleElement*)pPackage->GetModule(E_TYPE_ELEMENT);
	auto pModuleMesh = (CModuleMesh*)pPackage->GetModule(E_TYPE_MESH);
	
	auto VERTEX_NUM = 3;
	auto NORMAL_NUM = 3;
	auto TEXCORD_NUM = 2;
	auto BUFFER_NUM = VERTEX_NUM + NORMAL_NUM + TEXCORD_NUM;

	auto tMesh = pModuleMesh->GetAtNU(itrMesh);
	auto lVertexNum = tMesh.aItrNode.size();
	float* aBuffer = new float[lVertexNum * BUFFER_NUM];

	auto lCount = 0;
	auto lBufferNum = 0;
	for (auto itrNode : tMesh.aItrNode)
	{
		auto& tNode = pModuleNode->GetAtNU(itrNode);
		tNode.aVertex;
		tNode.aNormal;
		tNode.aTexCoord;

		lBufferNum += lambda_glm_copy(glm::value_ptr(tNode.aVertex), VERTEX_NUM, &aBuffer[lBufferNum]);
		lBufferNum += lambda_glm_copy(glm::value_ptr(tNode.aNormal), NORMAL_NUM, &aBuffer[lBufferNum]);
		lBufferNum += lambda_glm_copy(glm::value_ptr(tNode.aTexCoord), TEXCORD_NUM, &aBuffer[lBufferNum]);

		mNodeIndx[tNode.dbKey] = lCount++;
	}

	UINT VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(lVertexNum*BUFFER_NUM), aBuffer, GL_STATIC_DRAW);

	_SAFE_DELETE_ARRAY(aBuffer);

	return VBO;
}

UINT CMeshBuffer::GLCreateIndex(CViewHelper * pHelper, DITER itrMesh, std::map<DKEY, UINT>& mNodeIndx)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleNode = (CModuleNode*)pPackage->GetModule(E_TYPE_NODE);
	auto pModuleElem = (CModuleElement*)pPackage->GetModule(E_TYPE_ELEMENT);
	auto pModuleMesh = (CModuleMesh*)pPackage->GetModule(E_TYPE_MESH);

	auto tMesh = pModuleMesh->GetAtNU(itrMesh);
	auto lElemNum = tMesh.aItrElement.size();
	float* aBuffer = new float[lElemNum * 3];

	auto lCount = 0;
	auto lIndexNum = 0;
	for (auto itrElem : tMesh.aItrElement)
	{
		auto& tElem = pModuleElem->GetAtNU(itrElem);
		if (tElem.uiType != E_ELEMTYPE_TRI3)
			continue;

		auto itrNode0 = mNodeIndx.find(ITR_TO_KEY(tElem.aItrNode[0]));
		auto itrNode1 = mNodeIndx.find(ITR_TO_KEY(tElem.aItrNode[1]));
		auto itrNode2 = mNodeIndx.find(ITR_TO_KEY(tElem.aItrNode[2]));
		if (itrNode0 == mNodeIndx.end()
			|| itrNode1 == mNodeIndx.end()
			|| itrNode2 == mNodeIndx.end())
			continue;

		itrNode0->second;


	}

	return 0;
}
