#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"

#include "WBFGraphicDef.h"
#include "ModelDefine.h"
#include "ModelFactory.h"
#include "HeaderPre.h"

namespace opt
{
	class IWBFOption;
}

class CShader;
class CModelManager;
class __MY_EXT_CLASS__ CModelData : public CFactoryObjectBase
{
public:
	CModelData();
	virtual ~CModelData();

public:
	virtual void Release() = 0;
	virtual void Build() = 0;
	virtual void Draw(CShader* pShader) = 0;


//
//
//public: // Update Flag
//	virtual UINT GetType() override { ASSERT(g_warning); return 0; }
//	virtual void InitFlag() { m_uiFlag = MODEL_UNKNOWN; }
//	virtual void SetFlag(UINT uiFlag) { m_uiFlag |= uiFlag; }
//	virtual UINT GetFlag() { return m_uiFlag; }
//
//public:
//	virtual opt::IWBFOption* GetOption() { ASSERT(g_warning); return nullptr; }
//
//
//	virtual BOOL IsValidModel() = 0;
//	virtual void GLInitialData() = 0;
//	virtual void GLCreateVBO() = 0;
//	virtual void GLAttachData() = 0;
//	virtual void GLBind() = 0;
//	virtual void GLDraw() = 0;
//	virtual void GLUnbind() = 0;
//	virtual void GLDelete() = 0;

public:
	void SetHelper(CModelManager* pModelMgr)
	{
		m_pModelMgr = pModelMgr;
	}

protected:
	UINT m_uiFlag;
	CModelManager* m_pModelMgr;
};

#include "HeaderPost.h"

#define DECLARE_MODEL(class_name)\
DECLARE_DYNCREATE(class_name);\

#define IMPLEMENT_MODEL(type, class_name)\
IMPLEMENT_DYNCREATE(class_name, CModelData);\
BOOL bReg##class_name = CModelFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));
