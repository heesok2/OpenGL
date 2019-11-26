#include "stdafx.h"
#include "ModuleTexture.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleTexture::CModuleTexture(CPackage * pPackage)
	: CModuleData<CEntityTexture>(pPackage, E_TYPE_TEXTURE)
{
}

CModuleTexture::~CModuleTexture()
{
}
