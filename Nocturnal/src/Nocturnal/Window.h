#pragma once

#include "NocturnalPrecompiledHeaders.h"

#include "Nocturnal/Core.h"
#include "Nocturnal/Events/Event.h"

namespace Nocturnal
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Nocturnal Engine", const unsigned int width = 1280,
		            const unsigned int height = 720) : Title(title), Width(width), Height(height)
		{
		}
	};

	class NOCTURNAL_API Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
		
	};
}