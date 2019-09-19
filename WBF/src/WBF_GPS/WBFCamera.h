#pragma once

#ifndef WBF_CAMERA
#define WBF_CAMERA

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

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
	void OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime);
	void OnMouseMove(float xoffset, float yoffset, BOOL bConstrainPitch = TRUE);

protected:
	void UpdateCameraVectors();

protected:
	glm::vec3 m_vPosition;
	glm::vec3 m_vWorldUp;
	glm::vec3 m_vFront;
	glm::vec3 m_vUp;
	glm::vec3 m_vRight;

	float m_fYaw;
	float m_fPitch;
	float m_fMovementSpeed;
	float m_fMouseSensitivity;
};

#include "HeaderPost.h"

#endif // !WBF_CAMERA