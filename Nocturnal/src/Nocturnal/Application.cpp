#include "NocturnalPrecompiledHeaders.h"
#include "Application.h"

#include "Nocturnal/Log.h"
#include <GLFW/glfw3.h>

namespace Nocturnal
{

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application::Application()
	{
		WindowInstance = std::unique_ptr<Window>(Window::Create());
		WindowInstance->SetEventCallback(BIND_EVENT_FUNCTION(OnWindowEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (ApplicationIsRunning)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			WindowInstance->OnUpdate();
		}
	}

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));

		NOC_CORE_TRACE("{0}", event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		ApplicationIsRunning = false;
		return true;
	}
}

