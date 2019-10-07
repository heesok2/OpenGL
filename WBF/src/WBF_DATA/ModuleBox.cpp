#include "stdafx.h"
#include "ModuleBox.h"
#include "ModuleBody.h"
#include "DataBaseDefine.h"

#include "..\WBF_LIB\Package.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

glm::vec3 cubePositions[] =
{
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

CModuleBox::CModuleBox(CPackage * pPackage)
	: CModuleData<CEntityBox>(pPackage, E_TYPE_BOX)
{
}

CModuleBox::~CModuleBox()
{
}

void CModuleBox::SetDefaultData()
{
	if (!Empty()) return;

	auto pModuleBody = static_cast<CModuleBody*>(m_pPackage->GetModule(E_TYPE_BODY));

	CEntityBody EntBody;
	if (!pModuleBody->Find(1, EntBody)) return;

	for (auto lcube = 0; lcube < 10; ++lcube)
	{
		CEntityBox EntBox;
		EntBox.dbKey = GetNewKey();
		EntBox.dbBodyKey = EntBody.dbKey;
		EntBox.vPos = cubePositions[lcube];

		Insert(EntBox);
	}
}
