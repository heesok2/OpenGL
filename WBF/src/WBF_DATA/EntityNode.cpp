#include "stdafx.h"
#include "EntityNode.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityNode::CEntityNode()
{
}

CEntityNode::~CEntityNode()
{
}

const DTYPE CEntityNode::GetType() const
{
	return E_TYPE_NODE;
}

const DKEY CEntityNode::GetKey() const
{
	return dbKey;
}
