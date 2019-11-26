#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityNode : public CEntityData
{
public:
	CEntityNode();
	virtual ~CEntityNode();

public:
	virtual const DTYPE GetType() const override;
	virtual const DKEY GetKey() const override;

public:
	DKEY dbKey;
	
	glm::vec3 aVertex;
	glm::vec3 aNormal;
	glm::vec2 aTexCoord;
	glm::vec3 aTangent;
	glm::vec3 aBitangent;

};

#include "HeaderPost.h"