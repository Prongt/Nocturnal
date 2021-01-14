#include <Nocturnal.h>

#include "Nocturnal/Events/KeyEvent.h"

class ExampleLayer : public Nocturnal::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
	}
	
	void OnUpdate() override
	{
		/*if (Nocturnal::Input::IsKeyPressed(Nocturnal::KeyCode::B))
		{
			NOC_WARN("B key was pressed");
		}
		
		if (Nocturnal::Input::IsKeyReleased(Nocturnal::KeyCode::Space))
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