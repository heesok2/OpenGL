#include "stdafx.h"
#include "RndrLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_RENDERER(CRndrLight, gps::E_GPS_LIGHT);

CRndrLight::CRndrLight()
{
}

CRndrLight::~CRndrLight()
{
}

void CRndrLight::GLDraw()
{
}