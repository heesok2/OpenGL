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

	std::vector<TObjectBuffer> aDelObj;

	std::vector<DITER> aItrMesh;
	auto lMeshSize = pModuleMesh->GetIterList(aItrMesh);
	for (auto lmesh = 0; lmesh < lMeshSize; ++lmesh)
	{
		TObjectBuffer tObjectBuffer;
		std::map<DKEY, UINT> mNodeIndx;

		if (!GLCreateVBO(pHelper, aItrMesh[lmesh], mNodeIndx, tObjectBuffer))
		{
			ASSERT(g_warning);
			aDelObj.push_back(tObjectBuffer);

			continue;
		}

		if (!GLCreateEBO(pHelper, aItrMesh[lmesh], mNodeIndx, tObjectBuffer))
		{
			ASSERT(g_warning);
			aDelObj.push_back(tObjectBuffer);

			continue;
		}

		if (!GLCreateVAO(tObjectBuffer))
		{
			ASSERT(g_warning);
			aDelObj.push_back(tObjectBuffer);

			continue;
		}
		
		auto dbKey = ITR_TO_KEY(aItrMesh[lmesh]);
		m_mObjectBuffer[dbKey] = tObjectBuffer;
	}

	/////////////////////////////////////////////////////////////
	// 불필요한 리소스 삭제 

	auto itr = aDelObj.begin();
	while (itr != aDelObj.end())
	{
		auto& tObjectBuffer = *itr;

		if (tObjectBuffer.uiVAO != 0)
			glDeleteVertexArrays(1, &tObjectBuffer.uiVAO);
		if (tObjectBuffer.uiVBO != 0)
			glDeleteBuffers(1, &tObjectBuffer.uiVBO);
		if (tObjectBuffer.uiEBO != 0)
			glDeleteBuffers(1, &tObjectBuffer.uiEBO);

		itr++;
	}

	aDelObj.clear();
}

long CMeshBuffer::GetObjectBuffer(std::map<UINT, TObjectBuffer>& mObjectBuffer)
{
	mObjectBuffer.insert(m_mObjectBuffer.begin(), m_mObjectBuffer.end());

	return (long)mObjectBuffer.size();
}

BOOL CMeshBuffer::GLCreateVAO(TObjectBuffer & tObjectBuffer)
{
	int VERTEX_NUM = 3;
	int NORMAL_NUM = 3;
	int TEXCORD_NUM = 2;
	auto BUFFER_NUM = VERTEX_NUM + NORMAL_NUM + TEXCORD_NUM;

	glGenVertexArrays(1, &tObjectBuffer.uiVAO);
	glBindVertexArray(tObjectBuffer.uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tObjectBuffer.uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tObjectBuffer.uiEBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, VERTEX_NUM, GL_FLOAT, GL_FALSE, sizeof(float)*BUFFER_NUM, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, NORMAL_NUM, GL_FLOAT, GL_FALSE, sizeof(float)*BUFFER_NUM, (void*)(sizeof(float)*(VERTEX_NUM)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, TEXCORD_NUM, GL_FLOAT, GL_FALSE, sizeof(float)*BUFFER_NUM, (void*)(sizeof(float)*(VERTEX_NUM + NORMAL_NUM)));

	glBindVertexArray(0);

	return TRUE;
}

BOOL CMeshBuffer::GLCreateVBO(CViewHelper * pHelper, DITER itrMesh, OUT std::map<DKEY, UINT>& mNodeIndx, OUT TObjectBuffer& tObjectBuffer)
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

	int VERTEX_NUM = 3;
	int NORMAL_NUM = 3;
	int TEXCORD_NUM = 2;
	auto BUFFER_NUM = VERTEX_NUM + NORMAL_NUM + TEXCORD_NUM;

	auto tMesh = pModuleMesh->GetAtNU(itrMesh);
	auto lVertexNum = tMesh.aItrNode.size();
	float* aBuffer = new float[lVertexNum * BUFFER_NUM];

	auto lCount = 0;
	auto lBufferIndex = 0;
	for (auto itrNode : tMesh.aItrNode)
	{
		auto& tNode = pModuleNode->GetAtNU(itrNode);
		tNode.aVertex;
		tNode.aNormal;
		tNode.aTexCoord;

		lBufferIndex += lambda_glm_copy(glm::value_ptr(tNode.aVertex), VERTEX_NUM, &aBuffer[lBufferIndex]);
		lBufferIndex += lambda_glm_copy(glm::value_ptr(tNode.aNormal), NORMAL_NUM, &aBuffer[lBufferIndex]);
		lBufferIndex += lambda_glm_copy(glm::value_ptr(tNode.aTexCoord), TEXCORD_NUM, &aBuffer[lBufferIndex]);

		mNodeIndx[tNode.dbKey] = lCount++;
	}

	glGenBuffers(1, &tObjectBuffer.uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tObjectBuffer.uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(lVertexNum*BUFFER_NUM), aBuffer, GL_STATIC_DRAW);

	_SAFE_DELETE_ARRAY(aBuffer);	

	return TRUE;
}

BOOL CMeshBuffer::GLCreateEBO(CViewHelper * pHelper, DITER itrMesh, IN std::map<DKEY, UINT>& mNodeIndx, OUT TObjectBuffer& tObjectBuffer)
{
	auto pDoc = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDoc->GetPackage();
	auto pModuleNode = (CModuleNode*)pPackage->GetModule(E_TYPE_NODE);
	auto pModuleElem = (CModuleElement*)pPackage->GetModule(E_TYPE_ELEMENT);
	auto pModuleMesh = (CModuleMesh*)pPackage->GetModule(E_TYPE_MESH);

	auto tMesh = pModuleMesh->GetAtNU(itrMesh);
	auto lElemNum = tMesh.aItrElement.size();
	UINT* aBuffer = new UINT[lElemNum * 3];

	auto lBufferIndex = 0;
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

		aBuffer[lBufferIndex++] = itrNode0->second;
		aBuffer[lBufferIndex++] = itrNode1->second;
		aBuffer[lBufferIndex++] = itrNode2->second;
	}

	tObjectBuffer.uiSize = lBufferIndex;

	glGenBuffers(1, &tObjectBuffer.uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tObjectBuffer.uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT)*tObjectBuffer.uiSize, aBuffer, GL_STATIC_DRAW);

	_SAFE_DELETE_ARRAY(aBuffer);

	return TRUE;
}
