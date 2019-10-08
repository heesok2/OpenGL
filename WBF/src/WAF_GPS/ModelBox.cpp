#include "stdafx.h"
#include "ModelBox.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_DATA\DataBaseDefine.h"
#include "..\WBF_DATA\ModuleBox.h"
#include "..\WBF_DATA\ModuleLight.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\WBFViewBase.h"
#include "..\WBF_BASE\ModelManager.h"
#include "..\WBF_BASE\WBFVBOManager.h"
#include "..\WBF_GPS\VBOGeom.h"
#include "..\WBF_GPS\Shader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_MODEL(E_MODEL_BOX, CModelBox);

CModelBox::CModelBox()
{
}

CModelBox::~CModelBox()
{
}

void CModelBox::Release()
{
	m_lstBox.clear();
}

void CModelBox::Build()
{
	auto pDoc = m_pModelMgr->GetDoc();
	auto pPackage = pDoc->GetPackage();
	auto pModuleBox = (CModuleBox*)pPackage->GetModule(E_TYPE_BOX);
	auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);

	std::vector<CEntityLight> lstLight;
	auto lLightNum = pModuleLight->GetDataList(lstLight);

	glm::vec3 aLightPos;
	if(lLightNum > 0) aLightPos = lstLight.front().vPos;
	else aLightPos = glm::vec3(1.f, 1.f, 1.f);


	std::vector<CEntityBox> lstBox;
	auto lBoxNum = pModuleBox->GetDataList(lstBox);

	for (auto lbox = 0; lbox < lBoxNum; ++lbox)
	{
		TModelBox box;
		box.BodyKey = lstBox[lbox].dbBodyKey;
		box.ModelPos = lstBox[lbox].vPos;
		box.LightPos = aLightPos;

		m_lstBox.push_back(std::move(box));
	}
}

void CModelBox::Draw(CShader * pShader)
{
	auto pView = m_pModelMgr->GetView();
	auto pManager = m_pModelMgr->GetVBOManager();
	auto pGeom = (CVBOGeom*)pManager->Lookup(E_VBO_GEOM);

	pShader->GLBind();
	{
		int nProg;
		glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);

		glm::mat4 view(1.f);
		pView->GetViewMatrix(view);

		glm::mat4 proj(1.f);
		pView->GetProjectionMatrix(proj);

		glm::vec3 CamPos(0.f);
		pView->GetCameraPos(CamPos);

		for (auto& box : m_lstBox)
		{
			TEntityVBO tData;
			if (!pGeom->GetVBO(box.BodyKey, tData))
				continue;

			glm::mat4 mod(1.f);
			mod = glm::translate(mod, box.ModelPos);

			auto modelLoc = glGetUniformLocation(nProg, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mod));

			auto viewLoc = glGetUniformLocation(nProg, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			auto projLoc = glGetUniformLocation(nProg, "projection");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

			auto modelColor = glGetUniformLocation(nProg, "ourModelColor");
			glUniform3f(modelColor, 0.8f, 0.8f, 0.8f);

			auto lightColor = glGetUniformLocation(nProg, "ourLightColor");
			glUniform3f(lightColor, 1.f, 1.f, 1.f);

			auto CameraPos = glGetUniformLocation(nProg, "ourCameraPos");
			glUniform3fv(CameraPos, 1, glm::value_ptr(CamPos));
			
			auto LightPos = glGetUniformLocation(nProg, "ourLightPos");
			glUniform3fv(LightPos, 1, glm::value_ptr(box.LightPos));

			glBindVertexArray(tData.VAO);
			glDrawElements(GL_TRIANGLES, tData.DataNum, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	pShader->GLUnbind();
}

