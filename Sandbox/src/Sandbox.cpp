#include <Nocturnal.h>


#include "imgui/imgui.h"
#include "Nocturnal/Events/KeyEvent.h"
#include "Nocturnal/Renderer/RenderCommand.h"
#include "Nocturnal/Renderer/Renderer.h"

class ExampleLayer : public Nocturnal::Layer
{
private:
	const std::string _VertexShaderSource = R"(#version 330 core
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

	const std::string _FragmentShaderSource = R"(#version 330 core
			out vec4 FragColor;

			in vec3 v_position;
			in vec4 v_Color;
		
			void main()
			{
				FragColor = vec4(v_position * 0.5 + 0.5, 1.0f);
				FragColor = v_Color;
			}
			)";

	std::shared_ptr<Nocturnal::OpenGLShader> _Shader;
	std::shared_ptr<Nocturnal::VertexArray> _VertexArray;
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
		_VertexArray.reset(Nocturnal::VertexArray::Create());

		//Vertices of the triangle
		//z is 0 as it is a 2d triangle 
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Nocturnal::VertexBuffer> _vertexBuffer;
		_vertexBuffer.reset(Nocturnal::VertexBuffer::Create(vertices, sizeof(vertices)));

		const Nocturnal::BufferLayout layout = {
			{Nocturnal::ShaderType::Float3, "a_Position"},
			{Nocturnal::ShaderType::Float4, "a_Color"}
		};
		_vertexBuffer->SetLayout(layout);
		_VertexArray->AddVertexBuffer(_vertexBuffer);


		std::shared_ptr<Nocturnal::IndexBuffer> _indexBuffer;
		uint32_t indices[3] = { 0, 1, 2 };
		_indexBuffer.reset(Nocturnal::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		_VertexArray->AddIndexBuffer(_indexBuffer);


		_Shader = std::make_unique<Nocturnal::OpenGLShader>(_VertexShaderSource, _FragmentShaderSource);
	}
	
	void OnUpdate() override
	{
		Nocturnal::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f);
		Nocturnal::RenderCommand::Clear();

		Nocturnal::Renderer::BeginScene();

		_Shader->Bind();
		Nocturnal::Renderer::Submit(_VertexArray);

		Nocturnal::Renderer::EndScene();
		/*if (Nocturnal::Input::IsKeyPressed(Nocturnal::KeyCode::B))
		{
			NOC_WARN("B key was pressed");
		}
		
		if (Nocturnal::Input::IsKeyUp(Nocturnal::KeyCode::Space))
		{
			NOC_WARN("Space Released");
		}

		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::D))
		{
			NOC_WARN("d Held");
		}*/
	}

	bool OnKeyPressed(Nocturnal::KeyPressedEvent& event)
	{
		NOC_TRACE("{0} was pressed", event.GetKeyCode());
		return true;
	}

	void OnEvent(Nocturnal::Event& event) override
	{
		Nocturnal::EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<Nocturnal::KeyPressedEvent>(NOC_BIND_EVENT_FUNCTION(ExampleLayer::OnKeyPressed));
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Bla");
		ImGui::End();
	}
};

class Sandbox : public Nocturnal::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox()
	{
		
	}
};

Nocturnal::Application* Nocturnal::CreateApplication()
{
	return new Sandbox();
}