#include "stdafx.h"
#include "RndrLight.h"
#include "RndrAppManager.h"
#include "WBFModelManager.h"
#include "ModelLight.h"

#include "..\WBF_BASE\WBFViewBase.h"
#include "..\WBF_BASE\WBFModelDefine.h"
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
	auto pShaderMgr = ((CRndrAppManager*)m_pRndrMgr)->GetShaderManager();
	pShaderMgr->GLCreateShader(E_SHADER_LIGHT);
}

void CRndrLight::GLDraw()
{
	auto pShaderMgr = ((CRndrAppManager*)m_pRndrMgr)->GetShaderManager();
	if (!pShaderMgr->IsValidShader(GetType())) return;

	auto pModel = ((CWBFModelManager*)m_pModelMgr)->GetModel(E_MODEL_LIGHT);
	if (pModel == nullptr) return;

	auto pView = ((CRndrAppManager*)m_pRndrMgr)->GetView();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_DEPTH_TEST);
		//glPolygonMode(pOption->uiPolygonFace, pOption->uiPolygonMode);

		auto& Shader = pShaderMgr->GetShader(E_SHADER_LIGHT);
		pModel->Draw(&Shader);

		glDisable(GL_DEPTH_TEST);
	}
	glPopAttrib();

}
