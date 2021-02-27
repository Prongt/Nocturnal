#pragma once
#include "glm/glm.hpp"

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
		float _Pitch = 0.0f;
		float _Yaw = -90.0f;
		float _LastMouseX = 0;
		float _LastMouseY = 0;
		float _MovementSpeed = 2.5f;
		float _MouseSensitivity = 0.1f;

		bool _isFirstInput = true;
		float _FieldOfView = 45.0f;

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

		void ProcessKeyInput(CameraMoveDirection moveDirection, float deltaTime);

		void ProcessMouseMovement(float mouseX, float mouseY, bool constrainPitch = true);
		float CalculateFov(float yScrollDelta);
	};
}