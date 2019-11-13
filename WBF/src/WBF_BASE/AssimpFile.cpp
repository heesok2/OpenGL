#include "stdafx.h"
#include "AssimpFile.h"


CAssimpFile::CAssimpFile()
{
}


CAssimpFile::~CAssimpFile()
{
}

void CAssimpFile::Scan(CString strFilePath)
{
	m_tLoader.Import(strFilePath);
}
