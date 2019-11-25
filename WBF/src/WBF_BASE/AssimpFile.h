#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class CAssimpFile
{
public:
	CAssimpFile();
	virtual ~CAssimpFile();

public:
	BOOL Import(const CString& strFullPath);
	   
protected:
	CString m_strFullPath;

};

