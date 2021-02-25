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
		bool _applicationIsRunning = true;
		LayerStack _layerStack;
		std::unique_ptr<Window> _windowInstance;
		ImGuiLayer* _imGuiLayerInstance;
		static Application* _applicationInstance;
		
		bool OnWindowClose(WindowCloseEvent& event);



		const std::string _vertexShaderSource = R"(#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;
		
			out vec3 v_position;
			out vec4 v_Color;
		
			void main()
			{
				v_Color = a_Color;
				v_position = a_Position;
				gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
			}
			)";

		const std::string _fragmentShaderSource = R"(#version 330 core
			out vec4 FragColor;

			in vec3 v_position;
			in vec4 v_Color;
		
			void main()
			{
				FragColor = vec4(v_position * 0.5 + 0.5, 1.0f);
				FragColor = v_Color;
			}
			)";


		std::shared_ptr<OpenGLShader> _shader;
		std::shared_ptr<VertexArray> _vertexArray;

	public:
		
		Application();
		
		virtual ~Application();
		void Run();

		void OnWindowEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *_applicationInstance; }
		Window& GetWindow() const { return *_windowInstance; }
	};


	//To be defined in client
	Application* CreateApplication();
}


