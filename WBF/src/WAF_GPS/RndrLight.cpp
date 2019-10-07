#include "stdafx.h"
#include "RndrLight.h"
#include "ModelLight.h"
#include "WBFRndrManager.h"
#include "WBFModelManager.h"

#include "..\WBF_BASE\WBFViewBase.h"
#include "..\WBF_BASE\ModelDefine.h"
#include "..\WBF_GPS\ShaderDefine.h"
#include "..\WBF_GPS\ShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_RENDERER(E_RNDR_LIGHT, CRndrLight);

CRndrLight::CRndrLight()
{
}

CRndrLight::~CRndrLight()
{
}

void CRndrLight::OnInitialData()
{
	auto pShaderMgr = ((CWBFRndrManager*)m_pRndrMgr)->GetShaderManager();
	pShaderMgr->GLCreateShader(E_SHADER_LIGHT);
}

void CRndrLight::GLDraw()
{
	auto pShaderMgr = ((CWBFRndrManager*)m_pRndrMgr)->GetShaderManager();
	if (!pShaderMgr->IsValidShader(GetType())) return;

	auto pModel = ((CWBFModelManager*)m_pModelMgr)->GetModel(E_MODEL_LIGHT);
	if (pModel == nullptr) return;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_DEPTH_TEST);

		auto& Shader = pShaderMgr->GetShader(E_SHADER_LIGHT);
		pModel->Draw(&Shader);

		glDisable(GL_DEPTH_TEST);
	}
	glPopAttrib();

}
