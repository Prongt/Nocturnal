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
	private:
		bool ApplicationIsRunning = true;
		LayerStack LayerStack;
		std::unique_ptr<Window> WindowInstance;

		static Application* ApplicationInstance;
		
		bool OnWindowClose(WindowCloseEvent& event);

	public:
		Application();
		virtual ~Application();
		void Run();

		void OnWindowEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *ApplicationInstance; }
		Window& GetWindow() const { return *WindowInstance; }
	};


	//To be defined in client
	Application* CreateApplication();
}


