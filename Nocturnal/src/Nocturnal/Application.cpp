#include "NocturnalPrecompiledHeaders.h"
#include "Application.h"

#include "Time.h"
#include "ImGui/ImGuiLayer.h"
#include "Nocturnal/Log.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"


namespace Nocturnal
{
	Application* Application::sApplicationInstance = nullptr;
	
	
	Application::Application()
	{
		NOC_CORE_ASSERT(!sApplicationInstance, "Application instance already exists");
		sApplicationInstance = this;
		mWindowInstance = std::unique_ptr<Window>(Window::Create());
		mWindowInstance->SetEventCallback(NOC_BIND_EVENT_FUNCTION(Application::OnWindowEvent));

		mImGuiLayerInstance = new ImGuiLayer();
		PushOverlay(mImGuiLayerInstance);
	}
	

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
	}


	void Application::PushOverlay(Layer* overlay)
	{
		mLayerStack.PushOverlay(overlay);
	}


	void Application::Run()
	{
		while (mApplicationIsRunning)
		{
			Time::CalculateDeltaTime(RenderCommand::GetTime());
			
			for (Layer* layer : mLayerStack)
				layer->OnUpdate(Time::GetDeltaTime());

			mImGuiLayerInstance->Begin();

			for (Layer* layer : mLayerStack)
				layer->OnImGuiRender();
			
			mImGuiLayerInstance->End();
			mWindowInstance->OnUpdate();
		}
	}

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(NOC_BIND_EVENT_FUNCTION(Application::OnWindowClose));
		
		//Goes through the layer stack and sends events
		for (auto layerIterator = mLayerStack.end(); layerIterator != mLayerStack.begin();)
		{
			(*--layerIterator)->OnEvent(event);
			if (event.EventHasBeenHandled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		mApplicationIsRunning = false;
		return true;
	}
}

