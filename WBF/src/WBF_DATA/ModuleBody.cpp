#include "stdafx.h"
#include "ModuleBody.h"

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

	auto SZ_DATA = sizeof(int);
	auto szNum = sizeof(g_sub_index) / SZ_DATA;

	CEntityBody Data;
	Data.dbKey = GetNewKey();
	Data.lstSubBody.resize(szNum);
	std::copy(&g_sub_index[0], &g_sub_index[0] + szNum, Data.lstSubBody.begin());

	InsertNU(Data);
}