#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Nocturnal
{
	class NOCTURNAL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

	private:
		std::unique_ptr<Window> WindowInstance;
		bool ApplicationIsRunning = true;
	};


	//To be defined in client
	Application* CreateApplication();
}


