#pragma once
#include "Nocturnal/Layer.h"
#include "Nocturnal/Application.h"
#include "Nocturnal/Events/KeyEvent.h"
#include "Nocturnal/Events/MouseEvent.h"

namespace Nocturnal
{
	class NOCTURNAL_API ImGuiLayer : public Layer
	{
	private:
		float DeltaTime = 0;

		bool OnKeyDownEvent(KeyDownEvent& event);
		bool OnKeyUpEvent(KeyUpEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseDownEvent(MouseButtonDownEvent& event);
		bool OnMouseUpEvent(MouseButtonUpEvent& event);
		bool OnMouseScrollEvent(MouseScrolledEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	};
}
