#include "NocturnalPrecompiledHeaders.h"
#include "Camera.h"


#include "Renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
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

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		//Converting from screen to clip space
		return glm::perspective(glm::radians(mFieldOfView),
			mAspectRatio, mNearClipPlane, mFarClipPlane);
	}

	void Camera::ProcessKeyInput(const CameraMoveDirection moveDirection, const float deltaTime)
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

	void Camera::ProcessMouseMovement(const float mouseX, const float mouseY, const bool constrainPitch)
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

	float Camera::CalculateFov(const float yScrollDelta)
	{
		mFieldOfView -= yScrollDelta;
		if (mFieldOfView < mMinFov)
			mFieldOfView = mMinFov;
		if (mFieldOfView > mMaxFov)
			mFieldOfView = mMaxFov;
		
		return mFieldOfView;
	}

	void Camera::CalculateAspectRatio(const float width, const float height)
	{
		mAspectRatio = width / height;
	}
}
