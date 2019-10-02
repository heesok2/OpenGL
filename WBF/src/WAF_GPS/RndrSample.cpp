#include "stdafx.h"
#include "RndrSample.h"
#include "RndrAppManager.h"
#include "WBFModelManager.h"
#include "ModelSample.h"

#include "..\WBF_GPS\ShaderDefine.h"
#include "..\WBF_GPS\ShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_RENDERER(E_RNDR_SAMPLE, CRndrSample);

CRndrSample::CRndrSample()
{
}

CRndrSample::~CRndrSample()
{
}

void CRndrSample::OnInitialData()
{
	auto pShaderMgr = ((CRndrAppManager*)m_pRndrMgr)->GetShaderManager();
	pShaderMgr->GLCreateShader(E_SHADER_SAMPLE);
}

void CRndrSample::GLDraw()
{
	//auto pShaderMgr = ((CRndrAppManager*)m_pRndrMgr)->GetShaderManager();
	//if (!pShaderMgr->IsValidShader(GetType())) return;

	//auto pModel = ((CWBFModelManager*)m_pModelMgr)->GetModel(GetType());
	//if (pModel == nullptr) return;

	//auto pOption = (CWBFGPSOption*)pModel->GetOption();

	//glPushAttrib(GL_ALL_ATTRIB_BITS);
	//{
	//	glEnable(GL_DEPTH_TEST);
	//	glPolygonMode(pOption->uiPolygonFace, pOption->uiPolygonMode);

	//	auto& Shader = pShaderMgr->GetShader(GetType());
	//	Shader.GLBind();
	//	{
	//		if (pModel->IsValidModel())
	//		{
	//			pModel->GLAttachData();

	//			pModel->GLBind();
	//			pModel->GLDraw();
	//			pModel->GLUnbind();
	//		}
	//	}
	//	Shader.GLUnbind();

	//	glDisable(GL_DEPTH_TEST);
	//}
	//glPopAttrib();
}