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
		Shader.GLBind();
		{
			auto pView = (CWBFViewBase*)m_pRndrMgr->GetView();

			glm::mat4 view(1.f);
			pView->GetViewMatrix(view);

			int aViewPort[4] = {0};
			glGetIntegerv(GL_VIEWPORT, aViewPort);

			glm::mat4 proj(1.f);
			proj = glm::perspective(glm::radians(45.f), (float)(aViewPort[2] - aViewPort[0]) / (float)(aViewPort[3] - aViewPort[1]), 0.1f, 100.f);

			int nProg;
			glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);

			auto viewLoc = glGetUniformLocation(nProg, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			auto projLoc = glGetUniformLocation(nProg, "projection");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		}
		Shader.GLUnbind();

		pModel->Draw(&Shader);

		glDisable(GL_DEPTH_TEST);
	}
	glPopAttrib();

}
