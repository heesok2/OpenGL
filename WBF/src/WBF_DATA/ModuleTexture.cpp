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

BOOL CModuleTexture::ExistTexture(UINT uiType, const CString& strFilePath)
{
	std::vector<DITER> aItr;
	auto lSize = GetIterList(aItr);
	for (auto indx = 0; indx < lSize; ++indx)
	{
		auto& tData = GetAtNU(aItr[indx]);
		
		if (uiType != tData.uiType)
			continue;

		if (strFilePath.CompareNoCase((tData.strPath + tData.strTexture)) == 0)
			return TRUE;
	}

	return FALSE;	
}
