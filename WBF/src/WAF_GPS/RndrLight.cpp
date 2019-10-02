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

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_DEPTH_TEST);
		//glPolygonMode(pOption->uiPolygonFace, pOption->uiPolygonMode);

		auto& Shader = pShaderMgr->GetShader(E_SHADER_LIGHT);
		Shader.GLBind();
		{
			auto pView = (CWBFViewBase*)m_pRndrMgr->GetView();
			glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

			int nProg;
			glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);

			glm::mat4 model(1.f);
			model = glm::translate(model, lightPos);
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			glm::mat4 view(1.f);
			pView->GetViewMatrix(view);
			//view = glm::lookAt(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

			//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
			//view = glm::lookAt(glm::vec3(3.f, 0.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
			//pView->GetViewMatrix(view);

			glm::mat4 proj(1.f);

			int aViewPort[4] = {0};
			glGetIntegerv(GL_VIEWPORT, aViewPort);
			proj = glm::perspective(glm::radians(45.f), (float)(aViewPort[2] - aViewPort[0]) / (float)(aViewPort[3] - aViewPort[1]), 0.1f, 100.f);

			auto modelLoc = glGetUniformLocation(nProg, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

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
