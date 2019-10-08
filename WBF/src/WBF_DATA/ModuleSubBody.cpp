#include "stdafx.h"
#include "ModuleSubBody.h"
#include "ModuleVertex.h"

#include "..\WBF_LIB\Package.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int g_tri_index[] = {
	1, 1, 2, 3,
	1, 4, 5, 6,

	1, 7, 8, 9,
	1, 10, 11, 12, 

	1, 13, 14, 15,
	1, 16, 17, 18,
			   
	1, 19, 20, 21,
	1, 22, 23, 24,
			   
	1, 25, 26, 27,
	1, 28, 29, 30,
			   
	1, 31, 32, 33,
	1, 34, 35, 36
};

CModuleSubBody::CModuleSubBody(CPackage * pPackage)
	: CModuleData<CEntitySubBody>(pPackage, E_TYPE_SUBBODY)
{
}

CModuleSubBody::~CModuleSubBody()
{
}

void CModuleSubBody::SetDefaultData()
{
	if (!Empty()) return;

	auto pModuleVertex = (CModuleVertex*)m_pPackage->GetModule(E_TYPE_VERTEX);

	auto SZ_DATA = sizeof(int) * 4;
	auto szNum = sizeof(g_tri_index) / SZ_DATA;
	for (auto indx = 0; indx < static_cast<int>(szNum); ++indx)
	{
		CEntitySubBody Data;
		Data.dbKey = GetNewKey();
		Data.uiSubType = g_tri_index[indx * 4 + 0];
		
		Data.aItrVertex.resize(3);
		for (auto lvtx = 0; lvtx < 3; ++lvtx)
		{
			auto key = g_tri_index[indx * 4 + 1 + lvtx];
			auto itr = pModuleVertex->Find(key);

			if (ITR_IS_VALID(itr))
				Data.aItrVertex[lvtx] = itr;
			else
				ASSERT(g_warning);
		}

		InsertNU(Data);
	}
}
