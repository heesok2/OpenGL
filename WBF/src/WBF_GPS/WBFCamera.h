#pragma once

#ifndef WBF_CAMERA
#define WBF_CAMERA

#include "HeaderPre.h"

enum E_CAMERA_MOVEMENT
{
	E_CAMERA_FORWARD = 0,
	E_CAMERA_BACKWARD,
	E_CAMERA_LEFT,
	E_CAMERA_RIGHT,
	E_CAMERA_NUM
};

class __MY_EXT_CLASS__ CWBFCamera
{
public:
	CWBFCamera();
	virtual ~CWBFCamera();

public:
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
		
	void SetCameraPosition(glm::vec3& vPosition);
	void SetMousePosition(CPoint& point);
	void SetViewSize(CRect& rect);

	void OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime);
	void OnMouseMove(CPoint point, BOOL bConstrainPitch = TRUE);

protected:
	void UpdateCameraVectors();

protected:
	CRect m_ViewRect; 
	CPoint m_MousePoint; // Mouse Move

	glm::vec3 m_vPosition;
	glm::vec3 m_vFront;
	glm::vec3 m_vWorldUp;

	glm::vec3 m_vUp;
	glm::vec3 m_vRight;

	float m_fYaw;
	float m_fPitch;
	float m_fMovementSpeed;
	float m_fMouseSensitivity;
};

#include "HeaderPost.h"

#endif // !WBF_CAMERA