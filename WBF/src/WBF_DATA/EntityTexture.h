#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CEntityTexture : public CEntityData
{
public:
	CEntityTexture();
	virtual ~CEntityTexture();

public:
	virtual const DTYPE GetType() const override;
	virtual const DKEY GetKey() const override;

public:
	DKEY dbKey;

	UINT uiType; // aiTextureType
	CString strPath;
	CString strTexture;
};

#include "HeaderPost.h"

