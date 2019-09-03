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
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_ERASEBKGND()
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

void CWBFViewGL::InitializePalette()
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

	// Make the rendering context current, perform initialization, then
	// deselect it
	BeginwglCurrent();

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		AfxMessageBox(_T("GLEW is not initialized!"));
	}
	
	// Create the palette if needed
	InitializePalette();

	// Default 
	glClearColor(1.f, 0.f, 0.f, 1.f);
	
	EndwglCurrent();

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

BOOL CWBFViewGL::OnQueryNewPalette()
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

	return CView::OnQueryNewPalette();
}


void CWBFViewGL::OnPaletteChanged(CWnd* pFocusWnd)
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

	CView::OnPaletteChanged(pFocusWnd);
}


BOOL CWBFViewGL::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
