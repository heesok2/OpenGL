#include "stdafx.h"
#include "AssimpLoader.h"
#include "StringConverter.h"

CAssimpLoader::CAssimpLoader()
{
}

CAssimpLoader::~CAssimpLoader()
{
}

BOOL CAssimpLoader::Import(CString strFilePath)
{
	std::string conv = CStringConverter::CSTR2STR(strFilePath);

	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(conv, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) // if is Not Zero
	{
		ASSERT(g_warning);
		TRACE(importer.GetErrorString());
		return FALSE;
	}
	
	auto pGetScene = importer.GetScene();

	importer.FreeScene();

	auto pFreeGetScene = importer.GetScene();
	if (pFreeGetScene == nullptr)
	{
		ASSERT(g_warning);
	}

	return TRUE;
}

//
//void CAssimpLoader::ProcessNode(aiNode * node, const aiScene * scene)
//{
//	for (unsigned int i = 0; i < node->mNumMeshes; i++)
//	{
//		// the node object only contains indices to index the actual objects in the scene. 
//		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		//meshes.push_back(processMesh(mesh, scene));
//	}
//	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
//	for (unsigned int i = 0; i < node->mNumChildren; i++)
//	{
//		ProcessNode(node->mChildren[i], scene);
//	}
//}
//
//BOOL CAssimpLoader::BuildMesh(const aiScene * pScene, aiNode * pNode)
//{
//	for (auto indx = 0; indx < pNode->mNumMeshes; ++indx)
//	{
//		auto pMesh = pScene->mMeshes[pNode->mMeshes[indx]];
//
//		for (auto lvtx = 0; lvtx < pMesh->mNumVertices; ++lvtx)
//		{
//			auto& tVertex = pMesh->mVertices[lvtx];
//			auto& tNormal = pMesh->mNormals[lvtx];
//			auto pTexCoods = pMesh->mTextureCoords[0];
//
//			auto& tTangent = pMesh->mTangents[lvtx];
//			auto& tBitangent = pMesh->mBitangents[lvtx];
//			
//		}
//
//		for (auto lface = 0; lface < pMesh->mNumFaces; ++lface)
//		{
//			if (pMesh->mPrimitiveTypes & aiPrimitiveType_TRIANGLE)
//			{
//				// Triangle
//			}
//
//			auto& tFace = pMesh->mFaces[lface];
//			tFace.mIndices;
//		}
//	}
//
//	for (auto lchild = 0; lchild < pNode->mNumChildren; ++lchild)
//	{
//		if (!BuildMesh(pScene, pNode->mChildren[lchild]))
//		{
//			ASSERT(g_warning);
//			return FALSE;
//		}
//	}
//
//	return TRUE;
//}