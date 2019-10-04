#include "stdafx.h"
#include "ModelLight.h"
#include "VBOGeom.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\DataBaseDefine.h"
#include "..\WBF_LIB\Package.h"
#include "..\WBF_BASE\ModuleBody.h"
#include "..\WBF_BASE\ModuleLight.h"

#include "..\WBF_BASE\WBFModelDataManager.h"
#include "..\WBF_BASE\WBFVBOManager.h"
#include "..\WBF_BASE\WBFVBOData.h"
#include "..\WBF_GPS\Shader.h"

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

	auto pModuleBody = (CModuleBody*)pPackage->GetModule(E_TYPE_BODY);
	auto pModuleLight = (CModuleLight*)pPackage->GetModule(E_TYPE_LIGHT);


	// Default Box
	CEntityBody EntBody;
	if (!pModuleBody->Find(1, EntBody))
		return;

	std::vector<CEntityLight> lstEntLight;
	auto lLightNum = pModuleLight->GetDataList(lstEntLight);

	for (auto lcaster = 0; lcaster < lLightNum; ++lcaster)
	{
		auto& EntLight = lstEntLight[lcaster];
		if (EntLight.uiType != E_ENT_POINT) continue;

		TModelLight model;
		model.BodyKey = EntBody.dbKey;
		model.Pos = EntLight.vPos;

		m_lstModel.push_back(std::move(model));
	}
}

void CModelLight::Draw(CShader * pShader)
{
	auto pManager = m_pModelMgr->GetVBOManager();
	auto pGeom = (CVBOGeom*)pManager->Lookup(E_VBO_GEOM);

	int nProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);
	   	 
	pShader->GLBind();
	{
		int nProg;
		glGetIntegerv(GL_CURRENT_PROGRAM, &nProg);

		for (auto& model : m_lstModel)
		{
			TEntityVBO tData;
			if(!pGeom->GetVBO(model.BodyKey, tData))
				continue;

			glm::mat4 mod(1.f);
			mod = glm::translate(mod, model.Pos);

			auto modelLoc = glGetUniformLocation(nProg, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mod));

			glBindVertexArray(tData.VAO);
			glDrawElements(GL_TRIANGLES, tData.DataNum, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	pShader->GLUnbind();
}
