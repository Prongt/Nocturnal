#pragma once

#include "Core.h"
#include "Layer.h"
#include "Nocturnal/LayerStack.h"
#include "Nocturnal/Events/Event.h"
#include "Window.h"
#include "Nocturnal/Events/ApplicationEvent.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/VertexArray.h"

namespace Nocturnal
{
	class ImGuiLayer;

	class NOCTURNAL_API Application
	{
	private:
		bool _ApplicationIsRunning = true;
		LayerStack _LayerStack;
		std::unique_ptr<Window> _WindowInstance;
		ImGuiLayer* _ImGuiLayerInstance;
		static Application* s_ApplicationInstance;
		
		bool OnWindowClose(WindowCloseEvent& event);
	public:
		
		Application();
		
		virtual ~Application();
		void Run();

		void OnWindowEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *s_ApplicationInstance; }
		Window& GetWindow() const { return *_WindowInstance; }

		void CloseApplication() { _ApplicationIsRunning = false; }
	};


	//To be defined in client
	Application* CreateApplication();
}


