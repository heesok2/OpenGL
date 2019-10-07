#include "stdafx.h"
#include "WBFCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Default camera values
const float g_YAW = -90.0f;
const float g_PITCH = 0.0f;
const float g_SPEED = 1.5f;
const float g_SENSITIVITY = 0.1f;
const float g_ZOOM = 45.0f;


CWBFCamera::CWBFCamera()
{
	m_vPosition = glm::vec3(0.f, 0.f, 0.f);
	m_vFront = glm::vec3(0.f, 0.f, -1.f);
	m_vWorldUp = glm::vec3(0.f, 1.f, 0.f);

	m_vUp = glm::vec3(0.f, 0.f, 0.f);
	m_vRight = glm::vec3(0.f, 0.f, 0.f);

	m_fYaw = g_YAW;
	m_fPitch = g_PITCH;
	m_fMovementSpeed = g_SPEED;
	m_fMouseSensitivity = g_SENSITIVITY;

	UpdateCameraVectors();
}

CWBFCamera::~CWBFCamera()
{
}

glm::mat4 CWBFCamera::GetViewMatrix()
{
	return glm::lookAt(m_vPosition, m_vPosition + m_vFront, m_vUp);
}

glm::mat4 CWBFCamera::GetProjectionMatrix()
{
	glm::mat4 proj(1.f);
	return glm::perspective(glm::radians(45.f), (float)(m_ViewRect.Width()) / (float)(m_ViewRect.Height()), 0.1f, 100.f);
}

void CWBFCamera::SetCameraPosition(glm::vec3& vPosition)
{
	m_vPosition = vPosition;
}

void CWBFCamera::SetMousePosition(CPoint& point)
{
	m_MousePoint = point;
}

void CWBFCamera::SetViewSize(CRect& rect)
{
	m_ViewRect = rect;
}

void CWBFCamera::OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime)
{
	auto fVelocity = m_fMovementSpeed * deltaTime;
	switch (eMovement)
	{
	case E_CAMERA_FORWARD:
		{
			m_vPosition += m_vFront * fVelocity;
		}
		break;
	case E_CAMERA_BACKWARD:
		{
			m_vPosition -= m_vFront * fVelocity;
		}
		break;
	case E_CAMERA_LEFT:
		{
			m_vPosition -= m_vRight * fVelocity;
		}
		break;
	case E_CAMERA_RIGHT:
		{
			m_vPosition += m_vRight * fVelocity;
		}
		break;
	}
}

void CWBFCamera::OnMouseMove(CPoint point, BOOL bConstrainPitch)
{
	auto MouseOffset = m_MousePoint - point;
	auto fOffsetX = (float)MouseOffset.cx * m_fMouseSensitivity;
	auto fOffsetY = (float)MouseOffset.cy * m_fMouseSensitivity;

	m_MousePoint = point;

	m_fYaw += fOffsetX;
	m_fPitch += -fOffsetY;

	if (bConstrainPitch)
	{
		if (m_fPitch > 89.f)
			m_fPitch = 89.f;
		if (m_fPitch < -89.f)
			m_fPitch = -89.f;
	}

	UpdateCameraVectors();
}

void CWBFCamera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	front.y = sin(glm::radians(m_fPitch));
	front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	m_vFront = glm::normalize(front);

	m_vRight = glm::normalize(glm::cross(m_vFront, m_vWorldUp));
	m_vUp = glm::normalize(glm::cross(m_vRight, m_vFront));
}
