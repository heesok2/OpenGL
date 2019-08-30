#include "stdafx.h"
#include "WBFViewGL.h"

CWBFViewGL::CWBFViewGL()
{
}


CWBFViewGL::~CWBFViewGL()
{
}

BEGIN_MESSAGE_MAP(CWBFViewGL, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CWBFViewGL::BeginwglCurrent()
{
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
}

void CWBFViewGL::EndwglCurrent()
{
	VERIFY(wglMakeCurrent(NULL, NULL));
}

void CWBFViewGL::SwapBuffers()
{
	::SwapBuffers(m_hDC);
}

int CWBFViewGL::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_SWAP_EXCHANGE |
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		24,								// Want 24bit color 
		0,0,0,0,0,0,					// Not used to select mode
		0,0,							// Not used to select mode
		0,0,0,0,0,						// Not used to select mode
		32,								// Size of depth buffer
		1,								// Not used to select mode
		0,								// Not used to select mode
		PFD_MAIN_PLANE,					// Draw in main plane
		0,								// Not used to select mode
		0,0,0							// Not used to select mode
	};


	// Get the Device context
	m_hDC = ::GetDC(m_hWnd);

	// Choose a pixel format that best matches that described in pfd
	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);

	// Set the pixel format for the device context
	VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));

	// Create the rendering context
	m_hRC = wglCreateContext(m_hDC);

	return 0;
}

void CWBFViewGL::OnDestroy()
{
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);

	CView::OnDestroy();
}

void CWBFViewGL::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	BeginwglCurrent();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	auto dRat = (double)cx / (double)cy;
	glOrtho(-dRat, dRat, -1, 1, -1, 1);

	EndwglCurrent();
}