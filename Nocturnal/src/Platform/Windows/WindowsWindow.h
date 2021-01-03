#pragma once

#include "Nocturnal/Window.h"

#include <GLFW/glfw3.h>


namespace Nocturnal
{
	class WindowsWindow : public Window
	{
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* WindowInstance;
		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSyncIsEnabled;
			EventCallbackFunction EventCallback;
		};

		WindowData WindowInstanceData;
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return WindowInstanceData.Width; }
		unsigned int GetHeight() const override { return WindowInstanceData.Height; }

		void SetEventCallback(const EventCallbackFunction& callback) override { WindowInstanceData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;

		virtual void* GetNativeWindow() const { return  WindowInstance; }
	};
}