#pragma once

#ifdef NOC_PLATFORM_WINDOWS

extern Nocturnal::Application* Nocturnal::CreateApplication();

int main(int argc, char** argv) {
	auto app = Nocturnal::CreateApplication();
	app->Run();

	delete app;
}


#endif
