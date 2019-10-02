#include "stdafx.h"
#include "ModelLight.h"
#include "VBOGeom.h"

#include "..\WBF_GPS\Shader.h"
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

}

CModelLight::~CModelLight()
{
}

void CModelLight::Release()
{
}

void CModelLight::Build()
{
}

void CModelLight::Draw(CShader * pShader)
{
	auto pManager = m_pModelMgr->GetVBOManager();
	auto pVBO = pManager->Lookup(E_VBO_GEOM);

	pShader->GLBind();
	{
		pVBO->Draw();		
	}
	pShader->GLUnbind();
}
