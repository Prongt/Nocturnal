#include "NocturnalPrecompiledHeaders.h"
#include "Application.h"

#include "Nocturnal/Log.h"
#include "glad/glad.h"

namespace Nocturnal
{

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::ApplicationInstance = nullptr;
	
	Application::Application()
	{
		NOC_CORE_ASSERT(!ApplicationInstance, "Application instance already exists");
		ApplicationInstance = this;
		WindowInstance = std::unique_ptr<Window>(Window::Create());
		WindowInstance->SetEventCallback(BIND_EVENT_FUNCTION(OnWindowEvent));
	}

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
			
			WindowInstance->OnUpdate();
		}
	}

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));

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

