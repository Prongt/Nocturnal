#pragma once

#include "Core.h"

namespace Nocturnal
{
	class NOCTURNAL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};


	//To be defined in client
	Application* CreateApplication();
}


