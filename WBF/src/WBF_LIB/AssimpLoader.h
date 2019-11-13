#pragma once

#ifndef DEF_ASSIMP_LOADER
#define DEF_ASSIMP_LOADER

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "HeaderPre.h"

class __MY_EXT_API__ CAssimpLoader
{
public:
	CAssimpLoader();
	virtual ~CAssimpLoader();

public:
	BOOL Import(CString strFilePath);

protected:
	CString m_strFilePath;

};

#include "HeaderPost.h"

#endif // !DEF_ASSIMP_LOADER