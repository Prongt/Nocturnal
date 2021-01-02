#pragma once

#include "Event.h"

namespace Nocturnal {

	class NOCTURNAL_API MouseMovedEvent : public Event
	{
	private:
		float MouseX, MouseY;
		
	public:
		MouseMovedEvent(const float mouseX, const float mouseY)
			: MouseX(mouseX), MouseY(mouseY) {}

		MouseMovedEvent(const double mouseX, const double mouseY)
			: MouseX(static_cast<float>(mouseX)), MouseY(static_cast<float>(mouseY)) {}

		float GetX() const { return MouseX; }
		float GetY() const { return MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: X:" << MouseX << ", Y:" << MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	
	};

	class NOCTURNAL_API MouseScrolledEvent : public Event
	{
	private:
		float XOffset, YOffset;
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: XOffset(xOffset), YOffset(yOffset) {}

		MouseScrolledEvent(const double xOffset, const double yOffset)
			: XOffset(static_cast<float>(xOffset)), YOffset(static_cast<float>(yOffset)) {}

		float GetXOffset() const { return XOffset; }
		float GetYOffset() const { return YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: X:" << GetXOffset() << ", Y:" << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NOCTURNAL_API MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(const int button)
			: Button(button) {}

		int Button;
	public:
		int GetMouseButton() const { return Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NOCTURNAL_API MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		MouseButtonDownEvent(const int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDownEvent: " << Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonDown)
	};

	class NOCTURNAL_API MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		MouseButtonUpEvent(const int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUpEvent: " << Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonUp)
	};

}