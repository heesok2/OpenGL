#include "stdafx.h"
#include "FrameBufferManager.h"
#include "FrameBuffer.h"

CFrameBufferManager::CFrameBufferManager()
{
	memset(m_aFBO, 0, sizeof(m_aFBO));
}

CFrameBufferManager::~CFrameBufferManager()
{
}

void CFrameBufferManager::GLCreateBuffer(UINT uiType)
{
	m_aFBO[uiType] = new CFrameBuffer;

	switch (uiType)
	{
	case E_FBO_SCREEN: break; // Unknown
	default:
		{
			int aViewport[4] = {0};
			glGetIntegerv(GL_VIEWPORT, aViewport);

			auto width = aViewport[2] - aViewport[0];
			auto height = aViewport[3] - aViewport[1];

			m_aFBO[uiType]->GLGeneralFrameBuffer();
			m_aFBO[uiType]->GLBind();
			{
				if (!m_aFBO[uiType]->GLAttachColorTexture2D(GL_COLOR_ATTACHMENT0, width, height) ||
					!m_aFBO[uiType]->GLAttachDepthStencilRender(width, height) ||
					!m_aFBO[uiType]->IsValidFrameBuffer())
				{
					m_aFBO[uiType]->GLDeleteColorTexture2D();
					m_aFBO[uiType]->GLDeleteDepthStencilRender();
					m_aFBO[uiType]->GLDeleteFrameBuffer();
				}
			}
			m_aFBO[uiType]->GLUnbind();
		}
		break;
	}
}

void CFrameBufferManager::GLDeleteBuffer()
{
	for (auto indx = 0; indx < E_FBO_NUM; ++indx)
	{
		_SAFE_DELETE(m_aFBO[indx]);
	}
}

void CFrameBufferManager::GLBindBuffer(UINT uiType)
{
	m_aFBO[uiType]->GLBind();
}

void CFrameBufferManager::GLUnbindBuffer(UINT uiType)
{
	m_aFBO[uiType]->GLUnbind();
}