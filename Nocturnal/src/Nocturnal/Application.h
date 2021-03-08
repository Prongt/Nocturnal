#pragma once

#include "Core.h"
#include "Layer.h"
#include "Window.h"
#include "Nocturnal/LayerStack.h"
#include "Nocturnal/Events/ApplicationEvent.h"
#include "Nocturnal/Events/Event.h"
#include "Renderer/VertexArray.h"

namespace Nocturnal
{
	class ImGuiLayer;

	class NOCTURNAL_API Application
	{
	private:
		bool mApplicationIsRunning = true;
		LayerStack mLayerStack;
		std::unique_ptr<Window> mWindowInstance;
		ImGuiLayer* mImGuiLayerInstance;
		static Application* sApplicationInstance;

		bool OnWindowClose(WindowCloseEvent& event);
	public:
		
		Application();
		
		virtual ~Application();
		void Run();

		void OnWindowEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *sApplicationInstance; }
		Window& GetWindow() const { return *mWindowInstance; }

		void CloseApplication() { mApplicationIsRunning = false; }
	};


	//To be defined in client
	Application* CreateApplication();
}


