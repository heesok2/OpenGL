#pragma once

#include "WBFShaderManager.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFDocBase : public CDocument
{
public:
	CWBFDocBase();
	virtual ~CWBFDocBase();

public:
	virtual CWBFShaderManager* GetShaderManager() { return &m_ShaderMgr; }

private:
	DECLARE_MESSAGE_MAP();

protected:
	CWBFShaderManager m_ShaderMgr;
};

#include "HeaderPost.h"
