#include "stdafx.h"
#include "GLCtrlView.h"


CGLCtrlView::CGLCtrlView()
{
}


CGLCtrlView::~CGLCtrlView()
{
}

glm::vec3 CGLCtrlView::GetEyePosition()
{
	return m_Camera.GetEyePos();
}

glm::mat4 CGLCtrlView::GetViewMatrix()
{
	return m_Camera.GetViewMatrix();
}

glm::mat4 CGLCtrlView::GetProjectionMatrix()
{
	return m_Camera.GetProjectionMatrix();
}

BEGIN_MESSAGE_MAP(CGLCtrlView, CGLView)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CGLCtrlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	float fDelta = 1.f;
	switch (nChar)
	{
	case 'a':
	case 'A':
		{
			m_Camera.OnKeyboardDown(E_CAMERA_LEFT, fDelta);
		}
		break;
	case 's':
	case 'S':
		{
			m_Camera.OnKeyboardDown(E_CAMERA_BOTTOM, fDelta);
		}
		break;
	case 'd':
	case 'D':
		{
			m_Camera.OnKeyboardDown(E_CAMERA_RIGHT, fDelta);
		}
		break;
	case 'w':
	case 'W':
		{
			m_Camera.OnKeyboardDown(E_CAMERA_TOP, fDelta);
		}
		break;
	case 'q':
	case 'Q':
		{
			m_Camera.OnKeyboardDown(E_CAMERA_BACKWARD, fDelta);
		}
		break;

	case 'e':
	case 'E':
		{
			m_Camera.OnKeyboardDown(E_CAMERA_FORWARD, fDelta);
		}
		break;
	}

	Invalidate();

	CGLView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGLCtrlView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CGLView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGLCtrlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	auto pWnd = GetCapture();
	if (pWnd == nullptr)
	{
		auto pCapture = SetCapture();
		m_Camera.SetMousePosition(point);
	}

	CGLView::OnLButtonDown(nFlags, point);
}

void CGLCtrlView::OnLButtonUp(UINT nFlags, CPoint point)
{
	auto pWnd = GetCapture();
	if (pWnd == this)
	{
		ReleaseCapture();
	}

	CGLView::OnLButtonUp(nFlags, point);
}

void CGLCtrlView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		auto pWnd = GetCapture();
		if (pWnd == this)
		{
			m_Camera.OnMouseMove(point);
			Invalidate();
		}
	}

	CGLView::OnMouseMove(nFlags, point);
}

void CGLCtrlView::OnSize(UINT nType, int cx, int cy)
{
	CGLView::OnSize(nType, cx, cy);

	CRect rect;
	rect.left = rect.bottom = 0;
	rect.right = cx;
	rect.top = cy;

	m_Camera.SetViewSize(rect);
}