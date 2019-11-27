#pragma once

#include "..\WBF_LIB\EntityData.h"

#include "HeaderPre.h"

enum E_TEX_TYPE
{
	E_TEX_DIFFUSE = 0,

	E_TEX_NUM,
	E_TEX_UNKNOWN
};

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

	UINT uiType; // E_TEX_TYPE
	CString strPath;
	CString strTexture;
};

#include "HeaderPost.h"

