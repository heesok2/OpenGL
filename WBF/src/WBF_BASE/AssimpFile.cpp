#include "stdafx.h"
#include "AssimpFile.h"

#include "..\WBF_LIB\StringConverter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAssimpFile::CAssimpFile()
{
	m_strFullPath = _T("");
}

CAssimpFile::~CAssimpFile()
{
}

BOOL CAssimpFile::Import(const CString & strFullPath)
{
	m_strFullPath = strFullPath;

	Assimp::Importer importer;
	auto strFilePath = CStringConverter::CSTR2STR(strFullPath);
	const aiScene* scene = importer.ReadFile(strFilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		TRACE(importer.GetErrorString());
		return FALSE; 
	}

	for (auto lmesh = 0; lmesh < scene->mNumMeshes; ++lmesh)
	{
		auto pMesh = scene->mMeshes[lmesh];
		pMesh->mNumVertices;
		pMesh->mNumFaces;
	}
}