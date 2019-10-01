#include "stdafx.h"
#include "ModelLight.h"
#include "VBOGeom.h"

#include "..\WBF_BASE\WBFModelDataManager.h"
#include "..\WBF_BASE\WBFVBOManager.h"
#include "..\WBF_BASE\WBFVBOData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_MODEL(E_MODEL_LIGHT, CModelLight);

CModelLight::CModelLight()
{
	uiVAO = 0;
}


CModelLight::~CModelLight()
{
}

BOOL CModelLight::IsValidModel()
{
	return uiVAO > 0;
}

void CModelLight::GLInitialData()
{
	if (IsValidModel())
		GLDelete();
}

void CModelLight::GLCreateVBO()
{
	auto pVBOManager = m_pModelMgr->GetVBOManager();
	auto pGeom = (CVBOGeom*)pVBOManager->GetVBO(E_VBO_GEOM);

	auto uiVBO = pGeom->uiVBO;
	auto uiEBO = pGeom->uiEBO;

	auto uiOffset1 = pGeom->uiVertexNum * sizeof(GL_FLOAT) * 0;
	auto uiOffset2 = pGeom->uiVertexNum * sizeof(GL_FLOAT) * 3;
	auto uiOffset3 = pGeom->uiVertexNum * sizeof(GL_FLOAT) * 6;


	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)uiOffset1);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)uiOffset2);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)uiOffset3);
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);
}

void CModelLight::GLAttachData()
{
}

void CModelLight::GLBind()
{
}

void CModelLight::GLDraw()
{
}

void CModelLight::GLUnbind()
{
}

void CModelLight::GLDelete()
{
}
