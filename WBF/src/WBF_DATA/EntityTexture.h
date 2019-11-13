#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class CEntityTexture : public CEntityData
{
public:
	CEntityTexture();
	virtual ~CEntityTexture();

	// CEntityData을(를) 통해 상속됨
	virtual const DTYPE GetType() const override;
	virtual const DKEY GetKey() const override;

public:
	DKEY dbKey;

};

#include "HeaderPost.h"

