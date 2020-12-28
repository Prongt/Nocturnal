#include <Nocturnal.h>

class Sandbox : public Nocturnal::Application
{
public:
	Sandbox()
	{
		
	}
	
	~Sandbox()
	{
		
	}
};

Nocturnal::Application* Nocturnal::CreateApplication()
{
	return new Sandbox();
}