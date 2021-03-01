#include "NocturnalPrecompiledHeaders.h"
#include "WindowsWindow.h"

#include "Nocturnal/Events/ApplicationEvent.h"
#include "Nocturnal/Events/MouseEvent.h"
#include "Nocturnal/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

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
		mWindowInstanceData.Title = props.Title;
		mWindowInstanceData.Width = props.Width;
		mWindowInstanceData.Height = props.Height;

		

		NOC_CORE_TRACE("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!GlfwHasInitialized)
		{
			const int success = glfwInit();
			NOC_CORE_ASSERT(success, "Could not intialize GLFW!");

			GlfwHasInitialized = true;
		}

		mWindowInstance = glfwCreateWindow(static_cast<int>(mWindowInstanceData.Width), 
			static_cast<int>(mWindowInstanceData.Height), 
			mWindowInstanceData.Title.c_str(), nullptr, nullptr);

		mRenderingContextInstance = new OpenGLContext(mWindowInstance);
		
		mRenderingContextInstance->Init();
		
		
		
		glfwSetWindowUserPointer(mWindowInstance, &mWindowInstanceData);
		SetVSync(true);

		// Setting up GLFW event callbacks
		glfwSetWindowSizeCallback(mWindowInstance, 
			[](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowResizeEvent event(width, height);

			data.Width = width;
			data.Height = height;
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(mWindowInstance, [](GLFWwindow* window)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(mWindowInstance, [](GLFWwindow* window, const int key, const int scanCode, const int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch(action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key);
					data.EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyHeldEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			default: 
				NOC_CORE_ERROR("GLFW key callback not defined! Define the callback in {0}", __func__);
			}
		});

		glfwSetCharCallback(mWindowInstance, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			KeyTypedEvent event(static_cast<int>(keycode));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(mWindowInstance, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonDownEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonUpEvent event(button);
				data.EventCallback(event);
				break;
			}
			default: 
				NOC_CORE_ERROR("GLFW mouse callback not defined! Define the callback in {0}", __func__);
			}
		});

		glfwSetScrollCallback(mWindowInstance, [](GLFWwindow* window, const double scrollXOffset, const double scrollYOffset)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(scrollXOffset, scrollYOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(mWindowInstance, [](GLFWwindow* window, const double mouseXPosition, const double mouseYPosition)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent event(mouseXPosition, mouseYPosition);
			data.EventCallback(event);
		});

		
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(mWindowInstance);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		mRenderingContextInstance->SwapBuffers();
	}

	void WindowsWindow::SetVSync(const bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		mWindowInstanceData.VSyncIsEnabled = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const
	{
		return mWindowInstanceData.VSyncIsEnabled;
	}
}
