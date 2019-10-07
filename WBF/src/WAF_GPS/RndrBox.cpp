#include "stdafx.h"
#include "RndrBox.h"
#include "ModelBox.h"
#include "WBFRndrManager.h"
#include "WBFModelManager.h"

#include "..\WBF_BASE\ModelDefine.h"
#include "..\WBF_GPS\ShaderDefine.h"
#include "..\WBF_GPS\ShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_RENDERER(E_RNDR_BOX, CRndrBox);

CRndrBox::CRndrBox()
{
}

CRndrBox::~CRndrBox()
{
}

void CRndrBox::OnInitialData()
{
	auto pShaderMgr = ((CWBFRndrManager*)m_pRndrMgr)->GetShaderManager();
	pShaderMgr->GLCreateShader(E_SHADER_BOX);
}

void CRndrBox::GLDraw()
{
	auto pShaderMgr = ((CWBFRndrManager*)m_pRndrMgr)->GetShaderManager();
	if (!pShaderMgr->IsValidShader(GetType())) return;

	auto pModel = ((CWBFModelManager*)m_pModelMgr)->GetModel(E_MODEL_BOX);
	if (pModel == nullptr) return;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_DEPTH_TEST);

		auto& Shader = pShaderMgr->GetShader(E_SHADER_BOX);
		pModel->Draw(&Shader);

		glDisable(GL_DEPTH_TEST);
	}
	glPopAttrib();
}
