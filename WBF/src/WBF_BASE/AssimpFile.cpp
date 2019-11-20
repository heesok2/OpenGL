#include "stdafx.h"
#include "AssimpFile.h"

#include "..\WBF_LIB\StringConverter.h"

CAssimpFile::CAssimpFile()
{
}


CAssimpFile::~CAssimpFile()
{
}

void CAssimpFile::Import(const CString & csFilePath)
{
	auto strFilePath = CStringConverter::CSTR2STR(csFilePath);

	



}
//
//void CAssimpFile::Import(CString csFilePath)
//{
//
//
//	// read file via ASSIMP
//	Assimp::Importer importer;
//	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//	// check for errors
//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
//	{
//		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
//		return;
//	}
//	// retrieve the directory path of the filepath
//	directory = path.substr(0, path.find_last_of('/'));
//
//	// process ASSIMP's root node recursively
//	processNode(scene->mRootNode, scene);
//}
