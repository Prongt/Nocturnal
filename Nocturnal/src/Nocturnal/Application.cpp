#include "NocturnalPrecompiledHeaders.h"
#include "Application.h"

#include "Nocturnal/Log.h"
#include <GLFW/glfw3.h>

namespace Nocturnal
{

	Application::Application()
	{
		WindowInstance = std::unique_ptr<Window>(Window::Create());
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
}

