#include "stdafx.h"
#include "EntityTexture.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityTexture::CEntityTexture()
{
	dbKey = 0;

	uiType = 0;
	strPath = _T("");
	strTexture = _T("");
}

CEntityTexture::~CEntityTexture()
{
}

const DTYPE CEntityTexture::GetType() const
{
	return E_TYPE_TEXTURE;
}

const DKEY CEntityTexture::GetKey() const
{
	return dbKey;
}
