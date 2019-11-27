#include "stdafx.h"
#include "AssimpFile.h"

#include "..\WBF_LIB\StringConverter.h"
#include "..\WBF_LIB\FileCtrl.h"
#include "..\WBF_LIB\Package.h"
#include "..\WBF_DATA\EntityDefine.h"
#include "..\WBF_DATA\ModuleTexture.h"
#include "..\WBF_DATA\ModuleNode.h"
#include "..\WBF_DATA\ModuleElement.h"
#include "..\WBF_DATA\ModuleMesh.h"
#include "..\WBF_DATA\ElementType.h"
#include "..\WBF_BASE\DocBase.h"

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

	auto strFilePath = CStringConverter::CSTR2STR(strFullPath, CP_UTF8);
	const aiScene* pScene = m_Importer.ReadFile(strFilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) // if is Not Zero
	{
		TRACE(m_Importer.GetErrorString());
		return FALSE;
	}

	return TRUE;
}

BOOL CAssimpFile::MakeDB(CDocBase * pDoc)
{
	auto pScene = m_Importer.GetScene();
	if (pScene == nullptr)
	{
		ASSERT(g_warning);
		return FALSE;
	}

	CFileCtrl FileCtrl(m_strFullPath);
	auto strFilePath = FileCtrl.GetPath();

	auto pPackage = pDoc->GetPackage();
	if (!pPackage->Start())
		return FALSE;

	auto pModuleTexture = (CModuleTexture*)pPackage->GetModule(E_TYPE_TEXTURE);
	auto pModuleNode = (CModuleNode*)pPackage->GetModule(E_TYPE_NODE);
	auto pModuleElement = (CModuleElement*)pPackage->GetModule(E_TYPE_ELEMENT);
	auto pModuleMesh = (CModuleMesh*)pPackage->GetModule(E_TYPE_MESH);

	auto lambda_material = [&](aiMaterial* pMaterial, aiTextureType uiType, OUT std::vector<DITER>& aItr)
	{
		auto lambda_type = [](aiTextureType uiType)
		{
			UINT uiTexType = E_TEX_UNKNOWN;
			switch (uiType)
			{
			case aiTextureType_NONE:
				break;
			case aiTextureType_DIFFUSE:
				uiTexType = E_TEX_DIFFUSE;
				break;
			case aiTextureType_SPECULAR:
				break;
			case aiTextureType_AMBIENT:
				break;
			case aiTextureType_EMISSIVE:
				break;
			case aiTextureType_HEIGHT:
				break;
			case aiTextureType_NORMALS:
				break;
			case aiTextureType_SHININESS:
				break;
			case aiTextureType_OPACITY:
				break;
			case aiTextureType_DISPLACEMENT:
				break;
			case aiTextureType_LIGHTMAP:
				break;
			case aiTextureType_REFLECTION:
				break;
			case aiTextureType_BASE_COLOR:
				break;
			case aiTextureType_NORMAL_CAMERA:
				break;
			case aiTextureType_EMISSION_COLOR:
				break;
			case aiTextureType_METALNESS:
				break;
			case aiTextureType_DIFFUSE_ROUGHNESS:
				break;
			case aiTextureType_AMBIENT_OCCLUSION:
				break;
			case aiTextureType_UNKNOWN:
				break;
			case _aiTextureType_Force32Bit:
				break;
			default:
				break;
			}

			return uiTexType;
		};

		auto lCount = pMaterial->GetTextureCount(uiType);
		for (unsigned int ltex = 0; ltex < lCount; ++ltex)
		{
			aiString aiPath;
			pMaterial->GetTexture(uiType, ltex, &aiPath);
			std::string strPath = aiPath.C_Str();

			UINT uiTexType = lambda_type(uiType);
			CString strTex = CStringConverter::STR2CSTR(strPath);

			if (pModuleTexture->ExistTexture(uiTexType, (strFilePath + strTex)))
				continue;

			CEntityTexture tTexture;
			tTexture.dbKey = pModuleTexture->GetNewKey();
			tTexture.uiType = uiTexType;
			tTexture.strPath = strFilePath;
			tTexture.strTexture = strTex;

			auto itrTexture = pModuleTexture->InsertNU(tTexture);
			if (!ITR_IS_VALID(itrTexture))
			{
				ASSERT(g_warning);
				continue;
			}

			aItr.push_back(itrTexture);
		}
	};
	for (unsigned int lmesh = 0; lmesh < pScene->mNumMeshes; ++lmesh)
	{
		auto pMesh = pScene->mMeshes[lmesh];

		std::vector<DITER> aItrNode;
		aItrNode.resize(pMesh->mNumVertices);
		for (unsigned int lvtx = 0; lvtx < pMesh->mNumVertices; ++lvtx)
		{
			CEntityNode tNode;
			tNode.dbKey = pModuleNode->GetNewKey();

			auto& tVertex = pMesh->mVertices[lvtx];
			tNode.aVertex.x = tVertex.x;
			tNode.aVertex.y = tVertex.y;
			tNode.aVertex.z = tVertex.z;

			auto& tNormal = pMesh->mNormals[lvtx];
			tNode.aNormal.x = tNormal.x;
			tNode.aNormal.y = tNormal.y;
			tNode.aNormal.z = tNormal.z;

			if (pMesh->mTextureCoords[0] != nullptr) // 
			{
				tNode.aTexCoord.x = pMesh->mTextureCoords[0][lvtx].x;
				tNode.aTexCoord.y = pMesh->mTextureCoords[0][lvtx].y;
			}
			else
			{
				ASSERT(g_warning);
			}

			auto& tTangent = pMesh->mTangents[lvtx];
			tNode.aTangent.x = tTangent.x;
			tNode.aTangent.y = tTangent.y;
			tNode.aTangent.z = tTangent.z;

			auto& tBitangent = pMesh->mBitangents[lvtx];
			tNode.aBitangent.x = tBitangent.x;
			tNode.aBitangent.y = tBitangent.y;
			tNode.aBitangent.z = tBitangent.z;

			auto itrNode = pModuleNode->InsertNU(tNode);
			if (!ITR_IS_VALID(itrNode))
			{
				ASSERT(g_warning);
				continue;
			}

			aItrNode[lvtx] = itrNode;
		}

		std::vector<DITER> aItrElem;
		for (unsigned int lface = 0; lface < pMesh->mNumFaces; ++lface)
		{
			auto& tFace = pMesh->mFaces[lface];
			for (unsigned int indx = 0; indx < tFace.mNumIndices; indx += 3)
			{
				if (!ITR_IS_VALID(aItrNode[tFace.mIndices[indx + 0]])
					|| !ITR_IS_VALID(aItrNode[tFace.mIndices[indx + 1]])
					|| !ITR_IS_VALID(aItrNode[tFace.mIndices[indx + 2]]))
					continue;

				CEntityElement tElem;
				tElem.dbKey = pModuleElement->GetNewKey();
				tElem.uiType = E_ELEMTYPE_TRI3; // Only Tri3
				tElem.aItrNode.push_back(aItrNode[tFace.mIndices[indx + 0]]);
				tElem.aItrNode.push_back(aItrNode[tFace.mIndices[indx + 1]]);
				tElem.aItrNode.push_back(aItrNode[tFace.mIndices[indx + 2]]);

				auto itrElem = pModuleElement->InsertNU(tElem);
				if (!ITR_IS_VALID(itrElem))
				{
					ASSERT(g_warning);
					continue;
				}

				aItrElem.push_back(itrElem);
			}
		}

		std::vector<DITER> aItrTexture;
		auto pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
		for (auto uiType = 0; uiType < aiTextureType_UNKNOWN; ++uiType)
		{
			lambda_material(pMaterial, (aiTextureType)uiType, aItrTexture);
		}

		CEntityMesh tMesh;
		tMesh.dbKey = pModuleMesh->GetNewKey();
		tMesh.aItrNode = aItrNode;
		tMesh.aItrElement = aItrElem;
		tMesh.aItrTexture = aItrTexture;

		auto itrMesh = pModuleMesh->InsertNU(tMesh);
		if (!ITR_IS_VALID(itrMesh))
		{
			ASSERT(g_warning);
			continue;
		}
	}

	return pPackage->Commit();
}
