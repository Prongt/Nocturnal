#pragma once

#include "Core.h"
#include "Layer.h"
#include "Nocturnal/LayerStack.h"
#include "Nocturnal/Events/Event.h"
#include "Window.h"
#include "Nocturnal/Events/ApplicationEvent.h"

namespace Nocturnal
{
	class ImGuiLayer;

	class NOCTURNAL_API Application
	{
	private:
		
		bool ApplicationIsRunning = true;
		LayerStack LayerStack;
		std::unique_ptr<Window> WindowInstance;
		//std::unique_ptr<ImGuiLayer> ImGuiLayerInstance;
		ImGuiLayer* ImGuiLayerInstance;
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

	private:
		
	};


	//To be defined in client
	Application* CreateApplication();
}


