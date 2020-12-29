#include "Application.h"

#include "Nocturnal/Events/ApplicationEvent.h"
#include "Nocturnal/Log.h"
namespace Nocturnal
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent resizeEvent(1280, 720);
		NOC_CORE_TRACE(resizeEvent);
		
		while (true)
		{
		}
	}
}

