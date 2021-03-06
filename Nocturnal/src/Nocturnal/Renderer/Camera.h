#pragma once
#include "glm/glm.hpp"
#include "Nocturnal/Events/ApplicationEvent.h"

namespace Nocturnal
{
	enum CameraMoveDirection
	{
		Forward,
		Back,
		Left,
		Right
	};
	class Camera
	{
	private:
		float mPitch = 0.0f;
		float mYaw = -90.0f;
		float mLastMouseX = 0;
		float mLastMouseY = 0;
		float mMovementSpeed = 2.5f;
		float mMouseSensitivity = 0.1f;

		bool mIsFirstInput = true;

		float mFieldOfView = 45.0f;
		float mMinFov = 10.0f;
		float mMaxFov = 45.0f;

		float mAspectRatio;
		float mNearClipPlane = 0.1f;
		float mFarClipPlane = 100.0f;


		void RecalculateCameraVectors();
	
	public:
		glm::vec3 Position;
		glm::vec3 ForwardAxis;
		glm::vec3 UpAxis;
		glm::vec3 RightAxis;
		glm::vec3 WorldUpAxis;

		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
			float yaw = -90.0f, float pitch = 0.0f, 
			float speed = 2.5f, float mouseSensitivity = 0.1f, 
			float fov = 45.0f);
		
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;

		void ProcessKeyInput(const CameraMoveDirection moveDirection, const float deltaTime);

		void ProcessMouseMovement(const float mouseX, const float mouseY, const bool constrainPitch = true);
		
		float CalculateFov(const float yScrollDelta);
		float GetFov() const { return mFieldOfView; }
		void SetFovConstraints(const float minFov, const float maxFov) { mMinFov = minFov; mMaxFov = maxFov; }
		void SetAspectRatio(const float width, const float height);
		float GetAspectRatio() const { return mAspectRatio; }
	};
}
