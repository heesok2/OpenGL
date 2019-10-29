#include "stdafx.h"
#include "ModelLight.h"

#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_BASE\ViewBase.h"

#include "..\WBF_LIB\Package.h"
#include "..\WBF_DATA\EntityDefine.h"
#include "..\WBF_DATA\ModuleLight.h"

#include "..\WBF_BASE\ModelManager.h"
#include "..\WBF_BASE\WBFVBOManager.h"
#include "..\WBF_BASE\WBFVBOData.h"
#include "..\WBF_GPS\VBOGeom.h"
#include "..\WBF_GLCORE\Shader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_MODEL(E_MODEL_LIGHT, CModelLight);

CModelLight::CModelLight()
{

}

CModelLight::~CModelLight()
{
}

void CModelLight::Release()
{
}

void CModelLight::Build()
{
	auto pDoc = m_pModelMgr->GetDoc();
	auto pPackage = pDoc->GetPackage(); 

	auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);

	std::vector<CEntityLight> lstEntLight;
	auto lLightNum = pModuleLight->GetDataList(lstEntLight);

	for (auto lcaster = 0; lcaster < lLightNum; ++lcaster)
	{
		auto& EntLight = lstEntLight[lcaster];
		if (EntLight.uiType != E_ENT_POINT) continue;

		auto itr = EntLight.itrBody;
		auto key = ITR_TO_KEY(itr);

		TModelLight model;
		model.BodyKey = key;
		model.Pos = EntLight.vPos;

		m_lstLight.push_back(std::move(model));
	}
}

void CModelLight::Draw(CShader * pShader)
{
	return;

	auto pView = m_pModelMgr->GetView();
	auto pManager = m_pModelMgr->GetVBOManager();
	auto pGeom = (CVBOGeom*)pManager->Lookup(E_VBO_GEOM);
 
	pShader->GLBind();
	{
		int nProg;
		glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);
		
		glm::mat4 view = pView->GetViewMatrix();
		glm::mat4 proj = pView->GetProjectionMatrix();

		for (auto& model : m_lstLight)
		{
			TEntityVBO tData;
			if(!pGeom->GetVBO(model.BodyKey, tData))
				continue;

			glm::mat4 mod(1.f);
			mod = glm::translate(mod, model.Pos);

			auto modelLoc = glGetUniformLocation(nProg, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mod));

			auto viewLoc = glGetUniformLocation(nProg, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			auto projLoc = glGetUniformLocation(nProg, "projection");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

			glBindVertexArray(tData.VAO);
			glDrawElements(GL_TRIANGLES, tData.DataNum, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	pShader->GLUnbind();
}
