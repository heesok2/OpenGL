#include "stdafx.h"
#include "FileCtrlManager.h"
#include "AssimpManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFileCtrlManager::CFileCtrlManager(CDocBase* pDocBase)
	: m_pDoc(pDocBase)
{
	m_pFileManager = new CAssimpManager;
}

CFileCtrlManager::~CFileCtrlManager()
{
	_SAFE_DELETE(m_pFileManager);
}

IFileManager * CFileCtrlManager::GetFileManager()
{
	return m_pFileManager;
}
