#include <Nocturnal.h>

class ExampleLayer : public Nocturnal::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
	}
	void OnUpdate() override
	{
		if (Nocturnal::Input::IsKeyDown(Nocturnal::KeyCode::B))
		{
			NOC_WARN("B key is down");
		}
	}

	void OnEvent(Nocturnal::Event& event) override
	{
		
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