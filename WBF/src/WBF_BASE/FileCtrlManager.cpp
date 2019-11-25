#include "stdafx.h"
#include "FileCtrlManager.h"


CFileCtrlManager::CFileCtrlManager(CDocBase* pDocBase)
	: m_pDoc(pDocBase)
{
	m_pFileManager = nullptr;
}

CFileCtrlManager::~CFileCtrlManager()
{
	_SAFE_DELETE(m_pFileManager);
}

IFileManager * CFileCtrlManager::GetFileManager()
{
	return m_pFileManager;
}
