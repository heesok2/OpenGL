#pragma once


#include "..\WBF_BASE\ViewBase.h"

#include "HeaderPre.h"

class CCamera;
class __MY_EXT_CLASS__ CGLView : public CViewBase
{
public:
	CGLView();
	virtual ~CGLView();
	

public:
	virtual BOOL GetViewMatrix(glm::mat4& mat);
	virtual BOOL GetProjectionMatrix(glm::mat4& mat);
	virtual BOOL GetCameraPos(glm::vec3& CamPos);// { ASSERT(g_warning); return FALSE; }

public:
	virtual void BeginwglCurrent() override;
	virtual void EndwglCurrent() override;
	virtual void SwapBuffers() override;

protected:
	void InitializePalette();
	void IninitialWGL();
	void ReleaseWGL();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP();

protected:
	HDC m_hDC;
	HGLRC m_hRC;

	CPalette m_GLPalette;	// Logical Palette
	CCamera* m_Camera;
};

#include "HeaderPost.h"