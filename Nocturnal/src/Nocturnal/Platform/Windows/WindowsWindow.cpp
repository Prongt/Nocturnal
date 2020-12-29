#include "NocturnalPrecompiledHeaders.h"
#include "WindowsWindow.h"

namespace Nocturnal
{
	static bool GlfwHasInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
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
		glfwSetWindowUserPointer(WindowInstance, &WindowInstanceData);
		SetVSync(true);
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