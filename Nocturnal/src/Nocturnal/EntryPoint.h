#pragma once

#ifdef NOC_PLATFORM_WINDOWS

extern Nocturnal::Application* Nocturnal::CreateApplication();

int main(int argc, char** argv) {
	Nocturnal::Log::Init();
	NOC_CORE_INFO("Core Logging Initialized");
	NOC_INFO("Client Logging Initialized");

	Nocturnal::Application* app = Nocturnal::CreateApplication();
	app->Run();
	delete app;
}


#endif
