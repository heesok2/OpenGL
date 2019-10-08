#include "stdafx.h"
#include "GLView.h"
#include "WBFCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGLView::CGLView()
{
	m_Camera = nullptr;
}

CGLView::~CGLView()
{
}

BEGIN_MESSAGE_MAP(CGLView, CViewBase)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CGLView::BeginwglCurrent()
{
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
}

void CGLView::EndwglCurrent()
{
	VERIFY(wglMakeCurrent(NULL, NULL));
}

void CGLView::SwapBuffers()
{
	::SwapBuffers(m_hDC);
}

BOOL CGLView::GetViewMatrix(glm::mat4 & mat)
{
	if (m_Camera == nullptr)
		return FALSE;

	mat = m_Camera->GetViewMatrix();

	return TRUE;
}

BOOL CGLView::GetProjectionMatrix(glm::mat4 & mat)
{
	if (m_Camera == nullptr)
		return FALSE;

	mat = m_Camera->GetProjectionMatrix();

	return TRUE;
}

BOOL CGLView::GetCameraPos(glm::vec3 & CamPos)
{
	if (m_Camera == nullptr)
		return FALSE;

	CamPos = m_Camera->GetCameraPos();

	return TRUE;
}

void CGLView::InitializePalette()
{
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange, GreenRange, BlueRange;
	// Range for each color entry (7,7,and 3)

	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(m_hDC);
	DescribePixelFormat(m_hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if (!(pfd.dwFlags & PFD_NEED_PALETTE))
		return;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) - 1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) - 1;

	// Loop through all the palette entries
	for (i = 0; i < nColors; i++)
	{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double)pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char)NULL;
	}

	// Create the palette
	m_GLPalette.CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(m_hDC, (HPALETTE)m_GLPalette, FALSE);
	RealizePalette(m_hDC);

	// Free the memory used for the logical palette structure
	free(pPal);
}

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CViewBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	IninitialWGL();

	m_Camera = new CWBFCamera();
	//m_Camera->SetCameraPosition(glm::vec3(0.f, 0.f, 3.f));

	return 0;
}

void CGLView::IninitialWGL()
{
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

	// Make the rendering context current, perform initialization, then
	// deselect it
	BeginwglCurrent();
	{

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			AfxMessageBox(_T("GLEW is not initialized!"));
		}

		// Create the palette if needed
		InitializePalette();

		// Default 
		glClearColor(0.f, 0.f, 0.f, 1.f);
	}
	EndwglCurrent();
}

void CGLView::OnDestroy()
{
	ReleaseWGL();

	_SAFE_DELETE(m_Camera);

	CViewBase::OnDestroy();
}

void CGLView::ReleaseWGL()
{
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}

void CGLView::OnSize(UINT nType, int cx, int cy)
{
	CViewBase::OnSize(nType, cx, cy);
	
	BeginwglCurrent();
	{
		glViewport(0, 0, cx, cy);
	}
	EndwglCurrent();

	if (m_Camera != nullptr)
	{
		CRect rect;
		rect.left = rect.bottom = 0;
		rect.right = cx;
		rect.top = cy;

		m_Camera->SetViewSize(rect);
	}
}

BOOL CGLView::OnQueryNewPalette()
{
	// If the palette was created.
	if ((HPALETTE)m_GLPalette)
	{
		int nRet;

		// Selects the palette into the current device context
		SelectPalette(m_hDC, (HPALETTE)m_GLPalette, FALSE);

		// Map entries from the currently selected palette to
		// the system palette.  The return value is the number 
		// of palette entries modified.
		nRet = RealizePalette(m_hDC);

		// Repaint, forces remap of palette in current window
		InvalidateRect(NULL, FALSE);

		return nRet;
	}

	return CViewBase::OnQueryNewPalette();
}


void CGLView::OnPaletteChanged(CWnd* pFocusWnd)
{
	if (((HPALETTE)m_GLPalette != NULL) && (pFocusWnd != this))
	{
		// Select the palette into the device context
		SelectPalette(m_hDC, (HPALETTE)m_GLPalette, FALSE);

		// Map entries to system palette
		RealizePalette(m_hDC);

		// Remap the current colors to the newly realized palette
		UpdateColors(m_hDC);
		return;
	}

	CViewBase::OnPaletteChanged(pFocusWnd);
}


BOOL CGLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CWBFViewBase::OnEraseBkgnd(pDC);
}


void CGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	float fDelta = 1.f;
	switch (nChar)
	{
	case 'a':
	case 'A':
		{
			m_Camera->OnKeyboardDown(E_CAMERA_LEFT, fDelta);
		}
		break;
	case 's':
	case 'S':
		{
			m_Camera->OnKeyboardDown(E_CAMERA_BACKWARD, fDelta);
		}
		break;
	case 'd':
	case 'D':
		{
			m_Camera->OnKeyboardDown(E_CAMERA_RIGHT, fDelta);
		}
		break;
	case 'w':
	case 'W':
		{
			m_Camera->OnKeyboardDown(E_CAMERA_FORWARD, fDelta);
		}
		break;
	}

	Invalidate();

	CViewBase::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGLView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CViewBase::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		auto pWnd = GetCapture();
		if (pWnd == this)
		{
			if (m_Camera != nullptr)
				m_Camera->OnMouseMove(point);

			Invalidate();
		}
	}

	CViewBase::OnMouseMove(nFlags, point);
}


void CGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	auto pWnd = GetCapture();
	if (pWnd == nullptr)
	{
		auto pCapture = SetCapture();
		if (m_Camera != nullptr)
			m_Camera->SetMousePosition(point);
	}

	CViewBase::OnLButtonDown(nFlags, point);
}


void CGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	auto pWnd = GetCapture();
	if (pWnd == this)
	{
		ReleaseCapture();
	}

	CViewBase::OnLButtonUp(nFlags, point);
}