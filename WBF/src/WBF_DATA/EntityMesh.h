#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityMesh : public CEntityData
{
public:
	CEntityMesh();
	virtual ~CEntityMesh();

public:
	virtual const DTYPE GetType() const override;
	virtual const DKEY GetKey() const override;

public:
	DKEY dbKey;

	std::vector<DITER> aItrMesh;
	std::vector<DITER> aItrNode;
	std::vector<DITER> aItrElement;
	std::vector<DITER> aItrTexture;

};

#include "HeaderPost.h"