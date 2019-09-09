#include "stdafx.h"
#include "WBFCRndrSample.h"
#include "WBFCRndrManager.h"
#include "WBFCModelManager.h"
#include "WBFCModelSample.h"

#include "..\WBF_GPS\WBFShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_RENDERER(CWBFCRndrSample, gps::E_GPS_SAMPLE);

CWBFCRndrSample::CWBFCRndrSample()
{
}

CWBFCRndrSample::~CWBFCRndrSample()
{
}

void CWBFCRndrSample::OnInitialData()
{
	auto pShaderMgr = ((CWBFCRndrManager*)m_pRndrMgr)->GetShaderManager();
	pShaderMgr->GLCreateShader(GetType());



}

void CWBFCRndrSample::GLDraw()
{
	auto pShaderMgr = ((CWBFCRndrManager*)m_pRndrMgr)->GetShaderManager();
	if (!pShaderMgr->IsValidShader(GetType())) return;

	auto pModel = ((CWBFCModelManager*)m_pModelMgr)->GetModel(GetType());
	if (pModel == nullptr) return;

	auto pOption = (CWBFGPSOption*)pModel->GetOption();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPolygonMode(pOption->uiPolygonFace, pOption->uiPolygonMode);

		auto& Shader = pShaderMgr->GetShader(GetType());
		Shader.GLBind();
		{
			if (pModel->IsValidModel())
			{
				pModel->GLBind();
				pModel->GLDraw();
				pModel->GLUnbind();
			}
		}
		Shader.GLUnbind();
	}
	glPopAttrib();
}