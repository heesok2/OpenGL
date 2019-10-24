#pragma once

#include "HeaderPre.h"

enum E_FRAMEBUFFER_TYPE
{
	E_FBO_SCREEN = 0,
	E_FBO_MODEL,
	E_FBO_NUM
};

class CFrameBuffer;
class __MY_EXT_CLASS__ CFrameBufferManager
{
public:
	CFrameBufferManager();
	virtual ~CFrameBufferManager();

public:
	void GLCreateBuffer(UINT uiType);
	void GLDeleteBuffer();
	void GLBindBuffer(UINT uiType = E_FBO_SCREEN);
	void GLUnbindBuffer(UINT uiType = E_FBO_SCREEN);

protected:
	CFrameBuffer* m_aFBO[E_FBO_NUM];

};

#include "HeaderPost.h"