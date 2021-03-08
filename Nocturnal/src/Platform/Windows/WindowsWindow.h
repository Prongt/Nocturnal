#pragma once

#include "Nocturnal/Window.h"

#include <GLFW/glfw3.h>
#include "Nocturnal/Renderer/RendererContext.h"


namespace Nocturnal
{
	class WindowsWindow : public Window
	{
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* mWindowInstance;
		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSyncIsEnabled;
			EventCallbackFunction EventCallback;
		};

		WindowData mWindowInstanceData;
		RendererContext* mRenderingContextInstance;
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return mWindowInstanceData.Width; }
		unsigned int GetHeight() const override { return mWindowInstanceData.Height; }

		void SetEventCallback(const EventCallbackFunction& callback) override { mWindowInstanceData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;

		void* GetNativeWindow() const override { return  mWindowInstance; }
	};
}