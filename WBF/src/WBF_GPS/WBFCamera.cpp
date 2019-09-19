#include "stdafx.h"
#include "WBFCamera.h"

// Default camera values
const float g_YAW = -90.0f;
const float g_PITCH = 0.0f;
const float g_SPEED = 2.5f;
const float g_SENSITIVITY = 0.1f;
const float g_ZOOM = 45.0f;


CWBFCamera::CWBFCamera()
{
	m_vPosition = glm::vec3(0.f, 0.f, 0.f);
	m_vWorldUp = glm::vec3(0.f, 0.f, 0.f);

	m_vFront = glm::vec3(0.f, 0.f, 0.f);
	m_vUp = glm::vec3(0.f, 0.f, 0.f);
	m_vRight = glm::vec3(0.f, 0.f, 0.f);

	m_fYaw = g_YAW ;
	m_fPitch = g_PITCH;
	m_fMovementSpeed = g_SPEED;
	m_fMouseSensitivity = g_SENSITIVITY;
}

CWBFCamera::~CWBFCamera()
{
}

glm::mat4 CWBFCamera::GetViewMatrix()
{
	return glm::lookAt(m_vPosition, m_vPosition + m_vFront, m_vUp);
}

void CWBFCamera::OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime)
{
}

void CWBFCamera::OnMouseMove(float xoffset, float yoffset, BOOL bConstrainPitch)
{
}

void CWBFCamera::UpdateCameraVectors()
{
	glm::vec3 vFront;
	vFront.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	vFront.y = sin(glm::radians(m_fPitch));
	vFront.z = sin(glm::radians(m_fYaw)) * sin(glm::radians(m_fPitch));
	m_vFront = glm::normalize(vFront);

	m_vRight = glm::normalize(glm::cross(m_vFront, m_vWorldUp));
	m_vUp = glm::normalize(glm::cross(m_vRight, m_vFront));
}
