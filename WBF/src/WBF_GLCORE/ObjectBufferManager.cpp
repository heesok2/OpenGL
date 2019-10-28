#include "stdafx.h"
#include "ObjectBufferManager.h"
#include "ObjectBuffer.h"


CObjectBufferManager::CObjectBufferManager()
	: m_pView(nullptr)
{
}

CObjectBufferManager::~CObjectBufferManager()
{
	auto itr = m_mObjectBuffer.begin();
	while (itr != m_mObjectBuffer.end())
	{
		_SAFE_DELETE(itr->second);

		itr++;
	}
	
	m_mObjectBuffer.clear();
}

void CObjectBufferManager::InitialData(CView * pView)
{
	m_pView = pView;
}

void CObjectBufferManager::CreateObjectBuffer()
{
	auto& fact = CObjectBufferFactory::GetInstance();

	std::vector<UINT> lstType;
	auto lSize = fact.GetTypeList(lstType);

	for (auto indx = 0; indx < lSize; ++indx)
	{
		auto pObject = fact.CreateObject(lstType[indx]);
		if (pObject != nullptr)
		{
			m_mObjectBuffer[lstType[indx]] = (CObjectBuffer*)pObject;
		}
	}
}

BOOL CObjectBufferManager::Exist(UINT uiType)
{
	auto itr = m_mObjectBuffer.find(uiType);
	return itr != m_mObjectBuffer.end();
}

CObjectBuffer * CObjectBufferManager::LookUp(UINT uiType)
{
	auto itr = m_mObjectBuffer.find(uiType);
	if (itr == m_mObjectBuffer.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	return itr->second;
}

void CObjectBufferManager::GLBuildObjectBuffer(UINT uiFlag)
{
	auto pDoc = m_pView->GetDocument();

	auto itr = m_mObjectBuffer.begin();
	while (itr != m_mObjectBuffer.end())
	{
		auto pObject = itr->second;
		if (pObject != nullptr)
			pObject->GLBuild(pDoc, uiFlag);

		itr++;
	}
}