#include "stdafx.h"
#include "WBFPakageSystem.h"

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

		m_mModule[dbType] = datamodule;
	};

	lambda_module(D_TYPE_BOX, new CModuleBox(D_TYPE_BOX));
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
