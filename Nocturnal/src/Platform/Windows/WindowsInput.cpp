#include "NocturnalPrecompiledHeaders.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Nocturnal/Application.h"

namespace Nocturnal
{
	Input* Input::Instance = new WindowsInput();
	
	auto* WindowsInput::GetGLFWWindow()
	{
		return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	}

	bool WindowsInput::IsKeyDownImplementation(const int keycode)
	{
		const auto keyState = glfwGetKey(GetGLFWWindow(), keycode);
		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseDownImplementation(const int button)
	{
		const auto buttonState = glfwGetMouseButton(GetGLFWWindow(), button);
		return buttonState == GLFW_PRESS;
	}

	std::tuple<float, float> WindowsInput::GetMousePositionImplementation()
	{
		double mouseX, mouseY;
		glfwGetCursorPos(GetGLFWWindow(), &mouseX, &mouseY);
		return std::tuple<float, float>(static_cast<float>(mouseX), static_cast<float>(mouseY));
	}

	float WindowsInput::GetMouseXImplementation()
	{
		auto [mouseX, mouseY] = GetMousePositionImplementation();
		return mouseX;
	}

	float WindowsInput::GetMouseYImplementation()
	{
		auto [mouseX, mouseY] = GetMousePositionImplementation();
		return mouseY;
	}
}
