#include "stdafx.h"
#include "GeometryBuffer.h"
#include "BufferType.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_BASE\DocBase.h"
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
	auto szObjectBuffer = m_lstObjectBuffer.size();
	for (auto indx = 0; indx < szObjectBuffer; ++indx)
	{
		glDeleteVertexArrays(1, &m_lstObjectBuffer[indx].uiVAO);
		glDeleteBuffers(1, &m_lstObjectBuffer[indx].uiVBO);
		glDeleteBuffers(1, &m_lstObjectBuffer[indx].uiEBO);
	}

	m_lstObjectBuffer.clear();
}

void CGeometryBuffer::GLBuild(CDocument * pDoc, UINT uiFlag)
{
	auto pDocBase = (CDocBase*)pDoc;
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

		TObjectBuffer tBuffer;
		tBuffer.uiKey = EntBody.dbKey;
		tBuffer.uiVAO = VAO;
		tBuffer.uiVBO = VBO;
		tBuffer.uiEBO = EBO;
		tBuffer.uiDataSize = lBufferIndxNum;

		m_lstObjectBuffer.push_back(std::move(tBuffer));

		_SAFE_DELETE_ARRAY(aIndex);
	}

	_SAFE_DELETE_ARRAY(aBuffer);
}

long CGeometryBuffer::GetObjectBuffer(std::vector<TObjectBuffer>& lstObjectBuffer)
{
	auto szData = (long)m_lstObjectBuffer.size();
	if (szData > 0)
	{
		lstObjectBuffer.resize(szData);
		std::copy(m_lstObjectBuffer.begin(), m_lstObjectBuffer.end(), lstObjectBuffer.begin());
	}

	return szData;
}
