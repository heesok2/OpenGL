#include "stdafx.h"
#include "WBFPakage.h"

#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_DATA\ModuleVertex.h"
#include "..\WBF_DATA\ModuleSubBody.h"
#include "..\WBF_DATA\ModuleBody.h"
#include "..\WBF_DATA\ModuleTexture.h"
#include "..\WBF_DATA\ModuleNode.h"
#include "..\WBF_DATA\ModuleElement.h"
#include "..\WBF_DATA\ModuleMesh.h"
#include "..\WBF_DATA\ModuleLight.h"
#include "..\WBF_DATA\ModuleGround.h"
#include "..\WBF_DATA\ModuleBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFPackage::CWBFPackage(CDocBase* pDoc)
	: CPackage(pDoc)
{
}

CWBFPackage::~CWBFPackage()
{
}

void CWBFPackage::OnInitial()
{
	auto lambda_module = [&](DTYPE dbType, CModuleBase* datamodule)
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

	lambda_module(E_TYPE_VERTEX, new CModuleVertex(this));
	lambda_module(E_TYPE_SUBBODY, new CModuleSubBody(this));
	lambda_module(E_TYPE_BODY, new CModuleBody(this));

	lambda_module(E_TYPE_TEXTURE, new CModuleTexture(this));
	lambda_module(E_TYPE_NODE, new CModuleNode(this));
	lambda_module(E_TYPE_ELEMENT, new CModuleElement(this));
	lambda_module(E_TYPE_MESH, new CModuleMesh(this));

	lambda_module(E_TYPE_LIGHT, new CModuleLight(this));
	lambda_module(E_TYPE_GROUND, new CModuleGround(this));
	lambda_module(E_TYPE_BOX, new CModuleBox(this));

	if (m_mModule.size() != (E_TYPE_NUM - 1))
	{
		ASSERT(g_warning);
	}
}

void CWBFPackage::OnDestroy()
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

CModuleBase * CWBFPackage::GetModule(DTYPE dbType)
{
	auto itr = m_mModule.find(dbType);
	if (itr == m_mModule.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	return itr->second;
}
