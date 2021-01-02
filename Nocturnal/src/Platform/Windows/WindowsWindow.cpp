#include "NocturnalPrecompiledHeaders.h"
#include "WindowsWindow.h"

#include "Nocturnal/Events/ApplicationEvent.h"
#include "Nocturnal/Events/MouseEvent.h"
#include "Nocturnal/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Nocturnal
{
	static bool GlfwHasInitialized = false;

	static void GLFWErrorCallback(int error, const char* errorDescription)
	{
		NOC_CORE_ERROR("GLFW Error ({0}): {1}", error, errorDescription);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		WindowInstanceData.Title = props.Title;
		WindowInstanceData.Width = props.Width;
		WindowInstanceData.Height = props.Height;

		NOC_CORE_TRACE("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!GlfwHasInitialized)
		{
			int success = glfwInit();
			NOC_CORE_ASSERT(success, "Could not intialize GLFW!");

			GlfwHasInitialized = true;
		}

		WindowInstance = glfwCreateWindow(static_cast<int>(WindowInstanceData.Width), 
			static_cast<int>(WindowInstanceData.Height), 
			WindowInstanceData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(WindowInstance);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NOC_CORE_ASSERT(status, "Failed to initialize GLAD");
		
		glfwSetWindowUserPointer(WindowInstance, &WindowInstanceData);
		SetVSync(true);

		// Setting up GLFW event callbacks
		glfwSetWindowSizeCallback(WindowInstance, 
			[](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowResizeEvent event(width, height);

			data.Width = width;
			data.Height = height;
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(WindowInstance, [](GLFWwindow* window)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(WindowInstance, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch(action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(WindowInstance, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(WindowInstance, [](GLFWwindow* window, double scrollXOffset, double scrollYOffset)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(scrollXOffset, scrollYOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(WindowInstance, [](GLFWwindow* window, double mouseXPosition, double mouseYPosition)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent event(mouseXPosition, mouseYPosition);
			data.EventCallback(event);
		});

		
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(WindowInstance);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(WindowInstance);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		WindowInstanceData.VSyncIsEnabled = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const
	{
		return WindowInstanceData.VSyncIsEnabled;
	}
}