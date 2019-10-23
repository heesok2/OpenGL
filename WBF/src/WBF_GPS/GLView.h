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
	virtual void BeginwglCurrent() override;
	virtual void EndwglCurrent() override;
	virtual void SwapBuffers() override;

	virtual BOOL GetEyePosition(glm::vec3& CamPos) override;
	virtual BOOL GetViewMatrix(glm::mat4& mat) override;
	virtual BOOL GetProjectionMatrix(glm::mat4& mat) override;

protected:
	void CreateWGL();
	void ReleaseWGL();
	void CreateFBO();
	void ReleaseFBO();

	void InitialPalette();

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
	HDC m_hDC; // m_hWnd ÀÇ DC
	HGLRC m_hRC; // m_hDC ÀÇ RC
	CPalette m_GLPalette;
	CCamera* m_Camera;
};

#include "HeaderPost.h"