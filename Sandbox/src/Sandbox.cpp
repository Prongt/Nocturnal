#include <Nocturnal.h>
#include "imgui/imgui.h"

class ExampleLayer : public Nocturnal::Layer
{
private:

	std::shared_ptr<Nocturnal::Shader> mShader;
	std::shared_ptr<Nocturnal::VertexArray> mVertexArray;
	std::shared_ptr<Nocturnal::Texture> mTexture;

	

	float mFieldOfView = 45.0f;
	

	/*glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);*/

	Nocturnal::Camera mCamera;
public:
	ExampleLayer()
		: Layer("ExampleLayer"), mCamera(Nocturnal::Camera())
	{
		mVertexArray.reset(Nocturnal::VertexArray::Create());

		const Nocturnal::BufferLayout layout = {
			{Nocturnal::ShaderType::Float3, "a_Position"},
			{Nocturnal::ShaderType::Float4, "a_Color"},
			{Nocturnal::ShaderType::Float2, "a_TexCoord"}
		};
		
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
		_vertexBuffer->SetLayout(layout);
		mVertexArray->AddVertexBuffer(_vertexBuffer);
		
		uint32_t indices[] = 
		{
			0, 1, 3, 1, 2, 3,
			0, 1, 4, 1, 4, 5,
			2, 3, 7, 2, 6, 7,
			4, 5, 7, 5, 6, 7,
			0, 3, 10, 3, 10, 8,
			1, 2, 9, 2, 9, 11
		};
		std::shared_ptr<Nocturnal::IndexBuffer> indexBuffer;
		indexBuffer.reset(Nocturnal::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		mVertexArray->AddIndexBuffer(indexBuffer);

		mTexture.reset(Nocturnal::Texture::Create("res/Textures/Container.jpg"));
		mTexture->Bind();

		mShader.reset(Nocturnal::Shader::Create("res/Shaders/VertexShader.vs", "res/Shaders/FragmentShader.fs"));
		mShader->Bind();

		//Converting from screen to clip space
		glm::mat4 projection = glm::perspective(glm::radians(mFieldOfView), 800.0f / 400.0f, 0.1f, 100.0f);
		mShader->SetMatrix4(static_cast<char*>("projection"), 1, false, glm::value_ptr(projection));

	}
	
	void OnUpdate(const float deltaTime) override
	{
		Nocturnal::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f);
		Nocturnal::RenderCommand::Clear();

		Nocturnal::Renderer::BeginScene();

		mTexture->Bind();

		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::W))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Forward, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::S))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Back, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::A))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Left, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::D))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Right, deltaTime);

		auto [mouseX, mouseY] = Nocturnal::Input::GetMousePosition();
		mCamera.ProcessMouseMovement(mouseX, mouseY);

		
		glm::mat4 view = mCamera.GetViewMatrix();
		mShader->SetMatrix4(static_cast<char*>("view"), 1, false, glm::value_ptr(view));

		//Converting from object to world space
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, Nocturnal::RenderCommand::GetTime() * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mShader->SetMatrix4(static_cast<char*>("model"), 1, false, glm::value_ptr(model));

		
		mShader->Bind();
		
		Nocturnal::Renderer::Submit(mVertexArray);

		Nocturnal::Renderer::EndScene();
		
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::F4))
		{
			Nocturnal::Application::Get().CloseApplication();
		}
	}

	bool OnMouseScrolled(Nocturnal::MouseScrolledEvent& event)
	{
		mFieldOfView = mCamera.CalculateFov(event.GetYOffset());
		
		//Converting from screen to clip space
		glm::mat4 projection = glm::perspective(glm::radians(mFieldOfView), 800.0f / 400.0f, 0.1f, 100.0f);
		mShader->SetMatrix4(static_cast<char*>("projection"), 1, false, glm::value_ptr(projection));
		
		return true;
	}

	void OnEvent(Nocturnal::Event& event) override
	{
		Nocturnal::EventDispatcher eventDispatcher(event);
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

	virtual ~Sandbox() = default;
};

Nocturnal::Application* Nocturnal::CreateApplication()
{
	return new Sandbox();
}