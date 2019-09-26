#include "stdafx.h"
#include "WBFPakageSystem.h"

#include "..\WBF_BASE\ModuleVertex.h"
#include "..\WBF_BASE\ModuleSubBody.h"
#include "..\WBF_BASE\ModuleBody.h"
#include "..\WBF_BASE\ModuleGeom.h"
#include "..\WBF_BASE\ModuleBox.h"

CWBFPackageSystem::CWBFPackageSystem()
{
}

CWBFPackageSystem::~CWBFPackageSystem()
{
}

void CWBFPackageSystem::OnInitial()
{
	auto lambda_module = [&](DTYPE dbType, CWBFModuleBase* datamodule)
	{
		auto itr = m_mModule.find(dbType);
		if (itr != m_mModule.end())
		{
			ASSERT(g_warning);
			m_mModule.erase(itr);
		}

		ASSERT(datamodule->GetDataType() == dbType);
		m_mModule[dbType] = datamodule;
	};

	lambda_module(E_TYPE_VERTEX, new CModuleVertex);
	lambda_module(E_TYPE_SUBBODY, new CModuleSubBody);
	lambda_module(E_TYPE_BODY, new CModuleBody);
	lambda_module(E_TYPE_GEOM, new CModuleGeom);
	lambda_module(E_TYPE_BOX, new CModuleBox);
}

void CWBFPackageSystem::OnDestroy()
{
	auto itr = m_mModule.begin();
	while (itr != m_mModule.end())
	{
		if (itr->second)
			itr->second->Clear();

		_SAFE_DELETE(itr->second);

		itr++;
	}

	m_mModule.clear();
}

CWBFModuleBase * CWBFPackageSystem::GetModule(DTYPE dbType)
{
	auto itr = m_mModule.find(dbType);
	if (itr == m_mModule.end()) return nullptr;

	return itr->second;
}
