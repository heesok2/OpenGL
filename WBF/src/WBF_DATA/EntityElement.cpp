#include "stdafx.h"
#include "EntityElement.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityElement::CEntityElement()
{
}


CEntityElement::~CEntityElement()
{
}

const DTYPE CEntityElement::GetType() const
{
	return E_TYPE_ELEMENT;
}

const DKEY CEntityElement::GetKey() const
{
	return dbKey;
}
