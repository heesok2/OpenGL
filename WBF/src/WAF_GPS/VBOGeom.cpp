#include "stdafx.h"
#include "VBOGeom.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_LIB\Package.h"
#include "..\WBF_DATA\ModuleVertex.h"
#include "..\WBF_DATA\ModuleSubBody.h"
#include "..\WBF_DATA\ModuleBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_VBO(E_VBO_GEOM, CVBOGeom);

CVBOGeom::CVBOGeom()
{
}

CVBOGeom::~CVBOGeom()
{
}

void CVBOGeom::Release()
{
	auto itr = m_mVAO.begin();
	while (itr != m_mVAO.end())
	{
		auto& EntVBO = itr->second;

		glDeleteBuffers(1, &EntVBO.VBO);
		glDeleteBuffers(1, &EntVBO.EBO);
		glDeleteVertexArrays(1, &EntVBO.VAO);

		itr++;
	}

	m_mVAO.clear();
}

void CVBOGeom::Build(CWBFDocBase * pDoc)
{
	auto pPackage = pDoc->GetPackage();
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
		for (auto lsub = 0; lsub < EntBody.lstSubBody.size(); ++lsub)
		{
			CEntitySubBody EntSubBody;
			if (!pModuleSubBody->Find(EntBody.lstSubBody[lsub], EntSubBody))
				continue;

			lIndexNum += static_cast<int>(EntSubBody.lstVertex.size());
		}

		auto lBufferIndxNum = 0;
		UINT* aIndex = new UINT[lIndexNum];
		for (auto lsub = 0; lsub < EntBody.lstSubBody.size(); ++lsub)
		{
			CEntitySubBody EntSubBody;
			if (!pModuleSubBody->Find(EntBody.lstSubBody[lsub], EntSubBody))
				continue;

			for (auto dbKey : EntSubBody.lstVertex)
				aIndex[lBufferIndxNum++] = mVertexIndex[dbKey];
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

		m_mVAO[EntBody.dbKey] = TEntityVBO(VBO, EBO, VAO, lBufferIndxNum);

		delete[] aIndex;
	}

	delete[] aBuffer;
}

void CVBOGeom::Draw()
{
	auto itr = m_mVAO.begin();
	while (itr != m_mVAO.end())
	{
		glBindVertexArray(itr->second.VAO);
		glDrawElements(GL_TRIANGLES, itr->second.DataNum, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		itr++;
	}
}

BOOL CVBOGeom::GetVBO(DKEY BodyKey, TEntityVBO & tData)
{
	auto itr = m_mVAO.find(BodyKey);
	if (itr == m_mVAO.end())
		return FALSE;

	tData = itr->second;
	return TRUE;
}