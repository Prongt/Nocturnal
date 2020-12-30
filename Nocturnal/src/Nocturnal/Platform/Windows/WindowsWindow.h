#pragma once

#include "Nocturnal/Window.h"

#include <GLFW/glfw3.h>

namespace Nocturnal
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return WindowInstanceData.Width; }
		inline unsigned int GetHeight() const override { return WindowInstanceData.Height; }

		inline void SetEventCallback(const EventCallbackFunction& callback) override { WindowInstanceData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private :
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
	};
}