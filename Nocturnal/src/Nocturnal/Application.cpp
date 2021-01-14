#include "NocturnalPrecompiledHeaders.h"
#include "Application.h"
#include "Input.h"
#include "Events/KeyEvent.h"
#include "Nocturnal/Log.h"
#include "glad/glad.h"
#include "ImGui/ImGuiLayer.h"

namespace Nocturnal
{

	
	
	Application::Application()
	{
		NOC_CORE_ASSERT(!ApplicationInstance, "Application instance already exists");
		ApplicationInstance = this;
		WindowInstance = std::unique_ptr<Window>(Window::Create());
		WindowInstance->SetEventCallback(NOC_BIND_EVENT_FUNCTION(Application::OnWindowEvent));

		ImGuiLayerInstance = new ImGuiLayer();
		PushOverlay(ImGuiLayerInstance);
	}
	Application* Application::ApplicationInstance = nullptr;

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		LayerStack.PushLayer(layer);
		layer->OnAttach();
	}


	void Application::PushOverlay(Layer* overlay)
	{
		LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}


	void Application::Run()
	{
		while (ApplicationIsRunning)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : LayerStack)
				layer->OnUpdate();

			ImGuiLayerInstance->Begin();

			for (Layer* layer : LayerStack)
				layer->OnImGuiRender();
			
			ImGuiLayerInstance->End();
			WindowInstance->OnUpdate();
		}
	}

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(NOC_BIND_EVENT_FUNCTION(Application::OnWindowClose));

		//Input::SetEvent(&event);
		
		//Goes through the layer stack and sends events
		for (auto layerIterator = LayerStack.end(); layerIterator != LayerStack.begin();)
		{
			(*--layerIterator)->OnEvent(event);
			if (event.EventHasBeenHandled){}
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		ApplicationIsRunning = false;
		return true;
	}
}

