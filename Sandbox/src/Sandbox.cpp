#include <Nocturnal.h>


#include "imgui/imgui.h"
#include "Nocturnal/Events/KeyEvent.h"
#include "Nocturnal/Events/MouseEvent.h"
#include "Nocturnal/Renderer/RenderCommand.h"
#include "Nocturnal/Renderer/Renderer.h"
#include "Nocturnal/Renderer/Texture.h"
#include "glm/glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Nocturnal/Renderer/Camera.h"

class ExampleLayer : public Nocturnal::Layer
{
private:

	std::shared_ptr<Nocturnal::Shader> _Shader;
	std::shared_ptr<Nocturnal::VertexArray> _VertexArray;
	std::shared_ptr<Nocturnal::Texture> _Texture;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float fieldOfView = 45.0f;
	

	/*glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);*/

	Nocturnal::Camera _Camera;
public:
	ExampleLayer()
		: Layer("ExampleLayer"), _Camera(Nocturnal::Camera())
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

		//Converting from screen to clip space
		glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), 800.0f / 400.0f, 0.1f, 100.0f);
		_Shader->SetMatrix4(static_cast<char*>("projection"), 1, false, glm::value_ptr(projection));

	}
	
	void OnUpdate() override
	{
		Nocturnal::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f);
		Nocturnal::RenderCommand::Clear();

		Nocturnal::Renderer::BeginScene();

		_Texture->Bind();

		float currentFrame = Nocturnal::RenderCommand::GetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::W))
			_Camera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Forward, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::S))
			_Camera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Back, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::A))
			_Camera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Left, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::D))
			_Camera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Right, deltaTime);

		auto [mouseX, mouseY] = Nocturnal::Input::GetMousePosition();
		_Camera.ProcessMouseMovement(mouseX, mouseY);

		
		glm::mat4 view = _Camera.GetViewMatrix();
		_Shader->SetMatrix4(static_cast<char*>("view"), 1, false, glm::value_ptr(view));

		//Converting from object to world space
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, Nocturnal::RenderCommand::GetTime() * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_Shader->SetMatrix4(static_cast<char*>("model"), 1, false, glm::value_ptr(model));

		
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
		//NOC_ERROR("{0} was pressed", event.GetKeyCode());
		return true;
	}

	bool OnMouseScrolled(Nocturnal::MouseScrolledEvent& event)
	{
		fieldOfView = _Camera.CalculateFov(event.GetYOffset());
		
		//Converting from screen to clip space
		glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), 800.0f / 400.0f, 0.1f, 100.0f);
		_Shader->SetMatrix4(static_cast<char*>("projection"), 1, false, glm::value_ptr(projection));
		
		return true;
	}

	bool OnMouseMoved(Nocturnal::MouseMovedEvent& event)
	{
		
	}

	void OnEvent(Nocturnal::Event& event) override
	{
		Nocturnal::EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<Nocturnal::KeyPressedEvent>(NOC_BIND_EVENT_FUNCTION(ExampleLayer::OnKeyPressed));
		eventDispatcher.Dispatch<Nocturnal::MouseScrolledEvent>(NOC_BIND_EVENT_FUNCTION(ExampleLayer::OnMouseScrolled));
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
	
	~Sandbox() = default;
};

Nocturnal::Application* Nocturnal::CreateApplication()
{
	return new Sandbox();
}