#include "stdafx.h"
#include "ModuleBody.h"
#include "ModuleSubBody.h"

#include "..\WBF_LIB\Package.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int g_sub_index[] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

CModuleBody::CModuleBody(CPackage * pPackage)
	: CModuleData<CEntityBody>(pPackage, E_TYPE_BODY)
{
}

CModuleBody::~CModuleBody()
{
}

void CModuleBody::SetDefaultData()
{
	if (!Empty()) return;

	auto pModuleSubBody = (CModuleSubBody*)m_pPackage->GetModule(E_TYPE_SUBBODY);

	auto SZ_DATA = sizeof(int);
	auto szNum = sizeof(g_sub_index) / SZ_DATA;

	CEntityBody Data;
	Data.dbKey = GetNewKey();
	Data.aItrSubBody.resize(szNum);

	for (auto lsub = 0; lsub < szNum; ++lsub)
	{
		auto key = g_sub_index[lsub];
		auto itr = pModuleSubBody->Find(key);
		if (ITR_IS_VALID(itr))
			Data.aItrSubBody[lsub] = itr;
		else
			ASSERT(g_warning);
	}

	InsertNU(Data);
}