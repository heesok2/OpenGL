#pragma once

#include "GLView.h"
#include "Camera.h"
#include "FrameBufferManager.h"
#include "ShaderManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CGLCtrlView : public CGLView
{
public:
	CGLCtrlView();
	virtual ~CGLCtrlView();

public:
	virtual void OnDraw(CDC* /*pDC*/);

public:
	CShaderManager* GetShaderManager() { return &m_ShaderManager; }
	CFrameBufferManager* GetFrameBufferManager() { return &m_FrameBufferManager; }

	glm::vec3 GetEyePosition();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

protected:
	void GLBindFrameBuffer(UINT uiType);
	void GLUnbindFrameBuffer(UINT uiType);
	void GLCreateScreen();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP();

protected:
	CCamera m_Camera;

	CFrameBufferManager m_FrameBufferManager;
	CShaderManager m_ShaderManager;
	UINT m_uiScreenVAO;
	UINT m_uiScreenVBO;
};

#include "HeaderPost.h"