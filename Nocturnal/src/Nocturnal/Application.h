#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Nocturnal
{
	class NOCTURNAL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnWindowEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *ApplicationInstance; }
		inline Window& GetWindow() { return *WindowInstance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		
		std::unique_ptr<Window> WindowInstance;
		bool ApplicationIsRunning = true;

		LayerStack LayerStack;

	private:
		static Application* ApplicationInstance;
	};


	//To be defined in client
	Application* CreateApplication();
}


