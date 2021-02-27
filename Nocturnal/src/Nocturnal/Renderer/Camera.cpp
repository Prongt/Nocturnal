#include "NocturnalPrecompiledHeaders.h"
#include "Camera.h"

#include "glm/ext/matrix_transform.hpp"

namespace Nocturnal
{
	void Camera::RecalculateCameraVectors()
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
		forward.y = sin(glm::radians(_Pitch));
		forward.z = sin(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
		ForwardAxis = glm::normalize(forward);

		RightAxis = glm::normalize(glm::cross(ForwardAxis, WorldUpAxis));  
		UpAxis = glm::normalize(glm::cross(RightAxis, ForwardAxis));
		
	}

	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float speed, float mouseSensitivity,
	               float fov) : _Pitch(pitch), _Yaw(yaw), _MovementSpeed(speed),
	                            _MouseSensitivity(mouseSensitivity), Position(position), UpAxis(up), WorldUpAxis(up)
	{
		RecalculateCameraVectors();
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(Position, Position + ForwardAxis, UpAxis);
	}

	void Camera::ProcessKeyInput(CameraMoveDirection moveDirection, float deltaTime)
	{
		const float velocity = _MovementSpeed * deltaTime;
		switch (moveDirection)
		{
		case Forward: Position += ForwardAxis * velocity; break;
		case Back: Position -= ForwardAxis * velocity; break;
		case Left: Position -= RightAxis * velocity; break;
		case Right: Position += RightAxis * velocity; break;
		default: break;
		}
		RecalculateCameraVectors();
	}

	void Camera::ProcessMouseMovement(float mouseX, float mouseY, bool constrainPitch)
	{
		if (_isFirstInput)
		{
			_LastMouseX = mouseX;
			_LastMouseY = mouseY;
			_isFirstInput = false;
		}
		float xOffset = mouseX - _LastMouseX;
		float yOffset = _LastMouseY - mouseY;

		_LastMouseX = mouseX;
		_LastMouseY = mouseY;
		
		xOffset *= _MouseSensitivity;
		yOffset *= _MouseSensitivity;

		_Yaw += xOffset;
		_Pitch += yOffset;
		if (constrainPitch)
		{
			if (_Pitch > 89.0f)
				_Pitch = 89.0f;
			if (_Pitch < -89.0f)
				_Pitch = -89.0f;
		}
		RecalculateCameraVectors();
	}

	float Camera::CalculateFov(float yScrollDelta)
	{
		_FieldOfView -= yScrollDelta;
		if (_FieldOfView < 1.0f)
			_FieldOfView = 1.0f;
		if (_FieldOfView > 45.0f)
			_FieldOfView = 45.0f;
		
		return _FieldOfView;
	}
}
