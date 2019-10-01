#include "stdafx.h"
#include "RndrLight.h"
#include "RndrAppManager.h"
#include "ModelAppManager.h"
#include "ModelLight.h"

#include "..\WBF_BASE\WBFViewBase.h"
#include "..\WBF_BASE\WBFModelDefine.h"
#include "..\WBF_GPS\WBFShaderDefine.h"
#include "..\WBF_GPS\WBFShaderManager.h"

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

	auto pModel = ((CModelAppManager*)m_pModelMgr)->GetModel(E_MODEL_LIGHT);
	if (pModel == nullptr) return;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_DEPTH_TEST);
		//glPolygonMode(pOption->uiPolygonFace, pOption->uiPolygonMode);

		auto& Shader = pShaderMgr->GetShader(E_SHADER_LIGHT);
		Shader.GLBind();
		{
			int nProg;
			glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);

			int aViewPort[4] = {0};
			glGetIntegerv(GL_VIEWPORT, aViewPort);

			glm::mat4 model(1.f);
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			glm::mat4 view(1.f);
			auto pView = (CWBFViewBase*)m_pRndrMgr->GetView();
			//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
			//view = glm::lookAt(glm::vec3(3.f, 0.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
			pView->GetViewMatrix(view);

			glm::mat4 proj(1.f);
			glm::ortho(0.f, 800.f, 0.f, 600.f, 0.1f, 100.f); // left, right, bottom, top, near, far
			proj = glm::perspective(glm::radians(45.f), (float)(aViewPort[2] - aViewPort[0]) / (float)(aViewPort[3] - aViewPort[1]), 0.1f, 100.f);

			auto modelLoc = glGetUniformLocation(nProg, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			auto viewLoc = glGetUniformLocation(nProg, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			auto projLoc = glGetUniformLocation(nProg, "projection");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


			if (pModel->IsValidModel())
			{
				pModel->GLAttachData();

				pModel->GLBind();
				pModel->GLDraw();
				pModel->GLUnbind();
			}
		}
		Shader.GLUnbind();

		glDisable(GL_DEPTH_TEST);
	}
	glPopAttrib();

}
