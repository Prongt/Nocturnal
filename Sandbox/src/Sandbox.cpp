#include <Nocturnal.h>


class Sandbox : public Nocturnal::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Nocturnal::ImGuiLayer());
	}
	
	~Sandbox()
	{
		
	}
};

Nocturnal::Application* Nocturnal::CreateApplication()
{
	return new Sandbox();
}