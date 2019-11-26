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
	dbKey = 0;

	aVertex = glm::vec3(0);
	aNormal = glm::vec3(0);
	aTexCoord = glm::vec2(0);
	aTangent = glm::vec3(0);
	aBitangent = glm::vec3(0);
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
