#include "stdafx.h"
#include "WBFCRndrSample.h"
#include "WBFCRndrManager.h"
#include "WBFCModelManager.h"

#include "..\WBF_GPS\WBFShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_RENDERER(CWBFCRndrSample, gps::E_GPS_SAMPLE);

CWBFCRndrSample::CWBFCRndrSample() : CWBFRndrBase()
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

	auto Shader = pShaderMgr->GetShader(GetType());
	Shader.GLBind();
	{
		glColor3f(0.f, 0.f, 0.f);
		glBegin(GL_TRIANGLES);

		glVertex3f(-0.5f, -0.5f, 0.f);
		glVertex3f(0.5f, -0.5f, 0.f);
		glVertex3f(0.f, 0.5f, 0.f);

		glEnd();
	}
	Shader.GLUnbind();
}