#include "NocturnalPrecompiledHeaders.h"
#include "Camera.h"

#include "glm/ext/matrix_transform.hpp"

namespace Nocturnal
{
	void Camera::RecalculateCameraVectors()
	{
		
		glm::vec3 forward;
		forward.x = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
		forward.y = glm::sin(glm::radians(mPitch));
		forward.z = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
		ForwardAxis = glm::normalize(forward);

		RightAxis = glm::normalize(glm::cross(ForwardAxis, WorldUpAxis));  
		UpAxis = glm::normalize(glm::cross(RightAxis, ForwardAxis));
		
	}

	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float speed, float mouseSensitivity,
	               float fov) : mPitch(pitch), mYaw(yaw), mMovementSpeed(speed),
	                            mMouseSensitivity(mouseSensitivity), Position(position), UpAxis(up), WorldUpAxis(up)
	{
		RecalculateCameraVectors();
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(Position, Position + ForwardAxis, UpAxis);
	}

	void Camera::ProcessKeyInput(CameraMoveDirection moveDirection, float deltaTime)
	{
		const float velocity = mMovementSpeed * deltaTime;
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
		if (mIsFirstInput)
		{
			mLastMouseX = mouseX;
			mLastMouseY = mouseY;
			mIsFirstInput = false;
		}
		float xOffset = mouseX - mLastMouseX;
		float yOffset = mLastMouseY - mouseY;

		mLastMouseX = mouseX;
		mLastMouseY = mouseY;
		
		xOffset *= mMouseSensitivity;
		yOffset *= mMouseSensitivity;

		mYaw += xOffset;
		mPitch += yOffset;
		if (constrainPitch)
		{
			if (mPitch > 89.0f)
				mPitch = 89.0f;
			if (mPitch < -89.0f)
				mPitch = -89.0f;
		}
		RecalculateCameraVectors();
	}

	float Camera::CalculateFov(float yScrollDelta)
	{
		mFieldOfView -= yScrollDelta;
		if (mFieldOfView < 1.0f)
			mFieldOfView = 1.0f;
		if (mFieldOfView > 45.0f)
			mFieldOfView = 45.0f;
		
		return mFieldOfView;
	}
}
