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
	void Import(const CString& csFilePath);
	   
protected:
	CString m_csFilePath;

};

