#include "stdafx.h"
#include "GeometryBuffer.h"
#include "BufferType.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_GLCORE\ViewHelper.h"
#include "..\WBF_DATA\ModuleVertex.h"
#include "..\WBF_DATA\ModuleSubBody.h"
#include "..\WBF_DATA\ModuleBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_BUFFER(CGeometryBuffer, E_BUFFER_GEOMETRY);

CGeometryBuffer::CGeometryBuffer()
{
}

CGeometryBuffer::~CGeometryBuffer()
{
}

void CGeometryBuffer::GLRelease()
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

void CGeometryBuffer::GLBuild(CViewHelper * pHelper, UINT uiFlag)
{
	auto pDocBase = (CDocBase*)pHelper->GetDocument();
	auto pPackage = pDocBase->GetPackage();
	auto pModuleVertex = (CModuleVertex*)pPackage->GetModule(E_TYPE_VERTEX);
	auto pModuleSubBody = (CModuleSubBody*)pPackage->GetModule(E_TYPE_SUBBODY);
	auto pModuleBody = (CModuleBody*)pPackage->GetModule(E_TYPE_BODY);

	auto lambda_glm_copy = [](float* pSrc, UINT uiSize, float* pDest)
	{
		std::copy(pSrc, pSrc + uiSize, pDest);
		return uiSize;
	};

	auto VERTEX_NUM = 3;
	auto NORMAL_NUM = 3;
	auto TEXCORD_NUM = 2;
	auto BUFFER_NUM = VERTEX_NUM + NORMAL_NUM + TEXCORD_NUM;

	std::map<UINT, UINT> mVertexIndex;
	std::vector<CEntityVertex> lstVertex;
	std::vector<CEntityBody> lstBody;

	auto lVertexNum = pModuleVertex->GetDataList(lstVertex);
	auto lBodyNum = pModuleBody->GetDataList(lstBody);

	float* aBuffer = new float[lVertexNum * BUFFER_NUM];

	auto lBufferNum = 0;
	for (auto lvtx = 0; lvtx < lVertexNum; ++lvtx)
	{
		auto& EntVertex = lstVertex[lvtx];

		lBufferNum += lambda_glm_copy(glm::value_ptr(EntVertex.vPos), VERTEX_NUM, &aBuffer[lBufferNum]);
		lBufferNum += lambda_glm_copy(glm::value_ptr(EntVertex.vNormal), NORMAL_NUM, &aBuffer[lBufferNum]);
		lBufferNum += lambda_glm_copy(glm::value_ptr(EntVertex.vTexcord), TEXCORD_NUM, &aBuffer[lBufferNum]);

		mVertexIndex[EntVertex.dbKey] = lvtx;
	}

	UINT VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(lVertexNum*BUFFER_NUM), aBuffer, GL_STATIC_DRAW);

	for (auto lbody = 0; lbody < lBodyNum; ++lbody)
	{
		auto& EntBody = lstBody[lbody];

		auto lIndexNum = 0;
		for (auto lsub = 0; lsub < static_cast<int>(EntBody.aItrSubBody.size()); ++lsub)
		{
			auto itr = EntBody.aItrSubBody[lsub];
			auto key = ITR_TO_KEY(itr);

			CEntitySubBody EntSubBody;
			if (!pModuleSubBody->Find(key, EntSubBody))
				continue;

			lIndexNum += static_cast<int>(EntSubBody.aItrVertex.size());
		}

		auto lBufferIndxNum = 0;
		UINT* aIndex = new UINT[lIndexNum];
		for (auto lsub = 0; lsub < static_cast<int>(EntBody.aItrSubBody.size()); ++lsub)
		{
			auto itr = EntBody.aItrSubBody[lsub];
			auto key = ITR_TO_KEY(itr);

			CEntitySubBody EntSubBody;
			if (!pModuleSubBody->Find(key, EntSubBody))
				continue;

			for (auto itrVertex : EntSubBody.aItrVertex)
			{
				auto dbKey = ITR_TO_KEY(itrVertex);
				aIndex[lBufferIndxNum++] = mVertexIndex[dbKey];
			}
		}

		///////////////////////////////////////////////////////////

		UINT EBO, VAO;

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT)*lBufferIndxNum, aIndex, GL_STATIC_DRAW);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, VERTEX_NUM, GL_FLOAT, GL_FALSE, sizeof(float)*BUFFER_NUM, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, NORMAL_NUM, GL_FLOAT, GL_FALSE, sizeof(float)*BUFFER_NUM, (void*)(sizeof(float)*(VERTEX_NUM)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, TEXCORD_NUM, GL_FLOAT, GL_FALSE, sizeof(float)*BUFFER_NUM, (void*)(sizeof(float)*(VERTEX_NUM + NORMAL_NUM)));

		glBindVertexArray(0);

		TObjectBuffer tObjectBuffer;
		tObjectBuffer.uiVAO = VAO;
		tObjectBuffer.uiVBO = VBO;
		tObjectBuffer.uiEBO = EBO;
		tObjectBuffer.uiSize = lBufferIndxNum;

		m_mObjectBuffer[EntBody.dbKey] = tObjectBuffer;

		_SAFE_DELETE_ARRAY(aIndex);
	}

	_SAFE_DELETE_ARRAY(aBuffer);
}

long CGeometryBuffer::GetObjectBuffer(std::map<UINT, TObjectBuffer>& mObjectBuffer)
{
	mObjectBuffer.insert(m_mObjectBuffer.begin(), m_mObjectBuffer.end());

	return (long)mObjectBuffer.size();
}
