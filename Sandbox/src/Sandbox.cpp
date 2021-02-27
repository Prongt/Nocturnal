#include <Nocturnal.h>


#include "imgui/imgui.h"
#include "Nocturnal/Events/KeyEvent.h"
#include "Nocturnal/Renderer/RenderCommand.h"
#include "Nocturnal/Renderer/Renderer.h"
#include "Nocturnal/Renderer/Texture.h"
#include "glm/glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Nocturnal::Layer
{
private:

	std::shared_ptr<Nocturnal::Shader> _Shader;
	std::shared_ptr<Nocturnal::VertexArray> _VertexArray;
	std::shared_ptr<Nocturnal::Texture> _Texture;
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
		_VertexArray.reset(Nocturnal::VertexArray::Create());

		float vertices[] = {
			   0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		1.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		1.0f, 0.0f,
			 -0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		0.0f, 0.0f,
			  -0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		0.0f, 1.0f,
											  			  
			    0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		0.0f, 1.0f,
			   0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		0.0f, 0.0f,
			  -0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		1.0f, 0.0f,
			   -0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		1.0f, 1.0f,
			  								  			  
			   -0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		0.0f, 0.0f,
			   0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		1.0f, 1.0f,
			    0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		1.0f, 0.0f,
			  -0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 0.25f,		0.0f, 1.0f,
		};

		std::shared_ptr<Nocturnal::VertexBuffer> _vertexBuffer;
		_vertexBuffer.reset(Nocturnal::VertexBuffer::Create(vertices, sizeof(vertices)));

		const Nocturnal::BufferLayout layout = {
			{Nocturnal::ShaderType::Float3, "a_Position"},
			{Nocturnal::ShaderType::Float4, "a_Color"},
			{Nocturnal::ShaderType::Float2, "a_TexCoord"}
		};
		_vertexBuffer->SetLayout(layout);
		_VertexArray->AddVertexBuffer(_vertexBuffer);


		std::shared_ptr<Nocturnal::IndexBuffer> _indexBuffer;
		uint32_t indices[] = 
		{
			0, 1, 3, 1, 2, 3,
			0, 1, 4, 1, 4, 5,
			2, 3, 7, 2, 6, 7,
			4, 5, 7, 5, 6, 7,
			0, 3, 10, 3, 10, 8,
			1, 2, 9, 2, 9, 11
		};
		_indexBuffer.reset(Nocturnal::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		_VertexArray->AddIndexBuffer(_indexBuffer);

		_Texture.reset(Nocturnal::Texture::Create("res/Textures/Container.jpg"));
		_Texture->Bind();

		_Shader.reset(Nocturnal::Shader::Create("res/Shaders/VertexShader.vs", "res/Shaders/FragmentShader.fs"));
		_Shader->Bind();
	}
	
	void OnUpdate() override
	{
		Nocturnal::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f);
		Nocturnal::RenderCommand::Clear();

		Nocturnal::Renderer::BeginScene();

		_Texture->Bind();
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, Nocturnal::RenderCommand::GetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		char uniformName[] = "model";
		_Shader->SetMatrix4(uniformName, 1, false, glm::value_ptr(model));

		float rotation = 45.0f;
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::Space))
		{
			rotation *= -1;
		}

		glm::mat4 projection = glm::perspective(glm::radians(rotation), 800.0f / 600.0f, 0.1f, 100.0f);
		char uniformNameB[] = "projection";
		_Shader->SetMatrix4(uniformNameB, 1, false, glm::value_ptr(projection));

		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
		char uniformNameC[] = "view";
		_Shader->SetMatrix4(uniformNameC, 1, false, glm::value_ptr(view));
		
		_Shader->Bind();
		
		Nocturnal::Renderer::Submit(_VertexArray);

		Nocturnal::Renderer::EndScene();
		
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::F4))
		{
			Nocturnal::Application::Get().CloseApplication();
		}
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