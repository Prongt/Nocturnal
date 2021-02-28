#include "NocturnalPrecompiledHeaders.h"
#include "Application.h"

#include "Time.h"
#include "Nocturnal/Log.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

namespace Nocturnal
{

	
	
	Application::Application()
	{
		NOC_CORE_ASSERT(!s_ApplicationInstance, "Application instance already exists");
		s_ApplicationInstance = this;
		_WindowInstance = std::unique_ptr<Window>(Window::Create());
		_WindowInstance->SetEventCallback(NOC_BIND_EVENT_FUNCTION(Application::OnWindowEvent));

		_ImGuiLayerInstance = new ImGuiLayer();
		PushOverlay(_ImGuiLayerInstance);
	}
	Application* Application::s_ApplicationInstance = nullptr;

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		_LayerStack.PushLayer(layer);
	}


	void Application::PushOverlay(Layer* overlay)
	{
		_LayerStack.PushOverlay(overlay);
	}


	void Application::Run()
	{
		while (_ApplicationIsRunning)
		{
			Time::CalculateDeltaTime(RenderCommand::GetTime());
			
			for (Layer* layer : _LayerStack)
				layer->OnUpdate(Time::GetDeltaTime());

			_ImGuiLayerInstance->Begin();

			for (Layer* layer : _LayerStack)
				layer->OnImGuiRender();
			
			_ImGuiLayerInstance->End();
			_WindowInstance->OnUpdate();
		}
	}

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(NOC_BIND_EVENT_FUNCTION(Application::OnWindowClose));
		
		//Goes through the layer stack and sends events
		for (auto layerIterator = _LayerStack.end(); layerIterator != _LayerStack.begin();)
		{
			(*--layerIterator)->OnEvent(event);
			if (event.EventHasBeenHandled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		_ApplicationIsRunning = false;
		return true;
	}
}

