#include "stdafx.h"
#include "GLCtrlView.h"
#include "ShaderDefine.h"

#include "..\WBF_LIB\NotifyDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGLCtrlView::CGLCtrlView()
{
	m_uiScreenVAO = 0;
	m_uiScreenVBO = 0;
}

CGLCtrlView::~CGLCtrlView()
{
}

BEGIN_MESSAGE_MAP(CGLCtrlView, CGLView)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CGLCtrlView::OnDraw(CDC* pDC)
{
	// Model FrameBuffer 에 그림을 화면 ScreenBuffer에 그린다.
	BeginwglCurrent();
	{
		if (glIsVertexArray(m_uiScreenVAO))
		{
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			m_FrameBufferManager.GLBindBuffer(E_FBO_SCREEN);
			{
				auto Shader = m_ShaderManager.GetShader(E_SHADER_SCREEN);

				glDisable(GL_DEPTH_TEST);
				glClearColor(0.f, 0.f, 0.f, 1.f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				Shader.GLBind();
				m_FrameBufferManager.GLBindColorTex2D(E_FBO_MODEL);
				{
					glBindVertexArray(m_uiScreenVAO);
					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);
				}
				m_FrameBufferManager.GLUnbindColorTex2D(E_FBO_MODEL);
				Shader.GLUnbind();
			}
			m_FrameBufferManager.GLUnbindBuffer(E_FBO_SCREEN);
			glPopAttrib();

			SwapBuffers();
		}
	}
	EndwglCurrent();
}

void CGLCtrlView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (pSender == this) return;

	auto eNotify = lHint;
	switch (eNotify)
	{
	case E_DOCUMENT_DB_UPDATE:
		{
			BeginwglCurrent();
			{
				m_ObjectBufferManager.GLBuildObjectBuffer(0);
				m_RendererManager.GLBuildRenderer(0);
			}
			EndwglCurrent();
		}
		break;
	case E_DOCUMENT_CLOSE:
		{
			BeginwglCurrent();
			{
				m_ObjectBufferManager.GLDeleteObjectBuffer();
				m_RendererManager.GLDeleteRenderer();
				m_FrameBufferManager.GLDeleteBuffer();

				glDeleteBuffers(1, &m_uiScreenVBO);
				glDeleteVertexArrays(1, &m_uiScreenVAO);
			}
			EndwglCurrent();
		}
		break;
	}

	CGLView::OnUpdate(pSender, lHint, pHint);
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

glm::mat4 CGLCtrlView::GetModelViewProjectionMatrix()
{
	return m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix();
}

void CGLCtrlView::GLBindFrameBuffer(UINT uiType)
{
	m_FrameBufferManager.GLBindBuffer(uiType);
}

void CGLCtrlView::GLUnbindFrameBuffer(UINT uiType)
{
	m_FrameBufferManager.GLUnbindBuffer(uiType);
}

void CGLCtrlView::GLCreateScreen()
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
   // positions   // texCoords
   -1.0f,  1.0f,  0.0f, 1.0f,
   -1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

   -1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
	};

	m_ShaderManager.GLCreateShader(E_SHADER_SCREEN);
	auto ShaderScreen = m_ShaderManager.GetShader(E_SHADER_SCREEN);
	
	glGenVertexArrays(1, &m_uiScreenVAO);
	glGenBuffers(1, &m_uiScreenVBO);

	glBindVertexArray(m_uiScreenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiScreenVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
		
		ShaderScreen.GLSetInt("ScreenTex2D", 0);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CGLCtrlView::GLPrepareScene()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf((float*)&m_Camera.GetProjectionMatrix());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float*)&m_Camera.GetViewMatrix());
}

int CGLCtrlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGLView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ObjectBufferManager.InitialData(this);
	m_ObjectBufferManager.CreateObjectBuffer();

	m_RendererManager.InitialData(this);
	m_RendererManager.CreateRenderer();

	BeginwglCurrent();
	{
		m_ShaderManager.GLCreateAllShader();
		m_FrameBufferManager.GLCreateBuffer();

		GLCreateScreen();
	}
	EndwglCurrent();

	return 0;
}

void CGLCtrlView::OnSize(UINT nType, int cx, int cy)
{
	CGLView::OnSize(nType, cx, cy);

	CRect rect;
	rect.left = rect.bottom = 0;
	rect.right = cx;
	rect.top = cy;
	m_Camera.SetViewSize(rect);

	BeginwglCurrent();
	{
		m_FrameBufferManager.GLResizeBuffer(cx, cy);
	}
	EndwglCurrent();
}

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

