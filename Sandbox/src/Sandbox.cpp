#include <Nocturnal.h>

class ExampleLayer : public Nocturnal::Layer
{
private:

	std::shared_ptr<Nocturnal::Shader> mShader;
	std::shared_ptr<Nocturnal::VertexArray> mVertexArray;
	std::shared_ptr<Nocturnal::Texture> mTexture;
	std::shared_ptr<Nocturnal::Texture> mTextureSpecular;
	std::shared_ptr<Nocturnal::Shader> mLitShader;
	std::shared_ptr<Nocturnal::Shader> mLightSourceShader;

	Nocturnal::Camera mCamera;

	glm::vec3 mLightPos = glm::vec3(1.2f, 0.0f, 2.0f);
	
public:
	ExampleLayer()
		: Layer("ExampleLayer"), mCamera(Nocturnal::Camera({0,0,5}))
	{
		mVertexArray.reset(Nocturnal::VertexArray::Create());

		const Nocturnal::BufferLayout layout = {
			{Nocturnal::ShaderType::Float3, "aPosition"},
			{Nocturnal::ShaderType::Float3, "aNormal"},
			{Nocturnal::ShaderType::Float2, "aTexCoord"}
		};

		float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

		std::shared_ptr<Nocturnal::VertexBuffer> _vertexBuffer;
		_vertexBuffer.reset(Nocturnal::VertexBuffer::Create(vertices, sizeof(vertices)));
		_vertexBuffer->SetLayout(layout);
		mVertexArray->AddVertexBuffer(_vertexBuffer);


		//TODO fix indicies INDICIES CURRENTLY NOT USED!!!
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

		mTexture.reset(Nocturnal::Texture::Create("res/Textures/container2.png"));
		mTexture->Bind();

		mTextureSpecular.reset(Nocturnal::Texture::Create("res/Textures/container2_specular.png"));
		mTextureSpecular->Bind(1);

		mShader.reset(Nocturnal::Shader::Create("res/Shaders/VertexShader.vs", "res/Shaders/FragmentShader.fs"));
		mShader->Bind();

		mLitShader.reset(Nocturnal::Shader::Create("res/Shaders/LitShader.vs", "res/Shaders/LitShader.fs"));
		mLitShader->Bind();
		

		mLightSourceShader.reset(Nocturnal::Shader::Create("res/Shaders/LightSourceShader.vs", "res/Shaders/LightSourceShader.fs"));
		mLightSourceShader->Bind();
		
		
		mCamera.SetAspectRatio(Nocturnal::Application::Get().GetWindow().GetWidth(),
			Nocturnal::Application::Get().GetWindow().GetHeight());
	}
	
	void OnUpdate(const float deltaTime) override
	{
		Nocturnal::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f);
		Nocturnal::RenderCommand::Clear();

		Nocturnal::Renderer::BeginScene(mCamera);

		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::W))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Forward, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::S))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Back, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::A))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Left, deltaTime);
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::D))
			mCamera.ProcessKeyInput(Nocturnal::CameraMoveDirection::Right, deltaTime);

		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::UpArrow))
			mLightPos.z -= 1 * deltaTime;
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::DownArrow))
			mLightPos.z += 1 * deltaTime;
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::LeftArrow))
			mLightPos.x -= 1 * deltaTime;
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::RightArrow))
			mLightPos.x += 1 * deltaTime;


		auto [mouseX, mouseY] = Nocturnal::Input::GetMousePosition();
		mCamera.ProcessMouseMovement(mouseX, mouseY);

		

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		mLitShader->Bind();
		mLitShader->SetVec3("light.position", mLightPos);
		mLitShader->SetVec3("viewPosition", mCamera.Position);


		

		//material
		//mLitShader->SetVec3("material.ambient", {1.0f, 0.5f, 0.31f});
		//mLitShader->SetVec3("material.diffuse", 0);
		//mLitShader->SetVec3("material.specular", {0.5f, 0.5f, 0.5f});
		mLitShader->SetInt("material.diffuse", 0);
		mLitShader->SetInt("material.specular", 1);
		mTexture->Bind();
		mTextureSpecular->Bind(1);
		mLitShader->SetFloat("material.shininess", 32.0f);

		//Lighting
		
		glm::vec3 lightColor = glm::vec3(1,1,1);
       /* lightColor.x = sin(Nocturnal::Time::GetTime() * 2.0f);
        lightColor.y = sin(Nocturnal::Time::GetTime() * 0.7f);
        lightColor.z = sin(Nocturnal::Time::GetTime() * 1.3f);*/
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		mLitShader->SetVec3("light.ambient", ambientColor);
        mLitShader->SetVec3("light.diffuse", diffuseColor);
		mLitShader->SetVec3("light.specular", {1.0f, 1.0f, 1.0f});
		
		
		
		for (auto& cubePosition : cubePositions)
		{
			//Converting from object to world space
			glm::mat4 transformMatrix = glm::mat4(1.0f);
			transformMatrix = glm::translate(transformMatrix, cubePosition);
			//transformMatrix = glm::rotate(transformMatrix, Nocturnal::Time::GetTime() * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			Nocturnal::Renderer::Submit(mLitShader, mVertexArray, transformMatrix);
		}


		//LightSource Cube
		mLightSourceShader->Bind();
		mLightSourceShader->SetVec3("objectColor", { 1.0f, 0.5f, 0.31f });
		mLightSourceShader->SetVec3("lightColor", { 1.0f, 1.0f, 1.0f });
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		transformMatrix = glm::translate(transformMatrix, mLightPos);
		transformMatrix = glm::scale(transformMatrix, glm::vec3(0.2f));
		Nocturnal::Renderer::Submit(mLightSourceShader, mVertexArray, transformMatrix);

		
		Nocturnal::Renderer::EndScene();
		
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::F4))
		{
			Nocturnal::Application::Get().CloseApplication();
		}
	}

	bool OnMouseScrolled(Nocturnal::MouseScrolledEvent& event)
	{
		mCamera.CalculateFov(event.GetYOffset());
		return true;
	}

	bool OnWindowResize(Nocturnal::WindowResizeEvent& event)
	{
		mCamera.SetAspectRatio(event.GetWidth(), event.GetHeight());
		return true;
	}

	void OnEvent(Nocturnal::Event& event) override
	{
		Nocturnal::EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<Nocturnal::MouseScrolledEvent>(NOC_BIND_EVENT_FUNCTION(ExampleLayer::OnMouseScrolled));
		eventDispatcher.Dispatch<Nocturnal::WindowResizeEvent>(NOC_BIND_EVENT_FUNCTION(ExampleLayer::OnWindowResize));
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