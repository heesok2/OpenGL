#include "stdafx.h"
#include "ModuleNode.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleNode::CModuleNode(CPackage * pPackage)
	: CModuleData<CEntityNode>(pPackage, E_TYPE_NODE)
{
}

CModuleNode::~CModuleNode()
{
}
