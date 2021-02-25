#include "NocturnalPrecompiledHeaders.h"
#include "Application.h"
#include "Nocturnal/Log.h"
#include "glad/glad.h"
#include "ImGui/ImGuiLayer.h"

namespace Nocturnal
{

	
	
	Application::Application()
	{
		NOC_CORE_ASSERT(!_applicationInstance, "Application instance already exists");
		_applicationInstance = this;
		_windowInstance = std::unique_ptr<Window>(Window::Create());
		_windowInstance->SetEventCallback(NOC_BIND_EVENT_FUNCTION(Application::OnWindowEvent));

		_imGuiLayerInstance = new ImGuiLayer();
		PushOverlay(_imGuiLayerInstance);

		_vertexArray.reset(VertexArray::Create());

		//Vertices of the triangle
		//z is 0 as it is a 2d triangle 
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> _vertexBuffer;
		_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		const BufferLayout layout = {
			{ ShaderType::Float3, "a_Position"},
			{ ShaderType::Float4, "a_Color"}
		};
		_vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(_vertexBuffer);


		std::shared_ptr<IndexBuffer> _indexBuffer;
		uint32_t indices[3] = { 0, 1, 2 };
		_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		_vertexArray->AddIndexBuffer(_indexBuffer);


		_shader = std::make_unique<OpenGLShader>(_vertexShaderSource, _fragmentShaderSource);
	}
	Application* Application::_applicationInstance = nullptr;

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
	}


	void Application::PushOverlay(Layer* overlay)
	{
		_layerStack.PushOverlay(overlay);
	}


	void Application::Run()
	{
		while (_applicationIsRunning)
		{
			glClearColor(0.19f, 0.19f, 0.19f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			_shader->Bind();
			_vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);


			for (Layer* layer : _layerStack)
				layer->OnUpdate();

			_imGuiLayerInstance->Begin();

			for (Layer* layer : _layerStack)
				layer->OnImGuiRender();
			
			_imGuiLayerInstance->End();
			_windowInstance->OnUpdate();
		}
	}

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(NOC_BIND_EVENT_FUNCTION(Application::OnWindowClose));
		
		//Goes through the layer stack and sends events
		for (auto layerIterator = _layerStack.end(); layerIterator != _layerStack.begin();)
		{
			(*--layerIterator)->OnEvent(event);
			if (event.EventHasBeenHandled){}
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		_applicationIsRunning = false;
		return true;
	}
}

