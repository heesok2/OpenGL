#include "stdafx.h"
#include "VBOGeom.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\WBFPackageData.h"
#include "..\WBF_BASE\ModuleVertex.h"
#include "..\WBF_BASE\ModuleSubBody.h"
#include "..\WBF_BASE\ModuleBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_VBO(E_VBO_GEOM, CVBOGeom, CWBFVBOData);

CVBOGeom::CVBOGeom()
{
	uiVBO = 0;
	uiEBO = 0;
}

CVBOGeom::~CVBOGeom()
{
}

void CVBOGeom::ProcessData(CWBFDocBase * pDoc)
{
	auto pPackage = pDoc->GetPackage();
	auto pModuleVertex = (CModuleVertex*)pPackage->GetModule(E_TYPE_VERTEX);
	auto pModuleSubBody = (CModuleSubBody*)pPackage->GetModule(E_TYPE_SUBBODY);
	auto pModuleBody = (CModuleBody*)pPackage->GetModule(E_TYPE_BODY);

	auto SZ_POS = 3;
	auto SZ_NORM = 3;
	auto SZ_TEX = 2;
	auto SZ_DATA = SZ_POS + SZ_NORM + SZ_TEX;

	auto lBufferNum = 0;
	std::vector<CEntityBody> lstBody;

	auto lBodyNum = pModuleBody->GetDataList(lstBody);
	for (auto lbody = 0; lbody < lBodyNum; ++lbody)
	{
		for (auto dbSub : lstBody[lbody].lstSubBody)
		{
			CEntitySubBody entSubBody;
			if (!pModuleSubBody->Find(dbSub, entSubBody))
				continue;

			lBufferNum += entSubBody.lstVertex.size();
		}
	}

	auto SZ_OFFSET_POS = 0;
	auto SZ_OFFSET_NORM = lBufferNum * SZ_POS;
	auto SZ_OFFSET_TEX = lBufferNum * (SZ_POS + SZ_NORM);

	auto lDataNum = 0;
	float* aBuffer = new float[lBufferNum * SZ_DATA];
	UINT* aIndex = new UINT[lBufferNum * SZ_DATA];

	for (auto lbody = 0; lbody < lBodyNum; ++lbody)
	{
		for (auto dbSub : lstBody[lbody].lstSubBody)
		{
			CEntitySubBody entSubBody;
			if (!pModuleSubBody->Find(dbSub, entSubBody))
				continue;

			for (auto dbVertex : entSubBody.lstVertex)
			{
				CEntityVertex entVertex;
				if (!pModuleVertex->Find(dbVertex, entVertex))
					continue;

				auto pPos = glm::value_ptr(entVertex.vPos);
				auto pNorm = glm::value_ptr(entVertex.vNormal);
				auto pTex = glm::value_ptr(entVertex.vTexcord);

				std::copy(pPos, pPos + SZ_POS, &aBuffer[lBufferNum]); lDataNum += SZ_POS;
				std::copy(pNorm, pNorm + SZ_NORM, &aBuffer[lBufferNum]); lDataNum += SZ_NORM;
				std::copy(pTex, pTex + SZ_TEX, &aBuffer[lBufferNum]); lDataNum += SZ_TEX;
			}
		}
	}

	for (auto indx = 0; indx < lBufferNum; ++indx)
	{
		aIndex[indx] = indx;
	}

	/////////////////////////////////////////////////////
	// VBO

	uiVertexNum = lBufferNum;

	glGenBuffers(1, &uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lDataNum, aBuffer, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT) * lBufferNum, aIndex, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] aBuffer;
	delete[] aIndex;
}
